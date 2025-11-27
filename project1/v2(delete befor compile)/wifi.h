#ifndef WIFI_H
#define WIFI_H

#include <QObject>
#include <QProcess>
#include <QQueue>
#include <QStringListModel>
#include <QTimer>

class Wifi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool wifiEnabled READ wifiEnabled NOTIFY wifiEnabledChanged)
    Q_PROPERTY(QStringListModel* networks READ networks NOTIFY networksChanged)

public:
    explicit Wifi(QObject *parent = nullptr);

    Q_INVOKABLE void enable();
    Q_INVOKABLE void scan();
    Q_INVOKABLE void connectTo(QString ssid, QString password);
    Q_INVOKABLE void disconnectWifi();

    bool wifiEnabled() const { return m_wifiEnabled; }
    QStringListModel* networks() { return m_networks; }

signals:
    void wifiEnabledChanged();
    void networksChanged();
    void log(QString text);

private slots:
    void onProcessStarted();
    void onProcessFinished(int exitCode, QProcess::ExitStatus status);
    void onProcessError(QProcess::ProcessError error);

    void handleTimeout();

private:
    enum WifiCommand {
        CmdNone,
        CmdEnable,
        CmdScan,
        CmdConnect,
        CmdDisconnect
    };

    struct Command {
        WifiCommand type;
        QString ssid;
        QString password;
    };

    void enqueueCommand(Command cmd);
    void startNextCommand();
    void setWifiEnabled(bool en);

    void parseScanResult(QString output);

private:
    QProcess *m_process;
    QTimer *m_timeoutTimer;
    QQueue<Command> m_queue;
    Command m_currentCommand;

    QStringListModel *m_networks;
    bool m_wifiEnabled;
};

#endif // WIFI_H
