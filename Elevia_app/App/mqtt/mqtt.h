#ifndef MQTT_H
#define MQTT_H

#include <QObject>

class Mqtt : public QObject
{
    Q_OBJECT
public:
    explicit Mqtt(QObject *parent = nullptr);

signals:
};

#endif // MQTT_H
