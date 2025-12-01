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

    Q_PROPERTY(bool busy READ busy WRITE setbusy NOTIFY busyChanged FINAL)
    Q_PROPERTY(QString password READ password WRITE setpassword NOTIFY passwordChanged FINAL)
    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged FINAL)
    Q_PROPERTY(bool wifi_enabeled READ wifi_enabeled WRITE setwifi_enabeled NOTIFY wifi_enabeledChanged FINAL)
    Q_PROPERTY(QStringListModel* wifi_list READ wifi_list WRITE setwifi_list NOTIFY wifi_listChanged FINAL)
    Q_PROPERTY(QString connected_ssid READ connected_ssid WRITE setconnected_ssid NOTIFY connected_ssidChanged FINAL)



public:
    explicit Wifi(QObject *parent = nullptr);


    Q_INVOKABLE void enable_wifi();
    Q_INVOKABLE void disable_wifi();
    Q_INVOKABLE void scan_wifi();
    Q_INVOKABLE void connect_wifi();
    Q_INVOKABLE void pingGoogle();
    Q_INVOKABLE void disconnect();

    void check_we();

    QStringListModel *wifi_list() const;
    void setwifi_list(QStringListModel *newWifi_list);

    bool wifi_enabeled() const;
    void setwifi_enabeled(bool newWifi_enabeled);

    QString password() const;
    void setpassword(const QString &newPassword);

    QString ssid() const;
    void setSsid(const QString &newSsid);

    bool busy() const;
    void setbusy(bool newBusy);

    QString err_msg() const;
    void seterr_msg(const QString &newErr_msg);

    QString connected_ssid() const;
    void setconnected_ssid(const QString &newConnected_ssid);

signals:

    void wifi_listChanged();
    void wifi_enabeledChanged();
    void passwordChanged();
    void ssidChanged();

    void command_out(const QString& output);
    void command_err(const QString& error);


    void connected(bool status,QString reason="");
    void ping_out(bool status,QString reason="");


    void busyChanged();



    void err_msgChanged();

    void connected_ssidChanged();


    void disconnectsig(bool status,QString reason="");

private slots:

    void onProcessStarted( );
    void onReadyReadStdOut( );
    void onReadyReadStdErr( );
    void onProcessFinished( int exitCode, QProcess::ExitStatus status);
    void onProcessError(QProcess::ProcessError error);



private:
    QStringListModel *m_wifi_list = nullptr;
    QProcess* m_wifi_process;
    bool m_wifi_enabeled;
    QString m_password;
    QString m_ssid;

    enum WifiProcessType {
        p_non,
        p_wifi_enable,
        p_wifi_disable,
        p_wifi_scan,
        p_wifi_connect,
        p_wifi_ping,
        p_wifi_disconnect
    };

    bool m_busy;
    QString m_err_msg;
    QString m_std_msg;
    QString m_connected_ssid;
};

#endif // WIFI_H
