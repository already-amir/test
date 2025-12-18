#ifndef APP_H
#define APP_H

#include <QObject>
#include "wifi/wifi.h"
#include "mqtt/mqtt.h"


class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged FINAL)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged FINAL)
public:
    explicit App(QObject *parent = nullptr);
    //wifi
    Q_INVOKABLE void enable_wifi();
    Q_INVOKABLE void disable_wifi();
    Q_INVOKABLE void connect_wifi();
    Q_INVOKABLE void disconnect_wifi();
    Q_INVOKABLE void scan_wifi();
    Q_INVOKABLE void forget_wifi();

    //backend
    void send_connect_info();
    void wifi_auto_connct();

    QString ssid() const;
    void setSsid(const QString &newSsid);

    QString password() const;
    void setPassword(const QString &newPassword);

signals:

    void ssidChanged();

    void passwordChanged();

private:
    Wifi *m_Wifi;
    Mqtt *m_Mqtt;
    QString m_ssid;
    QString m_password;
};

#endif // APP_H
