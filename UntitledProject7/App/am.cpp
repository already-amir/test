#include "am.h"
#include<QDebug>

Am::Am(QObject *parent)
    : QObject{parent}
{}

void Am::say_hello()
{
    qDebug()<<"hi from cpp file ";
}
