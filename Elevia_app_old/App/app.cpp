#include "app.h"

App::App(QObject *parent)
    : QObject{parent}
{
    m_Wifi = new Wifi(this);
    m_Mqtt = new Mqtt(this);


}

void App::enable_wifi()
{
    m_Wifi->enable_wifi();
}

void App::disable_wifi()
{
    m_Wifi->disable_wifi();
}

void App::connect_wifi()
{
    m_Wifi->connect_wifi(m_ssid,m_password);
}

void App::disconnect_wifi()
{
    m_Wifi->disconnect_wifi();
}

void App::scan_wifi()
{
    m_Wifi->scan_wifi();
}

void App::forget_wifi()
{
    m_Wifi->forget_wifi(m_ssid);
}

void App::send_connect_info()
{

}

void App::wifi_auto_connct()
{

}


















//======================================================================================================



QString App::ssid() const
{
    return m_ssid;
}

void App::setSsid(const QString &newSsid)
{
    if (m_ssid == newSsid)
        return;
    m_ssid = newSsid;
    emit ssidChanged();
}

QString App::password() const
{
    return m_password;
}

void App::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}
