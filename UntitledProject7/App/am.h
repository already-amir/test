#ifndef AM_H
#define AM_H

#include <QObject>

class Am : public QObject
{
    Q_OBJECT
public:
    explicit Am(QObject *parent = nullptr);
    Q_INVOKABLE void say_hello();

signals:
};

#endif // AM_H
