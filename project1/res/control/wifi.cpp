//wifi.cpp
#include "wifi.h"

Wifi::Wifi(QObject *parent)
    : QObject{parent},m_wifi_enabeled(false),m_password(""),m_ssid(""),m_busy(false),m_std_msg(""),m_err_msg("")
{
    m_wifi_list = new QStringListModel(this);
    m_wifi_process = new QProcess(this);
    connect(m_wifi_process, &QProcess::started, this, &Wifi::onProcessStarted);
    connect(m_wifi_process, &QProcess::readyReadStandardOutput, this, &Wifi::onReadyReadStdOut);
    connect(m_wifi_process, &QProcess::readyReadStandardError, this, &Wifi::onReadyReadStdErr);
    connect(m_wifi_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Wifi::onProcessFinished);
    connect(m_wifi_process, &QProcess::errorOccurred, this, &Wifi::onProcessError);
    check_we();
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
    if (m_wifi_process->property("type")== p_wifi_scan){
        qDebug() << "wifi is already scanning";
        return;
    }
    if (m_wifi_process->state() == QProcess::Running) {
        qDebug() << "Process is still running, skipping scan";
        return;
    }


    QStringList args = {"-f", "IN-USE,SSID", "device", "wifi", "list"};

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
    if (m_wifi_process->property("type")== p_wifi_ping){
        qDebug() << "wifi is already pinging";
        return;
    }
    if (m_wifi_process->state() == QProcess::Running) {
        qDebug() << "Process is still running, skipping scan";
        return;
    }

    QStringList args = {"-c", "3", "8.8.8.8"};
    m_wifi_process->setProperty("type",p_wifi_ping);
    m_wifi_process->start("ping", args);
}

void Wifi::disconnect()
{
    if (m_wifi_process->state() == QProcess::Running) {
        m_wifi_process->kill();
    }

    if (m_connected_ssid.isEmpty()) {
        qDebug() << "No active WiFi connection to disconnect.";
        emit disconnectsig(false, "No active connection");
        return;
    }

    QStringList args = {"connection", "down", "id", m_connected_ssid};

    m_wifi_process->setProperty("type", p_wifi_disconnect);
    setbusy(true);
    m_wifi_process->start("nmcli", args);
}

void Wifi::check_we()
{
    QProcess check;
    check.start("nmcli", {"radio", "wifi"});
    check.waitForFinished();
    QString out = QString::fromUtf8(check.readAllStandardOutput()).trimmed();
    bool enabled = (out == "enabled");

    setwifi_enabeled(enabled);
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
    case p_wifi_disconnect:

        qDebug() << "WiFi disconnect process started";
        break;
    }
}

void Wifi::onReadyReadStdOut()
{
    QByteArray out = m_wifi_process->readAllStandardOutput();
    QString output = QString::fromUtf8(out).trimmed();
    QStringList lines = output.split("\n", Qt::SkipEmptyParts);
    QStringList cleanList;


    int type = m_wifi_process->property("type").toInt();
    switch (type) {

    case p_wifi_enable:


        break;
    case p_wifi_disable:


        break;

    case p_wifi_scan:
        if (!lines.isEmpty() && lines.first().contains("IN-USE"))
            lines.removeFirst();

        m_connected_ssid = "";

        for (QString line : lines) {
            line = line.trimmed();
            if (line.startsWith("*")) {
                line = line.mid(1).trimmed();
                m_connected_ssid = line;
            }
            cleanList.append(line);
        }

        if (!lines.isEmpty()) lines.removeFirst();
        m_wifi_list->setStringList(cleanList);
        emit connected_ssidChanged();
        emit command_out(output);
        break;
    case p_wifi_connect:

        m_std_msg=output;
        break;
    case p_wifi_ping:

        m_std_msg=output;
        break;

    case p_wifi_disconnect:

        m_std_msg=output;
        break;

    }
}

void Wifi::onReadyReadStdErr()
{
    QByteArray err = m_wifi_process->readAllStandardError();
    QString error = QString::fromUtf8(err).trimmed();
    if (!error.isEmpty()){
        qDebug() << "error: "<<error;
    }
    int type = m_wifi_process->property("type").toInt();
    switch (type) {
    case p_wifi_enable:


        break;
    case p_wifi_disable:


        break;
    case p_wifi_scan:

        emit command_err(error);
        break;

    case p_wifi_connect:

        m_err_msg=error;
        break;

    case p_wifi_ping:
        m_err_msg=error;
        break;

    case p_wifi_disconnect:

        m_err_msg=error;
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
            setconnected_ssid(m_ssid);
            emit connected(true,m_std_msg);
        } else {
            qDebug() << "WiFi connection error";
            emit connected(false,m_std_msg);
        }
        break;

    case p_wifi_ping:

        if (exitCode == 0) {
            qDebug() << "ping completed";
            ping_out(true,m_std_msg);
        } else {
            qDebug() << "ping completion error";
            ping_out(false,m_std_msg);
        }
        break;

    case p_wifi_disconnect:

        if (exitCode == 0) {
            qDebug() << "WiFi disconnected";
            setconnected_ssid("");
            emit disconnectsig(true, "Disconnected");
        } else {
            qDebug() << "WiFi disconnect error";
            emit disconnectsig(false, "Disconnect error");
        }
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

QString Wifi::err_msg() const
{
    return m_err_msg;
}

void Wifi::seterr_msg(const QString &newErr_msg)
{
    if (m_err_msg == newErr_msg)
        return;
    m_err_msg = newErr_msg;
    emit err_msgChanged();
}

QString Wifi::connected_ssid() const
{
    return m_connected_ssid;
}

void Wifi::setconnected_ssid(const QString &newConnected_ssid)
{
    if (m_connected_ssid == newConnected_ssid)
        return;
    m_connected_ssid = newConnected_ssid;
    emit connected_ssidChanged();
}
