#ifndef EVENT_HANDELER_H
#define EVENT_HANDELER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
class Event_handeler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList Cmd_out READ Cmd_out WRITE setCmd_out NOTIFY Cmd_outChanged FINAL)

public:
    explicit Event_handeler(QObject *parent = nullptr);


    Q_INVOKABLE void enable_wifi();
    Q_INVOKABLE void disable_wifi();
    Q_INVOKABLE void scan_wifi();

    QStringList Cmd_out() const;
    void setCmd_out(const QStringList &newCmd_out);

signals:



    void Cmd_outChanged();

private slots:

    void onStarted();
    void onReadyReadStdOut();
    void onReadyReadStdErr();
    void onFinished(int exitCode, QProcess::ExitStatus status);
    void onError(QProcess::ProcessError error);

private:
    QString run_command(QString cmd, QStringList args);
    QProcess process;
    QStringList m_Cmd_out;
};

#endif // EVENT_HANDELER_H
