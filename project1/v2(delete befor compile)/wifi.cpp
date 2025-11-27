#include "wifi.h"
#include <QDebug>

Wifi::Wifi(QObject *parent)
    : QObject(parent),
      m_wifiEnabled(false)
{
    m_process = new QProcess(this);
    m_networks = new QStringListModel(this);
    m_timeoutTimer = new QTimer(this);

    m_timeoutTimer->setSingleShot(true);

    connect(m_process, &QProcess::started, this, &Wifi::onProcessStarted);
    connect(m_process, &QProcess::finished, this, &Wifi::onProcessFinished);
    connect(m_process, &QProcess::errorOccurred, this, &Wifi::onProcessError);
    connect(m_timeoutTimer, &QTimer::timeout, this, &Wifi::handleTimeout);
}

/* ==== QML API ==== */

void Wifi::enable()
{
    enqueueCommand({CmdEnable, "", ""});
}

void Wifi::scan()
{
    enqueueCommand({CmdScan, "", ""});
}

void Wifi::connectTo(QString ssid, QString password)
{
    enqueueCommand({CmdConnect, ssid, password});
}

void Wifi::disconnectWifi()
{
    enqueueCommand({CmdDisconnect, "", ""});
}

/* ==== Queue logic ==== */

void Wifi::enqueueCommand(Command cmd)
{
    m_queue.enqueue(cmd);
    if(m_process->state() == QProcess::NotRunning)
        startNextCommand();
}

void Wifi::startNextCommand()
{
    if(m_queue.isEmpty()) {
        m_currentCommand.type = CmdNone;
        return;
    }

    m_currentCommand = m_queue.dequeue();
    QStringList args;

    switch(m_currentCommand.type) {

    case CmdEnable:
        args << "radio" << "wifi" << "on";
        break;

    case CmdScan:
        args << "-f" << "SSID" << "device" << "wifi" << "list";
        break;

    case CmdConnect:
        args << "device" << "wifi" << "connect"
             << m_currentCommand.ssid
             << "password" << m_currentCommand.password;
        break;

    case CmdDisconnect:
        args << "networking" << "off";
        break;

    default:
        return;
    }

    m_process->setProcessChannelMode(QProcess::MergedChannels);
    m_process->start("nmcli", args);

    m_timeoutTimer->start(6000); // 6 ثانیه تایم‌اوت
}

/* ==== QProcess Slots ==== */

void Wifi::onProcessStarted()
{
    emit log("Process started: " + QString::number(m_currentCommand.type));
}

void Wifi::onProcessFinished(int exitCode, QProcess::ExitStatus status)
{
    m_timeoutTimer->stop();

    QString output = m_process->readAll();

    emit log(output);

    switch(m_currentCommand.type)
    {
    case CmdEnable:
        if(exitCode == 0)
            setWifiEnabled(true);
        break;

    case CmdScan:
        if(exitCode == 0)
            parseScanResult(output);
        break;

    case CmdConnect:
        emit log("Connect finished: exit=" + QString::number(exitCode));
        break;

    case CmdDisconnect:
        setWifiEnabled(false);
        break;

    default:
        break;
    }

    startNextCommand();
}

void Wifi::onProcessError(QProcess::ProcessError error)
{
    emit log("Process error: " + QString::number(error));
    startNextCommand();
}

/* ==== Timeout ==== */

void Wifi::handleTimeout()
{
    emit log("Process timeout -> killing");
    m_process->kill();
}

/* ==== Internal ==== */

void Wifi::setWifiEnabled(bool en)
{
    if(m_wifiEnabled == en)
        return;

    m_wifiEnabled = en;
    emit wifiEnabledChanged();
}

void Wifi::parseScanResult(QString output)
{
    QStringList list;
    QStringList lines = output.split("\n");

    for(const QString &line : lines) {
        QString ssid = line.trimmed();
        if(!ssid.isEmpty() && !ssid.contains("SSID"))
            list << ssid;
    }

    m_networks->setStringList(list);
    emit networksChanged();
}
