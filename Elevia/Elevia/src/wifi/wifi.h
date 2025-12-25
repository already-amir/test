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
    bool get_is_wifi_enabled() const;

    void connect_wifi(const QString &ssid,const QString &password);
    void disconnect_wifi();
    void forget_wifi(const QString &ssid);

    void scan_wifi();
    QJsonArray get_wifi_list();
    QString get_current_ssid();
    QJsonArray get_connected_ssids();



signals:
    void wifi_enabled();
    void wifi_disabled();
    void wifi_connected(const QString &ssid);
    void wifi_disconnected();
    void wifi_scan_done(const QJsonArray &wifiList);
    void wifi_error(const QString &message);

private:
    bool is_wifi_enabled() const;
    void update_wifi_state();
    void update_wifi_list();
    void log_error(const QString &message);



private:
    QJsonArray m_wifi_list;
    QString m_current_ssid;
    QJsonArray m_connected_ssids;
    bool m_is_wifi_enabled;
};

#endif // WIFI_H
