#ifndef WIFI_H
#define WIFI_H

#include <QObject>
#include <QString>
#include <QJsonArray>

#include <QtDBus/QtDBus>

class Wifi : public QObject
{
    Q_OBJECT
public:
    explicit Wifi(QObject *parent = nullptr);
    void enable_wifi();
    void disable_wifi();
    void connect_wifi(const QString &ssid,const QString &password);
    void disconnect_wifi();
    void forget_wifi(const QString &ssid);
    void scan_wifi();
    QJsonArray get_wifi_list();
    QString get_current_ssid();


signals:


private:
    QJsonArray m_wifi_list;
    QString m_current_ssid;
};

#endif // WIFI_H
