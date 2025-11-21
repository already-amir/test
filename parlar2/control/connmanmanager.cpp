//connmanmanager.cpp
#include "connmanmanager.h"
#include <QDebug>

ConnmanManager::ConnmanManager(QObject *parent)
    : QObject(parent)
{
}

QString ConnmanManager::runCommand(QString program, QStringList args)
{
    QProcess process;
    process.start(program, args);

    if (!process.waitForStarted(3000)) { // حداکثر 3 ثانیه
        qDebug() << "Failed to start" << program;
        return "";
    }

    if (!process.waitForFinished(5000)) { // حداکثر 5 ثانیه
        qDebug() << "Process timeout:" << program;
        process.kill();
        return "";
    }

    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    if(!error.isEmpty())
        qDebug() << "Error:" << error;

    return output;
}

void ConnmanManager::enableWifi()
{
    qDebug() << "Enabling WiFi...";
    runCommand("/usr/bin/connmanctl", {"enable", "wifi"});
}

void ConnmanManager::disableWifi()
{
    qDebug() << "Disabling WiFi...";
    runCommand("/usr/bin/connmanctl", {"disable", "wifi"});
}

void ConnmanManager::scanWifi()
{
    qDebug() << "Scanning WiFi...";

    // ابتدا scan
    runCommand("/usr/bin/connmanctl", {"scan", "wifi"});

    // کمی صبر کن تا scan کامل بشه و بعد services بگیر
    QTimer::singleShot(2000, [=]() {
        QString output = runCommand("/usr/bin/connmanctl", {"services"});
        QStringList lines = output.split("\n", Qt::SkipEmptyParts);

        m_wifiList.clear();

        for (QString line : lines) {
            if (line.contains("wifi")) {
                // trim کردن و فقط اسم شبکه رو جدا کن
                QString trimmed = line.trimmed();
                // می‌تونی فقط ssid رو جدا کنی با split("_") اگه خواستی
                m_wifiList.append(trimmed);
            }
        }

        emit wifiListChanged();
        qDebug() << "WiFi List:" << m_wifiList;
    });
}


QStringList ConnmanManager::wifiList() const
{
    return m_wifiList;
}
