//wifi_mng.cpp
#include "wifi_mng.h"
#include<QDebug>
#include<QtDBus/QDBusInterface>
#include<QtDBus/QDBusReply>

Wifi_mng::Wifi_mng(QObject *parent)
    : QObject{parent}
{}

void Wifi_mng::enableWifi(bool enable)
{
    QDBusInterface manager("net.connman",
                           "/",
                           "net.connman.Manager",
                           QDBusConnection::systemBus());

    if (!manager.isValid()) {
        qWarning() << "Cannot connect to ConnMan Manager";
        return;
    }

    // لیست تکنولوژی‌ها
    QDBusReply<QList<QVariantMap>> technologiesReply = manager.call("GetTechnologies");
    if (!technologiesReply.isValid()) {
        qWarning() << "Failed to get technologies";
        return;
    }

    for (const QVariantMap &tech : technologiesReply.value()) {
        if (tech["Type"].toString() == "wifi") {
            QString path = tech["Path"].toString();
            QDBusInterface wifiInterface("net.connman",
                                         path,
                                         "net.connman.Technology",
                                         QDBusConnection::systemBus());
            if (wifiInterface.isValid()) {
                wifiInterface.call("SetProperty", "Powered", QVariant::fromValue(QDBusVariant(enable)));
            }
        }
    }
}

void Wifi_mng::scanNetworks()
{
    QDBusInterface manager("net.connman",
                           "/",
                           "net.connman.Manager",
                           QDBusConnection::systemBus());

    if (!manager.isValid()) return;

    QDBusReply<QList<QVariantMap>> servicesReply = manager.call("GetServices");
    if (!servicesReply.isValid()) return;

    QStringList ssids;
    for (const QVariantMap &service : servicesReply.value()) {
        QString type = service["Type"].toString();
        if (type == "wifi") {
            QString name = service["Name"].toString();
            ssids << name;
        }
    }

    emit networksFound(ssids);
}
