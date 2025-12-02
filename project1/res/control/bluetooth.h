#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QObject>

class Bluetooth : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool bluetooth_enabeld READ bluetooth_enabeld WRITE setBluetooth_enabeld NOTIFY bluetooth_enabeldChanged FINAL)
    Q_PROPERTY(QStringListModel out READ out WRITE setout NOTIFY outChanged FINAL)
    Q_PROPERTY(QString connected_bluetooth READ connected_bluetooth WRITE setConnected_bluetooth NOTIFY connected_bluetoothChanged FINAL)

public:
    explicit Bluetooth(QObject *parent = nullptr);

signals:
};

#endif // BLUETOOTH_H
