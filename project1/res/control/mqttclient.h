#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QString>
#include <mqtt/async_client.h>

class MqttClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)

public:
    explicit MqttClient(QObject *parent = nullptr);

    Q_INVOKABLE void connectToBroker(const QString &host, const QString &token);
    Q_INVOKABLE void disconnectFromBroker();
    Q_INVOKABLE void subscribeTopic(const QString &topic);
    Q_INVOKABLE void publishMessage(const QString &topic, const QString &message);

    bool isConnected() const { return m_connected; }

signals:
    void connectedChanged();
    void messageReceived(QString topic, QString payload);

private:
    mqtt::async_client *m_client;
    bool m_connected;

    // callback handler
    class Callback;
    Callback *m_callback;
};

#endif // MQTTCLIENT_H
