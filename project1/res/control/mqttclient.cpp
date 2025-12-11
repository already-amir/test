#include "mqttclient.h"

Mqttclient::Mqttclient(QObject *parent)
    : QObject{parent}
{}

void Mqttclient::connectToBroker(const QString &host, const QString &token)
{
    client = std::make_unique<mqtt::async_client>(host.toStdString(), "");

    connOpts = std::make_unique<mqtt::connect_options>();
    connOpts->set_user_name(token.toStdString()); // Access Token for ThingsBoard
    connOpts->set_keep_alive_interval(20);
    connOpts->set_clean_session(true);

    callback = std::make_shared<Callback>(this);
    client->set_callback(*callback);

    try {
        client->connect(*connOpts)->wait();
        qDebug() << "Connected to broker!";
    }
    catch (const mqtt::exception &e) {
        qDebug() << "Connection error:" << e.what();
    }
}

void Mqttclient::publishMessage(const QString &topic, const QString &message)
{
    if(client && client->is_connected()) {
        auto msg = mqtt::make_message(topic.toStdString(), message.toStdString());
        client->publish(msg)->wait_for(std::chrono::seconds(10));
        qDebug() << "Message published!";
    } else {
        qDebug() << "Client not connected!";
    }
}

void Mqttclient::subscribeTopic(const QString &topic)
{
    if(client && client->is_connected()) {
        client->subscribe(topic.toStdString(), 1)->wait();
        qDebug() << "Subscribed to topic:" << topic;
    } else {
        qDebug() << "Client not connected!";
    }
}
