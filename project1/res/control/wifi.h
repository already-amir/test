//wifi.h
#ifndef WIFI_H
#define WIFI_H

#include <QObject>
#include <QStringListModel>
#include <QProcess>
#include <QDebug>
#include<QTimer>

class Wifi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString password READ password WRITE setpassword NOTIFY passwordChanged FINAL)
    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged FINAL)
    Q_PROPERTY(bool wifi_enabeled READ wifi_enabeled WRITE setwifi_enabeled NOTIFY wifi_enabeledChanged FINAL)

    Q_PROPERTY(QStringListModel* wifi_list READ wifi_list WRITE setwifi_list NOTIFY wifi_listChanged FINAL)

public:
    explicit Wifi(QObject *parent = nullptr);

    QStringListModel *wifi_list() const;
    void setwifi_list(QStringListModel *newWifi_list);

    Q_INVOKABLE void enable_wifi();
    Q_INVOKABLE void disable_wifi();
    Q_INVOKABLE void scan_wifi();
    Q_INVOKABLE void connect_wifi();
    Q_INVOKABLE void pingGoogle();

    bool wifi_enabeled() const;
    void setwifi_enabeled(bool newWifi_enabeled);

    QString password() const;
    void setpassword(const QString &newPassword);

    QString ssid() const;
    void setSsid(const QString &newSsid);

signals:

    void wifi_listChanged();
    void wifi_enabeledChanged();
    void passwordChanged();
    void ssidChanged();

    void command_out(const QString& output);
    void command_err(const QString& error);
    void connected();
    void connectionFailed(QString reason);
    void pingResult(bool success, QString output);

private slots:

    void onProcessStarted(int id);
    void onReadyReadStdOut(int id);
    void onReadyReadStdErr(int id);
    void onProcessFinished(int id,int exitCode, QProcess::ExitStatus status);
    void onProcessError(int id,QProcess::ProcessError error);

private:
    QStringListModel *m_wifi_list = nullptr;
    QProcess* m_wifi_process;
    bool m_wifi_enabeled;
    bool m_waiting_for_scan;
    QString m_password;
    QString m_ssid;
    int m_id;
    enum WifiProcessType {
        p_non,
        p_wifi_enable,
        p_wifi_disable,
        p_wifi_scan,
        p_wifi_connect,
        p_wifi_ping
    };

};

#endif // WIFI_H
