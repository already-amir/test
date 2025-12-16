#ifndef MQTTCALLBACK_H
#define MQTTCALLBACK_H
#include <mqtt/async_client.h>
class Mqttclient;
class Mqttcallback :public virtual mqtt::callback
{
public:


    explicit Mqttcallback(Mqttclient *client);
    void connection_lost(const std::string &cause) override;
    void message_arrived(mqtt::const_message_ptr msg) override;
    void delivery_complete(mqtt::delivery_token_ptr) override;

private:
    Mqttclient *m_client;
};

#endif // MQTTCALLBACK_H
