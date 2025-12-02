#include "bluetooth.h"
#include <QJsonArray>
#include <QProcess>
#include <QDebug>

Bluetooth::Bluetooth(QObject *parent)
    : QObject(parent),
    m_device_list(new QStringListModel(this)),
    m_bt_process(new QProcess(this)),
    m_powered(false),
    m_busy(false),
    m_std_msg(""),
    m_err_msg("")
{
    connect(m_bt_process, &QProcess::started, this, &Bluetooth::onProcessStarted);
    connect(m_bt_process, &QProcess::readyReadStandardOutput, this, &Bluetooth::onReadyReadStdOut);
    connect(m_bt_process, &QProcess::readyReadStandardError, this, &Bluetooth::onReadyReadStdErr);
    connect(m_bt_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Bluetooth::onProcessFinished);
    connect(m_bt_process, &QProcess::errorOccurred, this, &Bluetooth::onProcessError);

    // initial check of adapter power state
    QProcess check;
    check.start("bluetoothctl", {"show"});
    check.waitForFinished(1000);
    QString out = QString::fromUtf8(check.readAllStandardOutput()).trimmed();
    bool powered = out.contains("Powered: yes");
    setPowered(powered);

    // initial device list
    listDevices();
}

QStringListModel* Bluetooth::device_list() const { return m_device_list; }
void Bluetooth::setDevice_list(QStringListModel* newList) {
    if (m_device_list == newList) return;
    m_device_list = newList;
    emit device_listChanged();
}

bool Bluetooth::powered() const { return m_powered; }
void Bluetooth::setPowered(bool p) {
    if (m_powered == p) return;
    m_powered = p;
    emit poweredChanged();
}

bool Bluetooth::busy() const { return m_busy; }
void Bluetooth::setBusy(bool b) {
    if (m_busy == b) return;
    m_busy = b;
    emit busyChanged();
}

QString Bluetooth::connected_mac() const { return m_connected_mac; }
void Bluetooth::setConnected_mac(const QString &mac) {
    if (m_connected_mac == mac) return;
    m_connected_mac = mac;
    emit connected_macChanged();
}

QString Bluetooth::err_msg() const { return m_err_msg; }
void Bluetooth::setErr_msg(const QString &e) {
    if (m_err_msg == e) return;
    m_err_msg = e;
    emit err_msgChanged();
}

void Bluetooth::powerOn() {
    if (m_bt_process->state() == QProcess::Running) {
        qDebug() << "Process running, cannot powerOn now";
        return;
    }
    QStringList args = {"power", "on"};
    m_bt_process->setProcessChannelMode(QProcess::MergedChannels);
    m_bt_process->setProperty("type", p_power_on);
    setBusy(true);
    m_bt_process->start("bluetoothctl", args);
}

void Bluetooth::powerOff() {
    if (m_bt_process->state() == QProcess::Running) {
        m_bt_process->kill();
    }
    QStringList args = {"power", "off"};
    m_bt_process->setProcessChannelMode(QProcess::MergedChannels);
    m_bt_process->setProperty("type", p_power_off);
    setBusy(true);
    m_bt_process->start("bluetoothctl", args);
}

void Bluetooth::startScan() {
    if (!m_powered) {
        powerOn();
        // After powerOn finishes, user can call startScan again; or you can set up to auto-scan.
        return;
    }
    if (m_bt_process->state() == QProcess::Running) {
        qDebug() << "Process running, skipping startScan";
        return;
    }

    // Start scan (blocking exec), then after a short delay collect devices and stop scan
    setBusy(true);
    // Turn scan on (blocking)
    execBlocking({"scan", "on"});

    // Wait a bit (3s) to let parties respond, then collect devices and stop scan
    QTimer::singleShot(3000, this, [this]() {
        // get devices (blocking)
        QProcess p;
        p.start("bluetoothctl", {"devices"});
        p.waitForFinished(2000);
        QString out = QString::fromUtf8(p.readAllStandardOutput()).trimmed();
        parseDevicesOutput(out);

        // stop scanning
        execBlocking({"scan", "off"});
        setBusy(false);
        emit scanned();
    });
}

void Bluetooth::listDevices() {
    if (m_bt_process->state() == QProcess::Running) {
        qDebug() << "Process running, skipping listDevices";
        return;
    }
    m_bt_process->setProcessChannelMode(QProcess::MergedChannels);
    m_bt_process->setProperty("type", p_list);
    setBusy(true);
    m_bt_process->start("bluetoothctl", {"devices"});
}

void Bluetooth::connectDevice(const QString &mac) {
    if (mac.isEmpty()) {
        emit command_err("MAC empty");
        emit connected(false, "MAC empty");
        return;
    }

    if (m_bt_process->property("type") == p_connect) {
        m_bt_process->kill();
        m_bt_process->waitForFinished();
    }

    QStringList args = {"connect", mac};
    m_bt_process->setProperty("type", p_connect);
    setBusy(true);
    m_bt_process->start("bluetoothctl", args);
}

void Bluetooth::disconnectDevice(const QString &mac) {
    if (mac.isEmpty()) {
        emit command_err("MAC empty");
        emit disconnected(false, "MAC empty");
        return;
    }

    if (m_bt_process->state() == QProcess::Running) {
        m_bt_process->kill();
    }
    QStringList args = {"disconnect", mac};
    m_bt_process->setProcessChannelMode(QProcess::MergedChannels);
    m_bt_process->setProperty("type", p_disconnect);
    setBusy(true);
    m_bt_process->start("bluetoothctl", args);
}

void Bluetooth::pairDevice(const QString &mac) {
    if (mac.isEmpty()) {
        emit command_err("MAC empty");
        return;
    }
    if (m_bt_process->property("type") == p_pair) {
        m_bt_process->kill();
        m_bt_process->waitForFinished();
    }
    QStringList args = {"pair", mac};
    m_bt_process->setProperty("type", p_pair);
    setBusy(true);
    m_bt_process->start("bluetoothctl", args);
}

void Bluetooth::trustDevice(const QString &mac) {
    if (mac.isEmpty()) {
        emit command_err("MAC empty");
        return;
    }
    if (m_bt_process->property("type") == p_trust) {
        m_bt_process->kill();
        m_bt_process->waitForFinished();
    }
    QStringList args = {"trust", mac};
    m_bt_process->setProperty("type", p_trust);
    setBusy(true);
    m_bt_process->start("bluetoothctl", args);
}

void Bluetooth::removeDevice(const QString &mac) {
    if (mac.isEmpty()) {
        emit command_err("MAC empty");
        return;
    }
    // blocking remove (like nmcli delete in wifi)
    QProcess::execute("bluetoothctl", {"remove", mac});
    // refresh list
    listDevices();
}

void Bluetooth::onProcessStarted() {
    int type = m_bt_process->property("type").toInt();
    switch (type) {
    case p_power_on: qDebug() << "BT power on started"; break;
    case p_power_off: qDebug() << "BT power off started"; break;
    case p_list: qDebug() << "BT devices list started"; break;
    case p_scan: qDebug() << "BT scan started"; break;
    case p_connect: qDebug() << "BT connect started"; break;
    case p_disconnect: qDebug() << "BT disconnect started"; break;
    case p_pair: qDebug() << "BT pair started"; break;
    case p_trust: qDebug() << "BT trust started"; break;
    case p_remove: qDebug() << "BT remove started"; break;
    default: break;
    }
}

void Bluetooth::onReadyReadStdOut() {
    QByteArray out = m_bt_process->readAllStandardOutput();
    QString output = QString::fromUtf8(out).trimmed();
    if (!output.isEmpty()) {
        qDebug() << "bt stdout:" << output;
        emit command_out(output);
    }
    m_std_msg = output;

    int type = m_bt_process->property("type").toInt();
    switch (type) {
    case p_list:
    case p_scan:
        // parse lines like: "Device AA:BB:CC:DD:EE:FF DeviceName"
        parseDevicesOutput(output);
        break;
    case p_connect:
        // bluetoothctl usually prints "Connection successful" or "Failed to connect: <reason>"
        if (output.contains("Connection successful") || output.contains("Connection established") || output.contains("Connected: yes")) {
            setConnected_mac(m_bt_process->property("target_mac").toString());
            emit connected(true, output);
        } else if (output.contains("Failed") || output.contains("Error")) {
            emit connected(false, output);
        }
        break;
    case p_disconnect:
        if (output.contains("Successful") || output.contains("Successful disconnected") || output.contains("Disconnected")) {
            emit disconnected(true, output);
            setConnected_mac("");
        } else if (output.contains("Failed") || output.contains("Error")) {
            emit disconnected(false, output);
        }
        break;
    case p_pair:
    case p_trust:
    case p_power_on:
    case p_power_off:
        // just forward to command_out / err
        break;
    default:
        break;
    }
}

void Bluetooth::onReadyReadStdErr() {
    QByteArray err = m_bt_process->readAllStandardError();
    QString error = QString::fromUtf8(err).trimmed();
    if (!error.isEmpty()) {
        qDebug() << "bt stderr:" << error;
        emit command_err(error);
        m_err_msg = error;
    }
}

void Bluetooth::onProcessFinished(int exitCode, QProcess::ExitStatus status) {
    int type = m_bt_process->property("type").toInt();

    switch (type) {
    case p_power_on:
        if (exitCode == 0) {
            setPowered(true);
            qDebug() << "Bluetooth powered on";
        } else {
            qDebug() << "Bluetooth power on failed";
        }
        break;
    case p_power_off:
        if (exitCode == 0) {
            setPowered(false);
            qDebug() << "Bluetooth powered off";
        } else {
            qDebug() << "Bluetooth power off failed";
        }
        break;
    case p_list:
        if (exitCode == 0) {
            qDebug() << "Devices listed";
        } else {
            qDebug() << "Devices list error";
        }
        break;
    case p_connect:
        if (exitCode == 0) {
            // success often already notified in stdout parse
            qDebug() << "connect finished";
        } else {
            emit connected(false, m_std_msg.isEmpty() ? "Connection error" : m_std_msg);
        }
        break;
    case p_disconnect:
        if (exitCode == 0) {
            qDebug() << "disconnect finished";
        } else {
            emit disconnected(false, m_std_msg.isEmpty() ? "Disconnect error" : m_std_msg);
        }
        break;
    default:
        break;
    }

    setBusy(false);
    m_bt_process->setProperty("type", p_non);
    qDebug() << "BT Exit code:" << exitCode << "Status:" << status;
}

void Bluetooth::onProcessError(QProcess::ProcessError err) {
    qDebug() << "BT Process error:" << err;
    emit command_err("BT Process error: " + QString::number(err));
    setBusy(false);
    m_bt_process->setProperty("type", p_non);
}

void Bluetooth::parseDevicesOutput(const QString &output) {
    // output lines: "Device AA:BB:CC:DD:EE:FF Name"
    //We'll construct JSON-like strings per device for QML parsing:
    // {"mac":"AA:...","name":"Name","paired":false,"trusted":false,"connected":false,"rssi":-45}
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    QStringList listEntries;

    for (QString line : lines) {
        line = line.trimmed();
        if (!line.startsWith("Device ")) continue;
        // Device <MAC> <Name...>
        QString rest = line.mid(QString("Device ").length()).trimmed();
        int firstSpace = rest.indexOf(' ');
        if (firstSpace <= 0) continue;
        QString mac = rest.left(firstSpace).trimmed();
        QString name = rest.mid(firstSpace + 1).trimmed();

        // For each device get more info (paired/trusted/connected/rssi) via blocking 'info <mac>'
        QProcess p;
        p.start("bluetoothctl", {"info", mac});
        p.waitForFinished(500);
        QString infoOut = QString::fromUtf8(p.readAllStandardOutput()).trimmed();

        bool paired = infoOut.contains("Paired: yes");
        bool trusted = infoOut.contains("Trusted: yes");
        bool connected = infoOut.contains("Connected: yes");

        int rssi = 0;
        // try to find "RSSI: -xx"
        QRegExp r("RSSI:\\s*([\\-0-9]+)");
        if (r.indexIn(infoOut) != -1) {
            rssi = r.cap(1).toInt();
        }

        // build JSON string (simple)
        QJsonObject obj;
        obj["mac"] = mac;
        obj["name"] = name;
        obj["paired"] = paired;
        obj["trusted"] = trusted;
        obj["connected"] = connected;
        obj["rssi"] = rssi;

        QJsonDocument doc(obj);
        listEntries << QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    }

    m_device_list->setStringList(listEntries);
    emit device_listChanged();
}

void Bluetooth::execBlocking(const QStringList &args) {
    // small helper for blocking commands (used for scan on/off)
    QProcess p;
    p.start("bluetoothctl", args);
    p.waitForFinished(2000);
    QString out = QString::fromUtf8(p.readAllStandardOutput()).trimmed();
    QString err = QString::fromUtf8(p.readAllStandardError()).trimmed();
    if (!out.isEmpty()) emit command_out(out);
    if (!err.isEmpty()) emit command_err(err);
}
