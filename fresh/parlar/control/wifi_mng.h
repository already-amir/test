//wifi_mng.h

#ifndef WIFI_MNG_H
#define WIFI_MNG_H

#include <QObject>

class Wifi_mng : public QObject
{
    Q_OBJECT
public:
    explicit Wifi_mng(QObject *parent = nullptr);
    Q_INVOKABLE void enableWifi(bool enable);
    Q_INVOKABLE void scanNetworks();

signals:
    void networksFound(const QStringList &networks);
};

#endif // WIFI_MNG_H
