#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H


#include <QObject>
#include <QStringListModel>
#include <QProcess>
#include <QTimer>
#include <QQueue>
#include <QtDBus/QDBusConnection>
#include<QtDBus/QDBusInterface>
#include <QDebug>


class WifiManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
    Q_PROPERTY(QStringListModel* wifi_list READ wifi_list NOTIFY wifi_listChanged)
    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString connected_ssid READ connected_ssid NOTIFY connected_ssidChanged)
    Q_PROPERTY(QString err_msg READ err_msg NOTIFY err_msgChanged)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)


public:
    explicit WifiManager(QObject *parent = nullptr);
    ~WifiManager() override;


    // API invokable
    Q_INVOKABLE void enableWifi();
    Q_INVOKABLE void disableWifi();
    Q_INVOKABLE void scanWifi();
    Q_INVOKABLE void connectToWifi();
    Q_INVOKABLE void disconnectFromWifi();
    Q_INVOKABLE void pingGoogle();


    QStringListModel* wifi_list() const { return m_wifi_list; }
    bool busy() const { return m_busy; }


    QString ssid() const { return m_ssid; }
    void setSsid(const QString &s) { if (m_ssid != s) { m_ssid = s; emit ssidChanged(); } }


    QString password() const { return m_password; }
    void setPassword(const QString &p) { if (m_password != p) { m_password = p; emit passwordChanged(); } }


    QString connected_ssid() const { return m_connected_ssid; }


    QString err_msg() const { return m_err_msg; }


    QString state() const { return stateToString(m_state); }


signals:
    void wifi_listChanged();
    void busyChanged();
    void ssidChanged();
    void passwordChanged();
    void connected_ssidChanged();
    void err_msgChanged();
    void stateChanged();


    // detailed outputs
    void commandOutput(const QString& out);
    void commandError(const QString& err);
    void connected(bool ok, const QString &reason);
    void disconnected(bool ok, const QString &reason);
    void pingResult(bool ok, const QString &out);


private slots:
    // internal QProcess handlers for each operation
    void onScanStarted();
    void onScanStdOut();
    void onScanStdErr();
    void onScanFinished(int exitCode, QProcess::ExitStatus st);


    void onConnectStarted();
    void onConnectStdOut();
    void onConnectStdErr();
    void onConnectFinished(int exitCode, QProcess::ExitStatus st);


    void onDisconnectStarted();
    void onDisconnectStdOut();
    void onDisconnectStdErr();
    void onDisconnectFinished(int exitCode, QProcess::ExitStatus st);


    void onPingStarted();
    void onPingStdOut();
    void onPingStdErr();
    void onPingFinished(int exitCode, QProcess::ExitStatus st);


    void onEnableDisableStarted();
    void onEnableDisableStdOut();
    void onEnableDisableStdErr();
    void onEnableDisableFinished(int exitCode, QProcess::ExitStatus st);


    // queue processing
    void processNextQueuedOperation();


    // DBus monitor slot (optional)
    void onNetworkManagerPropertiesChanged(const QString &interface, const QVariantMap &changedProperties, const QStringList &invalidatedProperties);


private:
    enum class WifiState { Idle, Scanning, Connecting, Disconnecting, Ping, Enabling, Disabling, Busy };
    QString stateToString(WifiState s) const;
    void setState(WifiState s);


    // helpers
    void startProcessIfIdle(QProcess *proc, const QString &program, const QStringList &args, WifiState targetState);
    void appendStdMsg(QProcess *proc, QByteArray chunk, QString &storage);


    // nmcli helpers
    QStringList parseNmcliWifiList(const QString &output);
    QString findActiveConnectionForSsid(const QString &ssid);


    // members
    QStringListModel *m_wifi_list;


    // Separate processes for operations (prevents races)
    QProcess *m_proc_scan;
    QProcess *m_proc_connect;
    QProcess *m_proc_disconnect;
    QProcess *m_proc_ping;
    QProcess *m_proc_enable_disable;


    // buffers
    QString m_scan_output;
    QString m_connect_output;
    QString m_disconnect_output;
    QString m_ping_output;
    QString m_enable_disable_output;


    // args/props
    QString m_ssid;
    QString m_password;
    QString m_connected_ssid;
    QString m_err_msg;


    QQueue<std::function<void()>> m_opQueue;
    bool m_busy;
    WifiState m_state;


    // DBus interface to NM (optional)
    QDBusInterface *m_nm_iface = nullptr;
};


#endif // WIFIMANAGER_H
