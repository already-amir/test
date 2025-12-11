#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <mqtt/async_client.h>

class Mqttclient : public QObject
{
    Q_OBJECT
public:
    explicit Mqttclient(QObject *parent = nullptr);
    Q_INVOKABLE void connectToBroker(const QString &host, const QString &token);
    Q_INVOKABLE void publishMessage(const QString &topic, const QString &message);
    Q_INVOKABLE void subscribeTopic(const QString &topic);

signals:
    void messageReceived(const QString &topic, const QString &message);
private:
    std::unique_ptr<mqtt::async_client> client;
    std::unique_ptr<mqtt::connect_options> connOpts;

    class Callback : public virtual mqtt::callback
    {
    public:
        Callback(Mqttclient *parent) : parent(parent) {}
        void message_arrived(mqtt::const_message_ptr msg) override {
            emit parent->messageReceived(QString::fromStdString(msg->get_topic()),
                                         QString::fromStdString(msg->to_string()));
        }
    private:
        Mqttclient *parent;
    };

    std::shared_ptr<Callback> callback;
};

#endif // MQTTCLIENT_H
