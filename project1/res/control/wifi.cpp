#include "wifi.h"

Wifi::Wifi(QObject *parent)
    : QObject{parent}
{
    m_wifi_list = new QStringListModel(this);
    m_wifi_process = new QProcess(this);
    connect(m_wifi_process, &QProcess::started, this, &Wifi::onProcessStarted);
    connect(m_wifi_process, &QProcess::readyReadStandardOutput, this, &Wifi::onReadyReadStdOut);
    connect(m_wifi_process, &QProcess::readyReadStandardError, this, &Wifi::onReadyReadStdErr);
    connect(m_wifi_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Wifi::onProcessFinished);
    connect(m_wifi_process, &QProcess::errorOccurred, this, &Wifi::onProcessError);

}

QStringListModel *Wifi::wifi_list() const
{
    return m_wifi_list;
}

void Wifi::setwifi_list(QStringListModel *newWifi_list)
{
    if (m_wifi_list == newWifi_list)
        return;
    m_wifi_list = newWifi_list;
    emit wifi_listChanged();
}

void Wifi::enable_wifi()
{
    if (m_wifi_process->state()==QProcess::Running){
        m_wifi_process->kill();
    }
    QStringList args = {"radio", "wifi", "on"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->start("nmcli", args);
}

void Wifi::disable_wifi()
{
    if (m_wifi_process->state()==QProcess::Running){
        m_wifi_process->kill();
    }
    QStringList args = {"radio", "wifi", "off"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->start("nmcli", args);
}

void Wifi::scan_wifi()
{
    if (m_wifi_process->state()==QProcess::Running){
        return;
    }
    QStringList args = {"-f", "SSID", "device", "wifi", "list"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->start("nmcli", args);
}

void Wifi::connect_wifi()
{

}

void Wifi::onProcessStarted()
{
    qDebug() << "wifi Process started.";
}

void Wifi::onReadyReadStdOut()
{
    QByteArray out = m_wifi_process->readAllStandardOutput();
    QString output = QString::fromUtf8(out).trimmed();

    QStringList lines = output.split("\n", Qt::SkipEmptyParts);
    if (!lines.isEmpty() && lines.first().contains("SSID")) lines.removeFirst();

    m_wifi_list->setStringList(lines); // آپدیت مدل QML
    emit command_out(output);
}

void Wifi::onReadyReadStdErr()
{
    QByteArray err = m_wifi_process->readAllStandardError();
    QString error = QString::fromUtf8(err).trimmed();
    if (!error.isEmpty()){

        emit command_err(error);
    }

}

void Wifi::onProcessFinished(int exitCode, QProcess::ExitStatus status)
{
    qDebug() << " wifi Process finished. Exit code:" << exitCode << "Status:" << status;
}

void Wifi::onProcessError(QProcess::ProcessError error)
{
    qDebug() << "wifi Process error:" << error;
}
