//main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>

#include "res/control/wifi.h"
#include "res/control/bluetooth.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Wifi wifi_handel;
    Bluetooth bluetooth;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("wifi",&wifi_handel);
    engine.rootContext()->setContextProperty("bluetooth",&bluetooth);

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
