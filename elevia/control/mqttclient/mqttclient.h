//mqttclient.h
#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <mqtt/async_client.h>
#include <QTimer>
#include<QDebug>
class Mqttcallback;

class Mqttclient : public QObject
{
    Q_OBJECT
public:
    explicit Mqttclient(QObject *parent = nullptr);
    Q_INVOKABLE void connect_to_broker();
    Q_INVOKABLE void publish_message(const QString &topic, const QString &message);
    Q_INVOKABLE void subscribe_topic(const QString &topic);


signals:
    void message_received(const QString &topic, const QString &message);
    void connected();
    void disconnected(const QString &reason);

private slots:
    void try_reconnect();

private:
    void load_config();
    void save_config(const QString &host, const QString &token);


private:
    std::unique_ptr<mqtt::async_client> m_client;
    std::unique_ptr<mqtt::connect_options> m_conn_opts;
    std::shared_ptr<Mqttcallback> m_callback;


    QTimer m_reconnect_timer;
    QString m_host;
    QString m_token;
};

#endif // MQTTCLIENT_H
