#include "mqttclient.h"
#include <iostream>

// ------------------ CALLBACK CLASS ------------------
class MqttClient::Callback :
                             public virtual mqtt::callback,
                             public virtual mqtt::iaction_listener
{
public:
    MqttClient *q;

    Callback(MqttClient *parent) : q(parent) {}

    void connected(const std::string&) override {
        q->m_connected = true;
        emit q->connectedChanged();
    }

    void connection_lost(const std::string&) override {
        q->m_connected = false;
        emit q->connectedChanged();
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
        emit q->messageReceived(
            QString::fromStdString(msg->get_topic()),
            QString::fromStdString(msg->to_string())
            );
    }

    void on_success(const mqtt::token&) override {}
    void on_failure(const mqtt::token&) override {}
};

// ------------------ MAIN CLASS ------------------

MqttClient::MqttClient(QObject *parent)
    : QObject(parent),
    m_client(nullptr),
    m_connected(false),
    m_callback(nullptr)
{
}

void MqttClient::connectToBroker(const QString &host, const QString &token)
{
    if (m_client)
        delete m_client;

    m_client = new mqtt::async_client(host.toStdString(), "qt-client");

    m_callback = new Callback(this);
    m_client->set_callback(*m_callback);

    mqtt::connect_options opts;
    opts.set_clean_session(true);
    opts.set_user_name(token.toStdString());
    opts.set_password("");

    try {
        m_client->connect(opts)->wait();
    } catch (const mqtt::exception &e) {
        qWarning() << "MQTT connect error:" << e.what();
    }
}

void MqttClient::disconnectFromBroker()
{
    if (!m_client) return;

    try {
        m_client->disconnect()->wait();
    } catch (...) {}

    m_connected = false;
    emit connectedChanged();
}

void MqttClient::subscribeTopic(const QString &topic)
{
    if (!m_client) return;

    try {
        m_client->subscribe(topic.toStdString(), 1)->wait();
    } catch (...) {}
}

void MqttClient::publishMessage(const QString &topic, const QString &message)
{
    if (!m_client) return;

    auto msg = mqtt::make_message(topic.toStdString(), message.toStdString());
    msg->set_qos(1);
    try {
        m_client->publish(msg)->wait();
    } catch (...) {}
}
