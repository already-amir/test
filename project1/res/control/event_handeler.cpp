#include "event_handeler.h"

Event_handeler::Event_handeler(QObject *parent)
    : QObject{parent}
{
    m_NNetworksModel = new QStringListModel(this);


}
//....................
QString Event_handeler::run_command(QString cmd, QStringList args)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(cmd, args);

    if(!process.waitForStarted(5000)){
        qDebug() << "Failed to start:" << cmd;
        return "";
    }


    if(!process.waitForFinished(-1)){
        qDebug() << "Process timeout:" << cmd;
        process.kill();
        return "";
    }

    QByteArray output = process.readAll();
    QString result = QString::fromUtf8(output);

    return result;
}
//............
void Event_handeler::enable_wifi()
{
    QString result = run_command("nmcli", {"radio", "wifi", "on"});
    //QString result = run_command("/usr/bin/connmanctl", {"enable", "wifi"});
    qDebug() << result;

}

void Event_handeler::disable_wifi()
{
    QString result = run_command("nmcli", {"radio", "wifi", "off"});
    //QString result = run_command("/usr/bin/connmanctl", {"disable", "wifi"});
    qDebug() << result;
}

void Event_handeler::scan_wifi()
{
    QString output = run_command("nmcli", {"-f", "SSID", "device", "wifi", "list"});
    QStringList lines = output.split("\n", Qt::SkipEmptyParts);
    if (lines.isEmpty()) {
        qWarning() << "WiFi scan returned empty output:" << output;
        return;
    }
    lines.removeFirst();
    qDebug() << "MODEL PTR =" << m_NNetworksModel;
    m_NNetworksModel->setStringList(lines);
    emit NNetworksModelChanged();
    //run_command("nmcli", {"device", "wifi", "rescan"});
    //QString result = run_command("nmcli", {"device", "wifi", "list"});

    //run_command("/usr/bin/connmanctl", {"scan", "wifi"});
    //QString result = run_command("/usr/bin/connmanctl", {"services"});
    qDebug() << lines;
}

void Event_handeler::connect_wifi(const QString &ssid, const QString &password)
{
    QStringList args = {"device", "wifi", "connect", ssid};
    if (!password.isEmpty())
        args << "password" << password;

    QString result = run_command("nmcli", args);
    qDebug() << "Connect to" << ssid << "result:" << result;
}


//.........................
QStringListModel *Event_handeler::NNetworksModel() const
{
    return m_NNetworksModel;
}


void Event_handeler::setNNetworksModel(QStringListModel *newNNetworksModel)
{
    if (m_NNetworksModel == newNNetworksModel)
        return;
    m_NNetworksModel = newNNetworksModel;
    emit NNetworksModelChanged();
}
