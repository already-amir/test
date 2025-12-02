#include "blue.h"

Blue::Blue(QObject *parent)
    : QObject{parent},m_blue_list(new QStringListModel(this)),m_bt_process(new QProcess(this)),
    m_connected_blue(""),m_blue_enabeld(false),m_err_msg(""),m_std_msg("")

{
    connect(m_bt_process, &QProcess::started, this, &Blue::onProcessStarted);
    connect(m_bt_process, &QProcess::readyReadStandardOutput, this, &Blue::onReadyReadStdOut);
    connect(m_bt_process, &QProcess::readyReadStandardError, this, &Blue::onReadyReadStdErr);
    connect(m_bt_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Blue::onProcessFinished);
    connect(m_bt_process, &QProcess::errorOccurred, this, &Blue::onProcessError);

    // initial check of adapter power state
    QProcess check;
    check.start("bluetoothctl", {"show"});
    check.waitForFinished(1000);
    QString out = QString::fromUtf8(check.readAllStandardOutput()).trimmed();
    bool powered = out.contains("Powered: yes");
    setBlue_enabeld(powered);

    // initial device list
    listDevices();
}

void Blue::powerOn()
{

}

void Blue::powerOff()
{

}

void Blue::startScan()
{

}

void Blue::listDevices()
{

}

void Blue::connectDevice(const QString &mac)
{

}

void Blue::disconnectDevice(const QString &mac)
{

}

void Blue::pairDevice(const QString &mac)
{

}

void Blue::trustDevice(const QString &mac)
{

}

void Blue::removeDevice(const QString &mac)
{

}

QStringListModel *Blue::blue_list() const
{
    return m_blue_list;
}

void Blue::setBlue_list(QStringListModel *newBlue_list)
{
    if (m_blue_list == newBlue_list)
        return;
    m_blue_list = newBlue_list;
    emit blue_listChanged();
}

QString Blue::connected_blue() const
{
    return m_connected_blue;
}

void Blue::setconnected_blue(const QString &newConnected_blue)
{
    if (m_connected_blue == newConnected_blue)
        return;
    m_connected_blue = newConnected_blue;
    emit connected_blueChanged();
}

bool Blue::blue_enabeld() const
{
    return m_blue_enabeld;
}

void Blue::setBlue_enabeld(bool newBlue_enabeld)
{
    if (m_blue_enabeld == newBlue_enabeld)
        return;
    m_blue_enabeld = newBlue_enabeld;
    emit blue_enabeldChanged();
}

QString Blue::err_msg() const
{
    return m_err_msg;
}

void Blue::seterr_msg(const QString &newErr_msg)
{
    if (m_err_msg == newErr_msg)
        return;
    m_err_msg = newErr_msg;
    emit err_msgChanged();
}

void Blue::onProcessStarted()
{

}

void Blue::onReadyReadStdOut()
{

}

void Blue::onReadyReadStdErr()
{

}

void Blue::onProcessFinished(int exitCode, QProcess::ExitStatus status)
{

}

void Blue::onProcessError(QProcess::ProcessError err)
{

}
