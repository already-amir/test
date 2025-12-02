#ifndef BLUE_H
#define BLUE_H

#include <QObject>
#include <QStringListModel>
#include <QProcess>
class Blue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString connected_blue READ connected_blue WRITE setconnected_blue NOTIFY connected_blueChanged FINAL)
    Q_PROPERTY(bool blue_enabeld READ blue_enabeld WRITE setBlue_enabeld NOTIFY blue_enabeldChanged FINAL)
    Q_PROPERTY(QString err_msg READ err_msg WRITE seterr_msg NOTIFY err_msgChanged FINAL)
    Q_PROPERTY(QStringListModel* blue_list READ blue_list WRITE setBlue_list NOTIFY blue_listChanged FINAL)
public:
    explicit Blue(QObject *parent = nullptr);

    Q_INVOKABLE void powerOn();
    Q_INVOKABLE void powerOff();
    Q_INVOKABLE void startScan();
    Q_INVOKABLE void listDevices();
    Q_INVOKABLE void connectDevice(const QString &mac);
    Q_INVOKABLE void disconnectDevice(const QString &mac);
    Q_INVOKABLE void pairDevice(const QString &mac);
    Q_INVOKABLE void trustDevice(const QString &mac);
    Q_INVOKABLE void removeDevice(const QString &mac);

    QStringListModel *blue_list() const;
    void setBlue_list(QStringListModel *newBlue_list);

    QString connected_blue() const;
    void setconnected_blue(const QString &newConnected_blue);

    bool blue_enabeld() const;
    void setBlue_enabeld(bool newBlue_enabeld);

    QString err_msg() const;
    void seterr_msg(const QString &newErr_msg);

signals:
    void blue_listChanged();
    void connected_blueChanged();

    void blue_enabeldChanged();

    void err_msgChanged();

    void command_out(const QString &output);
    void command_err(const QString &error);

    void connected(bool status, QString reason = "");
    void disconnected(bool status, QString reason = "");
    void scanned();

private slots:
    void onProcessStarted();
    void onReadyReadStdOut();
    void onReadyReadStdErr();
    void onProcessFinished(int exitCode, QProcess::ExitStatus status);
    void onProcessError(QProcess::ProcessError err);


private:
    QStringListModel *m_blue_list = nullptr;
    QProcess *m_bt_process = nullptr;
    QString m_connected_blue;
    bool m_blue_enabeld=false;
    QString m_err_msg;
    QString m_std_msg;
    enum bt_type {
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
};

#endif // BLUE_H
