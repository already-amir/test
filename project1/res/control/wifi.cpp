//wifi.cpp
#include "wifi.h"

Wifi::Wifi(QObject *parent)
    : QObject{parent},m_wifi_enabeled(false),m_waiting_for_scan(false),m_password(""),m_ssid("")
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
    setwifi_enabeled(true);
    m_waiting_for_scan=true;
    QTimer::singleShot(1000, this, &Wifi::scan_wifi);


}

void Wifi::disable_wifi()
{
    if (m_wifi_process->state()==QProcess::Running){
        m_wifi_process->kill();
    }
    QStringList args = {"radio", "wifi", "off"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->start("nmcli", args);
    setwifi_enabeled(false);
}

void Wifi::scan_wifi()
{
    if(!m_wifi_enabeled){
        enable_wifi();
    }
    if (m_wifi_process->state()==QProcess::Running){
        qDebug() << "wifi is already scanning";
        return;
    }
    QStringList args = {"-f", "SSID", "device", "wifi", "list"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->start("nmcli", args);
}


void Wifi::connect_wifi()
{
    if (m_wifi_process->state() == QProcess::Running) {
        m_wifi_process->kill();
        m_wifi_process->waitForFinished();
    }

    if (m_ssid.isEmpty()) {
        emit connectionFailed("SSID is empty!");
        return;
    }

    QStringList args = {"device", "wifi", "connect", m_ssid};

    if (!m_password.isEmpty()) {
        args <<"password"<<m_password;
    }

    m_wifi_process->start("nmcli", args);
    qDebug()<<m_ssid<<"/n"<<m_password;
}

void Wifi::pingGoogle()
{
    QProcess *pingProcess = new QProcess(this);

    connect(pingProcess, &QProcess::readyReadStandardOutput, this, [=]() {QString output = QString::fromUtf8(pingProcess->readAllStandardOutput());emit pingResult(true, output);});

    connect(pingProcess,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            [=](int exitCode, QProcess::ExitStatus) {
                if (exitCode == 0)
                    emit pingResult(true, "Internet Connected ✅");
                else
                    emit pingResult(false, "No Internet ❌");

                pingProcess->deleteLater();
            });

    QStringList args = {"-c", "3", "8.8.8.8"};   // او میتونی google.com هم بزاری
    pingProcess->start("ping", args);
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
    for (QString &line : lines) {
        line = line.trimmed();
    }
    m_wifi_list->setStringList(lines);
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
    if (m_waiting_for_scan) {
        m_waiting_for_scan = false;
        scan_wifi();
    }
    if (exitCode == 0) {
        emit connected();
    } else {
        emit connectionFailed("Connection failed!");
    }
}

void Wifi::onProcessError(QProcess::ProcessError error)
{
    qDebug() << "wifi Process error:" << error;
    emit command_err("wifi Process error: " + QString::number(error));
}

bool Wifi::wifi_enabeled() const
{
    return m_wifi_enabeled;
}

void Wifi::setwifi_enabeled(bool newWifi_enabeled)
{
    if (m_wifi_enabeled == newWifi_enabeled)
        return;
    m_wifi_enabeled = newWifi_enabeled;
    emit wifi_enabeledChanged();
}

QString Wifi::password() const
{
    return m_password;
}

void Wifi::setpassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

QString Wifi::ssid() const
{
    return m_ssid;
}

void Wifi::setSsid(const QString &newSsid)
{
    if (m_ssid == newSsid)
        return;
    m_ssid = newSsid;
    emit ssidChanged();
}
