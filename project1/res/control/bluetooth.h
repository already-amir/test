#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>
#include <QStringListModel>
#include <QProcess>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>

class Bluetooth : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged FINAL)
    Q_PROPERTY(QStringListModel* device_list READ device_list WRITE setDevice_list NOTIFY device_listChanged FINAL)
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged FINAL)
    Q_PROPERTY(QString connected_mac READ connected_mac WRITE setConnected_mac NOTIFY connected_macChanged FINAL)
    Q_PROPERTY(QString err_msg READ err_msg WRITE setErr_msg NOTIFY err_msgChanged FINAL)

public:
    explicit Bluetooth(QObject *parent = nullptr);

    // actions
    Q_INVOKABLE void powerOn();
    Q_INVOKABLE void powerOff();
    Q_INVOKABLE void startScan();         // scan on -> wait -> devices -> scan off
    Q_INVOKABLE void listDevices();       // just call 'bluetoothctl devices' and parse
    Q_INVOKABLE void connectDevice(const QString &mac);
    Q_INVOKABLE void disconnectDevice(const QString &mac);
    Q_INVOKABLE void pairDevice(const QString &mac);
    Q_INVOKABLE void trustDevice(const QString &mac);
    Q_INVOKABLE void removeDevice(const QString &mac);

    // properties
    QStringListModel* device_list() const;
    void setDevice_list(QStringListModel* newList);

    bool powered() const;
    void setPowered(bool p);

    bool busy() const;
    void setBusy(bool b);

    QString connected_mac() const;
    void setConnected_mac(const QString &mac);

    QString err_msg() const;
    void setErr_msg(const QString &e);

signals:
    void device_listChanged();
    void poweredChanged();
    void busyChanged();
    void connected_macChanged();
    void err_msgChanged();

    void command_out(const QString &output);
    void command_err(const QString &error);

    void connected(bool status, QString reason = "");
    void disconnected(bool status, QString reason = "");
    void scanned(); // emitted after scan finishes

private slots:
    void onProcessStarted();
    void onReadyReadStdOut();
    void onReadyReadStdErr();
    void onProcessFinished(int exitCode, QProcess::ExitStatus status);
    void onProcessError(QProcess::ProcessError err);

private:
    QStringListModel *m_device_list = nullptr;
    QProcess *m_bt_process = nullptr;
    bool m_powered = false;
    bool m_busy = false;
    QString m_connected_mac;
    QString m_err_msg;
    QString m_std_msg; // store last stdout

    enum BtProcessType {
        p_non,
        p_power_on,
        p_power_off,
        p_scan,
        p_list,
        p_connect,
        p_disconnect,
        p_pair,
        p_trust,
        p_remove
    };

    // helpers
    void parseDevicesOutput(const QString &output); // parse "Device <MAC> <Name>"
    QJsonObject parseInfoBlock(const QString &output); // if needed for details
    void execBlocking(const QStringList &args); // convenience wrapper to QProcess::execute
};

#endif // BLUETOOTH_H
