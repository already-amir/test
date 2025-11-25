//main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include "res/control/event_handeler.h"
#include "res/control/wifi.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    Event_handeler handler;
    Wifi wifi_handel;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("handler",&handler);
    engine.rootContext()->setContextProperty("wifi",&wifi_handel);

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
