//connmanmanager.h
#ifndef CONNMANMANAGER_H
#define CONNMANMANAGER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QTimer>

class ConnmanManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList wifiList READ wifiList NOTIFY wifiListChanged)

public:
    explicit ConnmanManager(QObject *parent = nullptr);

    Q_INVOKABLE void enableWifi();
    Q_INVOKABLE void disableWifi();
    Q_INVOKABLE void scanWifi();




    QStringList wifiList() const;

signals:
    void wifiListChanged();

private:
    QStringList m_wifiList;
    QString runCommand(QString program, QStringList args);
};

#endif
