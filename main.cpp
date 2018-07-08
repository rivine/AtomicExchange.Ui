#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QDebug>

#include "ooList.h"
#include "ohList.h"
#include "ooModel.h"
#include "login.h"
#include "newOrder.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
   
    qmlRegisterType<OoModel>("Oo", 1, 0, "OoModel");
    qmlRegisterUncreatableType<OoList>("Oo", 1, 0, "OoList",
        QStringLiteral("OoList should not be created in QML"));
    OoList ooList;


    qmlRegisterUncreatableType<OhList>("Oo", 1, 0, "OhList",
         QStringLiteral("OoList should not be created in QML"));

    OhList ohList;

    Login login;
    NewOrder newOrder;
    QObject::connect(&login, SIGNAL(signOutEvent()), &newOrder, SLOT(resetData()));
    

    QQmlApplicationEngine engine;
    ApplicationContext::Instance().setEngine(&engine);
    engine.rootContext()->setContextProperty(QStringLiteral("ooList"), &ooList);
    engine.rootContext()->setContextProperty(QStringLiteral("ohList"), &ohList);

    engine.rootContext()->setContextProperty(QStringLiteral("loginService"), &login);
    engine.rootContext()->setContextProperty(QStringLiteral("newOrderService"), &newOrder);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
