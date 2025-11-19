#include "sys.h"

Sys::Sys(QObject *parent)
    : QObject{parent}
{}

bool Sys::lock() const
{
    return m_lock;
}

void Sys::setlock(bool newLock)
{
    if (m_lock == newLock)
        return;
    m_lock = newLock;
    emit lockChanged();
}

int Sys::temp() const
{
    return m_temp;
}

void Sys::settemp(int newTemp)
{
    if (m_temp == newTemp)
        return;
    m_temp = newTemp;
    emit tempChanged();
}

QString Sys::usr() const
{
    return m_usr;
}

void Sys::setusr(const QString &newUsr)
{
    if (m_usr == newUsr)
        return;
    m_usr = newUsr;
    emit usrChanged();
}

int Sys::test() const
{
    return m_test;
}

void Sys::settest(int newTest)
{
    if (m_test == newTest)
        return;
    m_test = newTest;
    emit testChanged();
}
