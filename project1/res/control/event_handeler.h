#ifndef EVENT_HANDELER_H
#define EVENT_HANDELER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include<QStringListModel>
class Event_handeler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringListModel*  NNetworksModel READ NNetworksModel WRITE setNNetworksModel NOTIFY NNetworksModelChanged FINAL)

public:
    explicit Event_handeler(QObject *parent = nullptr);

    Q_INVOKABLE void enable_wifi();
    Q_INVOKABLE void disable_wifi();
    Q_INVOKABLE void scan_wifi();
    Q_INVOKABLE void connect_wifi(const QString &ssid, const QString &password);

    QStringListModel *NNetworksModel() const;
    void setNNetworksModel(QStringListModel *newNNetworksModel);

signals:

    void NNetworksModelChanged();

private:

    QString run_command(QString cmd, QStringList args);
    QStringListModel *m_NNetworksModel = nullptr;
};

#endif // EVENT_HANDELER_H
