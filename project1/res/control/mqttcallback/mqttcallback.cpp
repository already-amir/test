#include "mqttcallback.h"
#include "../mqttclient/mqttclient.h"

#include <QMetaObject>

Mqttcallback::Mqttcallback(Mqttclient *client) :m_client(client)

{}

void Mqttcallback::connection_lost(const std::string &cause)
{
    QString reason = cause.empty() ? "unknown reason" : QString::fromStdString(cause);
    QMetaObject::invokeMethod(
        m_client,
        [this, reason]() {
            emit m_client->disconnected(reason);
        },
        Qt::QueuedConnection);
}

void Mqttcallback::message_arrived(mqtt::const_message_ptr msg)
{
    const QString topic = QString::fromStdString(msg->get_topic());
    const QString payload = QString::fromStdString(msg->to_string());

    QMetaObject::invokeMethod(
        m_client,
        [this, topic, payload]() {
            emit m_client->message_received(topic, payload);
        },
        Qt::QueuedConnection);
}

void Mqttcallback::delivery_complete(mqtt::delivery_token_ptr) {}

