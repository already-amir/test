// Implementation

#include "wifimanager.h"

WifiManager::WifiManager(QObject *parent)
    : QObject(parent)
    , m_wifi_list(new QStringListModel(this))
    , m_proc_scan(new QProcess(this))
    , m_proc_connect(new QProcess(this))
    , m_proc_disconnect(new QProcess(this))
    , m_proc_ping(new QProcess(this))
    , m_proc_enable_disable(new QProcess(this))
    , m_busy(false)
    , m_state(WifiState::Idle)
{
    // Always merge channels for stderr/stdout where reasonable
    m_proc_scan->setProcessChannelMode(QProcess::MergedChannels);
    m_proc_connect->setProcessChannelMode(QProcess::MergedChannels);
    m_proc_disconnect->setProcessChannelMode(QProcess::MergedChannels);
    m_proc_ping->setProcessChannelMode(QProcess::MergedChannels);
    m_proc_enable_disable->setProcessChannelMode(QProcess::MergedChannels);

    // Connect scan handlers
    connect(m_proc_scan, &QProcess::started, this, &WifiManager::onScanStarted);
    connect(m_proc_scan, &QProcess::readyReadStandardOutput, this, &WifiManager::onScanStdOut);
    connect(m_proc_scan, &QProcess::readyReadStandardError, this, &WifiManager::onScanStdErr);
    connect(m_proc_scan, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &WifiManager::onScanFinished);

    // Connect connect handlers
    connect(m_proc_connect, &QProcess::started, this, &WifiManager::onConnectStarted);
    connect(m_proc_connect, &QProcess::readyReadStandardOutput, this, &WifiManager::onConnectStdOut);
    connect(m_proc_connect, &QProcess::readyReadStandardError, this, &WifiManager::onConnectStdErr);
    connect(m_proc_connect, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &WifiManager::onConnectFinished);

    // Disconnect handlers
    connect(m_proc_disconnect, &QProcess::started, this, &WifiManager::onDisconnectStarted);
    connect(m_proc_disconnect, &QProcess::readyReadStandardOutput, this, &WifiManager::onDisconnectStdOut);
    connect(m_proc_disconnect, &QProcess::readyReadStandardError, this, &WifiManager::onDisconnectStdErr);
    connect(m_proc_disconnect, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &WifiManager::onDisconnectFinished);

    // Ping handlers
    connect(m_proc_ping, &QProcess::started, this, &WifiManager::onPingStarted);
    connect(m_proc_ping, &QProcess::readyReadStandardOutput, this, &WifiManager::onPingStdOut);
    connect(m_proc_ping, &QProcess::readyReadStandardError, this, &WifiManager::onPingStdErr);
    connect(m_proc_ping, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &WifiManager::onPingFinished);

    // Enable/disable handlers
    connect(m_proc_enable_disable, &QProcess::started, this, &WifiManager::onEnableDisableStarted);
    connect(m_proc_enable_disable, &QProcess::readyReadStandardOutput, this, &WifiManager::onEnableDisableStdOut);
    connect(m_proc_enable_disable, &QProcess::readyReadStandardError, this, &WifiManager::onEnableDisableStdErr);
    connect(m_proc_enable_disable, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &WifiManager::onEnableDisableFinished);

    // Try to create a DBus interface for NetworkManager. This is optional: if DBus is unavailable,
    // we still function through nmcli but DBus allows event-driven updates.


    // At startup, check wifi radio state and schedule a scan
    QTimer::singleShot(500, this, [this](){
        // non-blocking check using QProcess::execute to read nmcli radio wifi
        QProcess p;
        p.start("nmcli", {"radio", "wifi"});
        p.waitForFinished(1500);
        QString out = QString::fromUtf8(p.readAllStandardOutput()).trimmed();
        bool enabled = (out == "enabled");
        if (enabled) {
            // queue a scan
            scanWifi();
        }
    });
}

WifiManager::~WifiManager() {
    // ensure processes are terminated cleanly
    for (QProcess* p : {m_proc_scan, m_proc_connect, m_proc_disconnect, m_proc_ping, m_proc_enable_disable}) {
        if (p->state() == QProcess::Running) {
            p->kill();
            p->waitForFinished(500);
        }
    }
}

QString WifiManager::stateToString(WifiState s) const {
    switch (s) {
    case WifiState::Idle: return "Idle";
    case WifiState::Scanning: return "Scanning";
    case WifiState::Connecting: return "Connecting";
    case WifiState::Disconnecting: return "Disconnecting";
    case WifiState::Ping: return "Pinging";
    case WifiState::Enabling: return "Enabling";
    case WifiState::Disabling: return "Disabling";
    case WifiState::Busy: return "Busy";
    }
    return "Unknown";
}

void WifiManager::setState(WifiState s) {
    if (m_state == s) return;
    m_state = s;
    emit stateChanged();
}

void WifiManager::startProcessIfIdle(QProcess *proc, const QString &program, const QStringList &args, WifiState targetState) {
    if (proc->state() == QProcess::Running) {
        // decide: either queue the operation or return error
        m_opQueue.enqueue([=]() { startProcessIfIdle(proc, program, args, targetState); });
        qDebug() << "Queued operation because process busy";
        return;
    }
    setState(targetState);
    m_busy = true;
    emit busyChanged();
    proc->start(program, args);
}

void WifiManager::appendStdMsg(QProcess *proc, QByteArray chunk, QString &storage) {
    // Append safely (keep full log)
    if (chunk.isEmpty()) return;
    QString s = QString::fromUtf8(chunk);
    storage += s;
}

// ===== API implementations =====

void WifiManager::enableWifi() {
    // Use nmcli radio wifi on
    startProcessIfIdle(m_proc_enable_disable, "nmcli", {"radio","wifi","on"}, WifiState::Enabling);
}

void WifiManager::disableWifi() {
    startProcessIfIdle(m_proc_enable_disable, "nmcli", {"radio","wifi","off"}, WifiState::Disabling);
}

void WifiManager::scanWifi() {
    // Use terse output (-t) and select useful fields: IN-USE,SSID,SIGNAL,SECURITY
    startProcessIfIdle(m_proc_scan, "nmcli", {"-t","-f","IN-USE,SSID,SIGNAL,SECURITY","device","wifi","list"}, WifiState::Scanning);
}

void WifiManager::connectToWifi() {
    if (m_ssid.isEmpty()) {
        m_err_msg = "SSID is empty";
        emit err_msgChanged();
        emit connected(false, m_err_msg);
        return;
    }
    // Build args without deleting existing connection
    QStringList args = {"device","wifi","connect", m_ssid};
    if (!m_password.isEmpty()) {
        args << "password" << m_password;
    }
    // Optionally add --ask if password is missing and interactive behavior desired
    startProcessIfIdle(m_proc_connect, "nmcli", args, WifiState::Connecting);
}

void WifiManager::disconnectFromWifi() {
    // To disconnect, prefer to find the active connection name for this SSID and call "nmcli connection down id <name>"
    // We'll do a small synchronous lookup then start the process.
    QString conn = findActiveConnectionForSsid(m_connected_ssid);
    if (conn.isEmpty()) {
        // nothing to disconnect - but we still attempt "nmcli device disconnect <ifname>" might require device name
        m_err_msg = "No active connection found for " + m_connected_ssid;
        emit err_msgChanged();
        emit disconnected(false, m_err_msg);
        return;
    }
    startProcessIfIdle(m_proc_disconnect, "nmcli", {"connection","down","id",conn}, WifiState::Disconnecting);
}

void WifiManager::pingGoogle() {
    startProcessIfIdle(m_proc_ping, "ping", {"-c","3","8.8.8.8"}, WifiState::Ping);
}

// ===== nmcli parsing helpers =====

QStringList WifiManager::parseNmcliWifiList(const QString &output) {
    // -t output: lines like "*:MySSID:70:WPA2" or ":OtherNet:30:--"
    QStringList result;
    const auto lines = output.split('\n', Qt::SkipEmptyParts);
    for (QString raw : lines) {
        // Split by ':' but SSID may contain ':'; nmcli -t uses ':' as delimiter, so fields are (IN-USE):(SSID):(SIGNAL):(SECURITY)
        // To be robust, limit to 4 parts
        QStringList parts = raw.split(':');
        if (parts.size() < 4) continue;
        QString inuse = parts[0];
        // Re-join possible extra colon in SSID
        QString ssid = parts[1];
        // If parts>4 then join middle fields into SSID
        if (parts.size() > 4) {
            for (int i = 2; i < parts.size()-2; ++i) ssid += ":" + parts[i];
        }
        QString signal = parts.at(parts.size()-2);
        QString sec = parts.last();
        QString display = QString("%1%2  (signal:%3, sec:%4)").arg(inuse=="*"?"* ":" ", ssid).arg(ssid).arg(signal).arg(sec);
        // better: store structured as "IN-USE|SSID|SIGNAL|SEC"
        result << QString("%1|%2|%3|%4").arg(inuse).arg(ssid).arg(signal).arg(sec);
    }
    return result;
}

QString WifiManager::findActiveConnectionForSsid(const QString &ssid) {
    if (ssid.isEmpty()) return QString();
    // Use nmcli -t -f NAME,DEVICE connection show --active
    QProcess p;
    p.start("nmcli", {"-t","-f","NAME,DEVICE","connection","show","--active"});
    if (!p.waitForFinished(1500)) return QString();
    QString out = QString::fromUtf8(p.readAllStandardOutput()).trimmed();
    // lines like "wifi-MySSID:wlx..." or "MySSID:eth0"
    const auto lines = out.split('\n', Qt::SkipEmptyParts);
    for (QString line : lines) {
        QStringList parts = line.split(':');
        if (parts.size() < 2) continue;
        QString name = parts[0];
        // Check if nmcli connection name contains SSID
        if (name == ssid || name.contains(ssid)) return name;
    }
    return QString();
}

// ===== QProcess slots implementation =====

// --- Scan ---
void WifiManager::onScanStarted() {
    m_scan_output.clear();
    emit commandOutput("Scan started");
}

void WifiManager::onScanStdOut() {
    QByteArray chunk = m_proc_scan->readAllStandardOutput();
    appendStdMsg(m_proc_scan, chunk, m_scan_output);
}

void WifiManager::onScanStdErr() {
    QByteArray chunk = m_proc_scan->readAllStandardError();
    QString err = QString::fromUtf8(chunk).trimmed();
    if (!err.isEmpty()) emit commandError(err);
}

void WifiManager::onScanFinished(int exitCode, QProcess::ExitStatus st) {
    Q_UNUSED(st)
    // parse m_scan_output
    QStringList parsed = parseNmcliWifiList(m_scan_output);
    // convert to user-friendly list
    QStringList display;
    for (QString line : parsed) {
        // stored "IN-USE|SSID|SIGNAL|SEC"
        QStringList p = line.split('|');
        if (p.size() == 4) {
            QString inuse = p[0];
            QString s = p[1];
            QString sig = p[2];
            QString sec = p[3];
            QString d = QString("%1%2  (sig:%3, %4)").arg(inuse=="*"?"* ":" ", s).arg(s).arg(sig).arg(sec);
            display << d;
            if (inuse == "*") {
                m_connected_ssid = s;
                emit connected_ssidChanged();
            }
        }
    }
    m_wifi_list->setStringList(display);
    emit wifi_listChanged();
    emit commandOutput(m_scan_output);

    // cleanup
    m_scan_output.clear();
    m_busy = false;
    emit busyChanged();
    setState(WifiState::Idle);
    // process queued ops
    QTimer::singleShot(10, this, &WifiManager::processNextQueuedOperation);
}

// --- Connect ---
void WifiManager::onConnectStarted() {
    m_connect_output.clear();
    emit commandOutput("Connect started");
}

void WifiManager::onConnectStdOut() {
    QByteArray chunk = m_proc_connect->readAllStandardOutput();
    appendStdMsg(m_proc_connect, chunk, m_connect_output);
}

void WifiManager::onConnectStdErr() {
    QByteArray chunk = m_proc_connect->readAllStandardError();
    QString err = QString::fromUtf8(chunk).trimmed();
    if (!err.isEmpty()) {
        m_err_msg += err + "\n";
        emit err_msgChanged();
        emit commandError(err);
    }
}

void WifiManager::onConnectFinished(int exitCode, QProcess::ExitStatus st) {
    Q_UNUSED(st)
    bool success = false;
    QString reason;

    // nmcli prints success messages like "Device 'wlan0' successfully activated with '...'"
    if (m_connect_output.contains("successfully activated") || exitCode == 0) {
        success = m_connect_output.contains("successfully activated");
        if (!success) {
            // Even if exitCode==0, nmcli might have warnings; do a double-check of active connections
            QString conn = findActiveConnectionForSsid(m_ssid);
            success = !conn.isEmpty();
        }
    }

    if (success) {
        m_connected_ssid = m_ssid;
        emit connected_ssidChanged();
        emit connected(true, m_connect_output);
    } else {
        reason = m_connect_output + "\n" + m_err_msg;
        emit connected(false, reason);
    }

    // cleanup
    m_connect_output.clear();
    m_err_msg.clear();
    m_busy = false;
    emit busyChanged();
    setState(WifiState::Idle);
    QTimer::singleShot(10, this, &WifiManager::processNextQueuedOperation);
}

// --- Disconnect ---
void WifiManager::onDisconnectStarted() {
    m_disconnect_output.clear();
}

void WifiManager::onDisconnectStdOut() {
    QByteArray chunk = m_proc_disconnect->readAllStandardOutput();
    appendStdMsg(m_proc_disconnect, chunk, m_disconnect_output);
}

void WifiManager::onDisconnectStdErr() {
    QByteArray chunk = m_proc_disconnect->readAllStandardError();
    QString err = QString::fromUtf8(chunk).trimmed();
    if (!err.isEmpty()) emit commandError(err);
}

void WifiManager::onDisconnectFinished(int exitCode, QProcess::ExitStatus st) {
    Q_UNUSED(st)
    if (exitCode == 0) {
        // nmcli returns 0 on success
        m_connected_ssid.clear();
        emit connected_ssidChanged();
        emit disconnected(true, "Disconnected");
    } else {
        emit disconnected(false, m_disconnect_output);
    }
    m_disconnect_output.clear();
    m_busy = false;
    emit busyChanged();
    setState(WifiState::Idle);
    QTimer::singleShot(10, this, &WifiManager::processNextQueuedOperation);
}

// --- Ping ---
void WifiManager::onPingStarted() {
    m_ping_output.clear();
}

void WifiManager::onPingStdOut() {
    QByteArray chunk = m_proc_ping->readAllStandardOutput();
    appendStdMsg(m_proc_ping, chunk, m_ping_output);
}

void WifiManager::onPingStdErr() {
    QByteArray chunk = m_proc_ping->readAllStandardError();
    QString err = QString::fromUtf8(chunk).trimmed();
    if (!err.isEmpty()) emit commandError(err);
}

void WifiManager::onPingFinished(int exitCode, QProcess::ExitStatus st) {
    Q_UNUSED(st)
    bool ok = (exitCode == 0);
    emit pingResult(ok, m_ping_output);
    m_ping_output.clear();
    m_busy = false;
    emit busyChanged();
    setState(WifiState::Idle);
    QTimer::singleShot(10, this, &WifiManager::processNextQueuedOperation);
}

// --- Enable/Disable ---
void WifiManager::onEnableDisableStarted() { m_enable_disable_output.clear(); }
void WifiManager::onEnableDisableStdOut() { appendStdMsg(m_proc_enable_disable, m_proc_enable_disable->readAllStandardOutput(), m_enable_disable_output); }
void WifiManager::onEnableDisableStdErr() { QByteArray chunk = m_proc_enable_disable->readAllStandardError(); QString err = QString::fromUtf8(chunk).trimmed(); if (!err.isEmpty()) emit commandError(err); }

void WifiManager::onEnableDisableFinished(int exitCode, QProcess::ExitStatus st) {
    Q_UNUSED(st)
    // After enabling/disabling, update state and possibly trigger scan
    if (m_state == WifiState::Enabling && exitCode == 0) {
        // small delay then scan
        QTimer::singleShot(1000, this, &WifiManager::scanWifi);
    }
    m_enable_disable_output.clear();
    m_busy = false;
    emit busyChanged();
    setState(WifiState::Idle);
    QTimer::singleShot(10, this, &WifiManager::processNextQueuedOperation);
}

// Process queued operations FIFO
void WifiManager::processNextQueuedOperation() {
    if (m_proc_scan->state() == QProcess::Running || m_proc_connect->state() == QProcess::Running ||
        m_proc_disconnect->state() == QProcess::Running || m_proc_ping->state() == QProcess::Running ||
        m_proc_enable_disable->state() == QProcess::Running) {
        // still busy
        return;
    }
    if (m_opQueue.isEmpty()) return;
    auto op = m_opQueue.dequeue();
    if (op) op();
}

// DBus hook (very generic) — called when PropertiesChanged is emitted on NetworkManager
void WifiManager::onNetworkManagerPropertiesChanged(const QString &interface, const QVariantMap &changedProperties, const QStringList &invalidatedProperties) {
    Q_UNUSED(interface)
    Q_UNUSED(invalidatedProperties)
    Q_UNUSED(changedProperties)
    // A simple reaction: schedule a scan to refresh SSID list
    QTimer::singleShot(100, this, &WifiManager::scanWifi);
}

// End of file
