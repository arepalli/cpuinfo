/****************************************************************************
**
**
** This file is a part of the Qt Cpu Info project
**
**
****************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "cpuinfomodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CpuInfoModel>("Backend", 1, 0, "CpuInfoModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/cpuinfo.qml")));

    return app.exec();
}
