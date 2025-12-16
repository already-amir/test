//main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>

#include "control/wifi/wifi.h"



#include "control/mqttclient/mqttclient.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Wifi wifi_handel;

    Mqttclient client;


    QObject::connect(&wifi_handel, &Wifi::wifiScanReady,&client, &Mqttclient::publish_message, Qt::QueuedConnection);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("wifi",&wifi_handel);

    engine.rootContext()->setContextProperty("mqttClient", &client);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
