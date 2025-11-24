#ifndef WIFI_H
#define WIFI_H

#include <QObject>
#include <QStringListModel>
#include <QProcess>
#include <QDebug>

class Wifi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringListModel* wifi_list READ wifi_list WRITE setwifi_list NOTIFY wifi_listChanged FINAL)

public:
    explicit Wifi(QObject *parent = nullptr);

    QStringListModel *wifi_list() const;
    void setwifi_list(QStringListModel *newWifi_list);

    Q_INVOKABLE void enable_wifi();
    Q_INVOKABLE void disable_wifi();
    Q_INVOKABLE void scan_wifi();
    Q_INVOKABLE void connect_wifi();

signals:

    void wifi_listChanged();
    void command_out(const QString& output);
    void command_err(const QString& error);

private slots:

    void onProcessStarted();
    void onReadyReadStdOut();
    void onReadyReadStdErr();
    void onProcessFinished(int exitCode, QProcess::ExitStatus status);
    void onProcessError(QProcess::ProcessError error);

private:
    QStringListModel *m_wifi_list = nullptr;
    QProcess* m_wifi_process;
};

#endif // WIFI_H
