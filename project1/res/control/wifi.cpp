//wifi.cpp
#include "wifi.h"

Wifi::Wifi(QObject *parent)
    : QObject{parent},m_wifi_enabeled(false),m_password(""),m_ssid(""),m_busy(false)
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
    if (m_wifi_process->state() == QProcess::Running) {
        int currentType = m_wifi_process->property("type").toInt();
        if (currentType == p_wifi_connect) {
            m_wifi_process->terminate();
            m_wifi_process->waitForFinished(1000);
        } else {
            qDebug() << "Another process running, ignoring connect request";
            return;
        }
    }

    QStringList args = {"radio", "wifi", "on"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->setProperty("type",p_wifi_enable);
    setbusy(true);
    m_wifi_process->start("nmcli", args);
}

void Wifi::disable_wifi()
{
    if (m_wifi_process->state()==QProcess::Running){
        m_wifi_process->kill();
    }
    QStringList args = {"radio", "wifi", "off"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->setProperty("type",p_wifi_disable);
    setbusy(true);
    m_wifi_process->start("nmcli", args);
}

void Wifi::scan_wifi()
{

    if(!m_wifi_enabeled){
        enable_wifi();

        return;
    }
    if (m_wifi_process->state() == QProcess::Running) {
        qDebug() << "Process is still running, skipping scan";
        return;
    }
    if (m_wifi_process->property("type")== p_wifi_scan){
        qDebug() << "wifi is already scanning";
        return;
    }

    QStringList args = {"-f", "SSID", "device", "wifi", "list"};
    m_wifi_process->setProcessChannelMode(QProcess::MergedChannels);
    m_wifi_process->setProperty("type",p_wifi_scan);
    setbusy(true);
    m_wifi_process->start("nmcli", args);
}


void Wifi::connect_wifi()
{
    if (m_wifi_process->property("type")== p_wifi_connect) {
        m_wifi_process->kill();
        m_wifi_process->waitForFinished();
    }

    if (m_ssid.isEmpty()) {
        emit connected(false,"SSID is empty!");
        return;
    }

    QStringList args = {"device", "wifi", "connect", m_ssid};

    if (!m_password.isEmpty()) {
        args <<"password"<<m_password;
    }
    m_wifi_process->setProperty("type",p_wifi_connect);
    setbusy(true);
    m_wifi_process->start("nmcli", args);
}

void Wifi::pingGoogle()
{
    //to do
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
    int type = m_wifi_process->property("type").toInt();
    switch (type) {
    case p_wifi_enable:

        qDebug() << "WiFi enable process started";
        break;
    case p_wifi_disable:

        qDebug() << "WiFi disable process started";
        break;
    case p_wifi_scan:

        qDebug() << "Wifi Scan process started";
        break;
    case p_wifi_connect:

        qDebug() << "WiFi connect process started";
        break;
    case p_wifi_ping:

        qDebug() << "WiFi ping process started";
        break;
    }
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

    int type = m_wifi_process->property("type").toInt();
    switch (type) {
    case p_wifi_scan:

        m_wifi_list->setStringList(lines);
        emit command_out(output);
        break;
    case p_wifi_connect:

        break;
    case p_wifi_ping:

        break;
    default:

        break;
    }
}

void Wifi::onReadyReadStdErr()
{
    QByteArray err = m_wifi_process->readAllStandardError();
    QString error = QString::fromUtf8(err).trimmed();
    if (!error.isEmpty()){
        qDebug() << "error: "<<error;
        emit command_err(error);
    }
    int type = m_wifi_process->property("type").toInt();
    switch (type) {
    case p_wifi_connect:


        emit connected(false, "Process error occurred");
        break;
    }
}

void Wifi::onProcessFinished(int exitCode, QProcess::ExitStatus status)
{
    int type = m_wifi_process->property("type").toInt();
    switch (type) {
    case p_wifi_enable:

        if (exitCode == 0) {
            setwifi_enabeled(true);
            qDebug() << "wiFi enabled";
            QTimer::singleShot(300, this, &Wifi::scan_wifi);
        } else {
            qDebug() << "wiFi enabled error code: "<<exitCode;
        }
        break;
    case p_wifi_disable:

        qDebug() << "WiFi disable process started";
        if (exitCode == 0) {
            setwifi_enabeled(false);
            qDebug() << "wiFi disabled";
        } else {
            qDebug() << "wiFi disable error!";
        }
        break;
    case p_wifi_scan:

        if (exitCode == 0) {
            qDebug() << "Wifi Scan  finished";
        } else {
            qDebug() << "Wifi Scan error";
        }
        break;

    case p_wifi_connect:

        if (exitCode == 0) {
            qDebug() << "WiFi connected";
            emit connected(true);
        } else {
            emit connected(false,"Connection failed!");
        }
        break;
    case p_wifi_ping:

        //to do
        break;
    }
    qDebug() <<"Exit code:" << exitCode << "Status:" << status<<Qt::endl ;
    setbusy(false);
    m_wifi_process->setProperty("type", p_non);
}

void Wifi::onProcessError(QProcess::ProcessError error)
{
    qDebug() << "wifi Process error:" << error;
    emit command_err("wifi Process error: " + QString::number(error));
    setbusy(false);
    m_wifi_process->setProperty("type", p_non);
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

bool Wifi::busy() const
{
    return m_busy;
}

void Wifi::setbusy(bool newBusy)
{
    if (m_busy == newBusy)
        return;
    m_busy = newBusy;
    emit busyChanged();
}
