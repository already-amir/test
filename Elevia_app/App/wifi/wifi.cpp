#include "wifi.h"
#include <QtDBus/QtDBus>
#include <QDebug>

Wifi::Wifi(QObject *parent)
    : QObject{parent}
{
    enable_wifi();
}

void Wifi::enable_wifi()
{
    QDBusInterface properties("org.freedesktop.NetworkManager","/org/freedesktop/NetworkManager","org.freedesktop.DBus.Properties",QDBusConnection::systemBus());

    if (!properties.isValid()) {
        qWarning() << "DBus interface invalid";
        return ;
    }

    QDBusReply<void> reply = properties.call(
        "Set",
        "org.freedesktop.NetworkManager",
        "WirelessEnabled",
        QVariant::fromValue(QDBusVariant(true))
        );

    if (!reply.isValid()) {
        qWarning() << "Failed to enable Wi-Fi:"
                   << reply.error().message();
        return ;
    }

    qDebug() << "Wi-Fi enabled successfully";
    return ;
}

void Wifi::disable_wifi()
{
    qDebug()<<"wifi_disable";
}

void Wifi::connect_wifi(const QString &ssid, const QString &password)
{
    qDebug()<<"wifi_connect";
}

void Wifi::disconnect_wifi()
{
    qDebug()<<"wifi_disconnect";
}

void Wifi::forget_wifi(const QString &ssid)
{
    qDebug()<<"wifi_forget";
}

void Wifi::scan_wifi()
{
    qDebug()<<"wifi_scan";
}

QJsonArray Wifi::get_wifi_list()
{
    return m_wifi_list;
}

QString Wifi::get_current_ssid()
{
    return m_current_ssid;
}
