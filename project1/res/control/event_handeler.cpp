#include "event_handeler.h"

Event_handeler::Event_handeler(QObject *parent)
    : QObject{parent}
{
    connect(&process,&QProcess::started,this,&Event_handeler::onStarted);
    connect(&process,&QProcess::readyReadStandardOutput,this,&Event_handeler::onReadyReadStdOut);
    connect(&process,&QProcess::readyReadStandardError,this,&Event_handeler::onReadyReadStdErr);
    connect(&process,&QProcess::errorOccurred,this,&Event_handeler::onError);
    connect(&process,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &Event_handeler::onFinished);

}
//....................
QString Event_handeler::run_command(QString cmd, QStringList args)
{
    process.start(cmd,args);
    if(!process.waitForStarted(2000)){
        qDebug()<<"failed to start: "<<cmd;
        return "";
    }

    if(process.waitForFinished(5000)){
        qDebug()<<"prosess timeout: "<<cmd;
        process.kill();
        return "";
    }

    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();
    if(!error.isEmpty())
        qDebug() << "Error:" << error<<Qt::endl;

    return output;
}
//............
void Event_handeler::enable_wifi()
{
    QString result = run_command("netsh", {"interface", "set", "interface", "name=\"Wi-Fi\"", "admin=enabled"});
    qDebug() << result;
}

void Event_handeler::disable_wifi()
{
    QString result = run_command("netsh", {"interface", "set", "interface", "name=\"Wi-Fi\"", "admin=disabled"});
    qDebug() << result;
}

void Event_handeler::scan_wifi()
{
    QString result = run_command("netsh", {"wlan", "show", "networks"});
    qDebug() << result;
}
//..............................
void Event_handeler::onStarted()
{
    qDebug() << "Process started.";

}

void Event_handeler::onReadyReadStdOut()
{
    QByteArray out = process.readAllStandardOutput();
    qDebug() << "STDOUT:" << out;

}

void Event_handeler::onReadyReadStdErr()
{
    QByteArray err = process.readAllStandardError();
    qDebug() << "STDERR:" << err;
}

void Event_handeler::onFinished(int exitCode, QProcess::ExitStatus status)
{
    qDebug() << "Process finished. Exit code:" << exitCode << "Status:" << status;
}

void Event_handeler::onError(QProcess::ProcessError error)
{
    qDebug() << "Process error:" << error;
}

//.........................
QStringList Event_handeler::Cmd_out() const
{
    return m_Cmd_out;
}

void Event_handeler::setCmd_out(const QStringList &newCmd_out)
{
    if (m_Cmd_out == newCmd_out)
        return;
    m_Cmd_out = newCmd_out;
    emit Cmd_outChanged();
}
