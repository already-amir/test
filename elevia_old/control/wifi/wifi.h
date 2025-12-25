#ifndef WIFI_H
#define WIFI_H

#include <QObject>

class Wifi : public QObject
{
    Q_OBJECT



public:
    explicit Wifi(QObject *parent = nullptr);


signals:
};

#endif // WIFI_H
