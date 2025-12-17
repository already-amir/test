#include "mqttclient.h"
#include"../mqttcallback/mqttcallback.h"
#include <QDebug>
Mqttclient::Mqttclient(QObject *parent)
    : QObject{parent}
{
    m_reconnect_timer.setInterval(1000);
    connect(&m_reconnect_timer, &QTimer::timeout,
            this, &Mqttclient::try_reconnect);

    connect(this, &Mqttclient::disconnected, this, [this](const QString &reason){
        qDebug() << "mqtt disconnected:" << reason;
        if (!m_reconnect_timer.isActive())
            m_reconnect_timer.start();
    });

    load_config();
    connect_to_broker();


}

void Mqttclient::connect_to_broker()
{
    m_client = std::make_unique<mqtt::async_client>(m_host.toStdString(), "");

    m_conn_opts = std::make_unique<mqtt::connect_options>();
    m_conn_opts->set_user_name(m_token.toStdString());
    m_conn_opts->set_keep_alive_interval(20);
    m_conn_opts->set_clean_session(true);

    m_callback = std::make_shared<Mqttcallback>(this);
    m_client->set_callback(*m_callback);

    try {
        m_client->connect(*m_conn_opts)->wait();
        emit connected();
        qDebug() << "connected to broker";
    } catch (const mqtt::exception &e) {
        qDebug() << "connection error:" << e.what();
        m_reconnect_timer.start();
    }
}

void Mqttclient::publish_message(const QString &topic, const QString &message)
{
    if (m_client && m_client->is_connected()) {
        auto msg = mqtt::make_message(
            topic.toStdString(),
            message.toStdString()
            );
        m_client->publish(msg);
    }
}

void Mqttclient::subscribe_topic(const QString &topic)
{
    if (m_client && m_client->is_connected()) {
        m_client->subscribe(topic.toStdString(), 1);
    }
}

void Mqttclient::try_reconnect()
{
    if (!m_client || m_client->is_connected())
        return;

    try {
        qDebug() << "trying to reconnect mqtt...";
        m_client->connect(*m_conn_opts)->wait();
        qDebug() << "connected to broker";
        emit connected();
        m_reconnect_timer.stop();
    } catch (...) {
        qDebug() << "Reconnect failed";
    }
}

void Mqttclient::load_config()
{
    QString path = ":/res/control/config.json";
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "cannot open config file:" << path;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parse_error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parse_error);
    if(parse_error.error != QJsonParseError::NoError) {
        qDebug() << "json parse error:" << parse_error.errorString();
        return;
    }

    QJsonObject root = doc.object();
    QJsonObject mqtt = root.value("mqtt").toObject();

    m_host  = mqtt.value("host").toString("defualt server here");
    m_token = mqtt.value("token").toString("defualt token here");
}

void Mqttclient::save_config(const QString &host, const QString &token)
{
    QJsonObject mqtt;
    mqtt["host"] = host;
    mqtt["token"] = token;

    QJsonObject root;
    root["mqtt"] = mqtt;

    QJsonDocument doc(root);

    QFile file(":/res/control/config.json");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "cannot open config file for writing";
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    m_host  = host;
    m_token = token;
    qDebug() << "config saved";
}


