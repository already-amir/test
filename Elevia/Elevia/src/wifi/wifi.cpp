#include "wifi.h"
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusVariant>
#include <QDebug>

Wifi::Wifi(QObject *parent)
    : QObject(parent), m_is_wifi_enabled(false)
{

    update_wifi_state();
    update_wifi_list();
}

void Wifi::enable_wifi()
{
    if (!QDBusConnection::systemBus().isConnected()) {
        log_error("Cannot connect to system DBus.");
        return;
    }

    QDBusInterface properties(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager",
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
        );

    if (!properties.isValid()) {
        log_error("DBus interface invalid: " + QDBusConnection::systemBus().lastError().message());
        return;
    }

    update_wifi_state();

    if (m_is_wifi_enabled) {
        qDebug() << "Wi-Fi is already enabled.";
        return;
    }

    QDBusReply<void> setReply = properties.call(
        "Set",
        "org.freedesktop.NetworkManager",
        "WirelessEnabled",
        QVariant::fromValue(QDBusVariant(true))
        );

    if (!setReply.isValid()) {
        log_error("Failed to enable Wi-Fi: " + setReply.error().message());
        return;
    }

    qDebug() << "Wi-Fi enabled successfully.";
    m_is_wifi_enabled = true;
    emit wifi_enabled();
}

void Wifi::disable_wifi()
{
    if (!QDBusConnection::systemBus().isConnected()) {
        log_error("Cannot connect to system DBus.");
        return;
    }

    QDBusInterface properties(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager",
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
        );

    if (!properties.isValid()) {
        log_error("DBus interface invalid: " + QDBusConnection::systemBus().lastError().message());
        return;
    }

    update_wifi_state();

    if (!m_is_wifi_enabled) {
        qDebug() << "Wi-Fi is already disabled.";
        return;
    }

    QDBusReply<void> setReply = properties.call(
        "Set",
        "org.freedesktop.NetworkManager",
        "WirelessEnabled",
        QVariant::fromValue(QDBusVariant(false))
        );

    if (!setReply.isValid()) {
        log_error("Failed to disable Wi-Fi: " + setReply.error().message());
        return;
    }

    qDebug() << "Wi-Fi disabled successfully.";
    m_is_wifi_enabled = false;
    emit wifi_disabled();
}

bool Wifi::get_is_wifi_enabled() const
{
    return m_is_wifi_enabled;
}

void Wifi::connect_wifi(const QString &ssid, const QString &password)
{
    if (!QDBusConnection::systemBus().isConnected()) {
        qWarning() << "DBus not connected";
        return ;
    }

    QString devicePath = findWifiDevicePath();
    if (devicePath.isEmpty()) {
        qWarning() << "Wi-Fi device not found";
        return ;
    }

    /* ---------- connection ---------- */
    QVariantMap connection;
    connection["type"] = "802-11-wireless";
    connection["id"] = ssid;
    connection["uuid"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    connection["autoconnect"] = true;

    /* ---------- wifi ---------- */
    QVariantMap wifi;
    wifi["ssid"] = ssid.toUtf8();     // حتماً QByteArray
    wifi["mode"] = "infrastructure";
    wifi["security"] = "802-11-wireless-security";

    /* ---------- security ---------- */
    QVariantMap wifiSecurity;
    wifiSecurity["key-mgmt"] = "wpa-psk";
    wifiSecurity["psk"] = password;

    /* ---------- ip ---------- */
    QVariantMap ipv4;
    ipv4["method"] = "auto";

    QVariantMap ipv6;
    ipv6["method"] = "ignore";

    /* =====================================================
     * این قسمت حیاتی است (a{sa{sv}})
     * ===================================================== */
    QVariantMap settings;
    settings.insert("connection", QVariant::fromValue(connection));
    settings.insert("802-11-wireless", QVariant::fromValue(wifi));
    settings.insert("802-11-wireless-security", QVariant::fromValue(wifiSecurity));
    settings.insert("ipv4", QVariant::fromValue(ipv4));
    settings.insert("ipv6", QVariant::fromValue(ipv6));

    /* ---------- AddConnection ---------- */
    QDBusInterface settingsIface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Settings",
        "org.freedesktop.NetworkManager.Settings",
        QDBusConnection::systemBus()
        );

    QDBusReply<QDBusObjectPath> addReply =
        settingsIface.call(
            "AddConnection",
            QVariant::fromValue(settings)
            );

    if (!addReply.isValid()) {
        qWarning() << "AddConnection failed:" << addReply.error().message();
        return ;
    }

    QDBusObjectPath connectionPath = addReply.value();

    /* ---------- ActivateConnection ---------- */
    QDBusInterface nm(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager",
        "org.freedesktop.NetworkManager",
        QDBusConnection::systemBus()
        );

    QDBusReply<QDBusObjectPath> actReply =
        nm.call(
            "ActivateConnection",
            QVariant::fromValue(connectionPath),
            QVariant::fromValue(QDBusObjectPath(devicePath)),
            QVariant::fromValue(QDBusObjectPath("/"))
            );

    if (!actReply.isValid()) {
        qWarning() << "ActivateConnection failed:" << actReply.error().message();
        return ;
    }

    qDebug() << "Connecting to Wi-Fi:" << ssid;
    return ;
}

void Wifi::disconnect_wifi()
{
    qDebug() << "Disconnecting from current Wi-Fi network: " << m_current_ssid;

    if (m_current_ssid.isEmpty()) {
        log_error("No Wi-Fi network to disconnect from.");
        return;
    }

    QDBusInterface activeConnectionInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/ActiveConnections",
        "org.freedesktop.NetworkManager.Connection.Active",
        QDBusConnection::systemBus()
        );

    if (!activeConnectionInterface.isValid()) {
        log_error("Failed to find active connection.");
        return;
    }

    QDBusReply<void> deactivateReply = activeConnectionInterface.call("Deactivate");
    if (!deactivateReply.isValid()) {
        log_error("Failed to disconnect from Wi-Fi network: " + deactivateReply.error().message());
        return;
    }

    m_current_ssid.clear();
    emit wifi_disconnected();
    qDebug() << "Disconnected from Wi-Fi network.";
}

void Wifi::forget_wifi(const QString &ssid)
{
    qDebug() << "Forgetting Wi-Fi network: " << ssid;

    QDBusInterface settingsInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Settings",
        "org.freedesktop.NetworkManager.Settings",
        QDBusConnection::systemBus()
        );

    if (!settingsInterface.isValid()) {
        log_error("Failed to access NetworkManager settings.");
        return;
    }

    QDBusReply<QVariant> getConnectionsReply = settingsInterface.call("ListConnections");
    if (!getConnectionsReply.isValid()) {
        log_error("Failed to list saved connections: " + getConnectionsReply.error().message());
        return;
    }

    QVariantList connections = getConnectionsReply.value().toList();
    QString connectionPath;

    for (const QVariant &connection : connections) {
        QDBusInterface connectionInterface(
            "org.freedesktop.NetworkManager",
            connection.toString(),
            "org.freedesktop.NetworkManager.Settings.Connection",
            QDBusConnection::systemBus()
            );

        QDBusReply<QVariant> ssidReply = connectionInterface.call("GetSettings");
        if (ssidReply.isValid()) {
            QJsonObject settings = ssidReply.value().toJsonObject();
            if (settings["ssid"].toString() == ssid) {
                connectionPath = connection.toString();
                break;
            }
        }
    }

    if (connectionPath.isEmpty()) {
        log_error("No saved Wi-Fi network found for SSID: " + ssid);
        return;
    }

    QDBusInterface deleteConnectionInterface(
        "org.freedesktop.NetworkManager",
        connectionPath,
        "org.freedesktop.NetworkManager.Settings.Connection",
        QDBusConnection::systemBus()
        );

    QDBusReply<void> deleteReply = deleteConnectionInterface.call("Delete");
    if (!deleteReply.isValid()) {
        log_error("Failed to forget Wi-Fi network: " + deleteReply.error().message());
        return;
    }

    qDebug() << "Forgot Wi-Fi network: " << ssid;
}

void Wifi::scan_wifi()
{
    qDebug() << "Scanning for available Wi-Fi networks...";

    QDBusInterface deviceInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Devices/0", // Use correct device path
        "org.freedesktop.NetworkManager.Device.Wireless",
        QDBusConnection::systemBus()
        );

    if (!deviceInterface.isValid()) {
        log_error("Failed to find Wi-Fi device for scanning.");
        return;
    }

    QDBusReply<void> scanReply = deviceInterface.call("RequestScan");
    if (!scanReply.isValid()) {
        log_error("Failed to start Wi-Fi scan: " + scanReply.error().message());
        return;
    }

    update_wifi_list();
    emit wifi_scan_done(m_wifi_list);
    qDebug() << "Wi-Fi scan completed.";
}

QJsonArray Wifi::get_wifi_list()
{
    return m_wifi_list;
}

QString Wifi::get_current_ssid()
{
    return m_current_ssid;
}

QJsonArray Wifi::get_connected_ssids()
{
    return m_connected_ssids;
}

void Wifi::update_wifi_state()
{
    if (!QDBusConnection::systemBus().isConnected()) {
        log_error("Cannot connect to system DBus.");
        return;
    }

    QDBusInterface properties(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager",
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
        );



    QDBusReply<QVariant> getReply = properties.call(
        "Get",
        "org.freedesktop.NetworkManager",
        "WirelessEnabled"
        );

    if (getReply.isValid()) {
        m_is_wifi_enabled = getReply.value().toBool();
    }
}

void Wifi::update_wifi_list()
{
    // Simulate Wi-Fi scan (in a real case, interact with the NetworkManager)
    m_wifi_list = QJsonArray{
        QJsonObject{{"SSID", "HomeNetwork"}},
        QJsonObject{{"SSID", "OfficeNetwork"}}
    };

    emit wifi_scan_done(m_wifi_list);
}

void Wifi::log_error(const QString &message)
{
    qWarning() << message;
    emit wifi_error(message);
}
