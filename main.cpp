#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "todolist.h"
#include "todomodel.h"
#include "ooList.h"
#include "ooModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ToDoModel>("ToDo", 1, 0, "ToDoModel");
    qmlRegisterUncreatableType<ToDoList>("ToDo", 1, 0, "ToDoList",
        QStringLiteral("ToDoList should not be created in QML"));

    ToDoList toDoList;
    
    qmlRegisterType<OoModel>("Oo", 1, 0, "OoModel");
    qmlRegisterUncreatableType<OoList>("Oo", 1, 0, "OoList",
        QStringLiteral("OoList should not be created in QML"));
    OoList ooList;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"), &toDoList);

    engine.rootContext()->setContextProperty(QStringLiteral("ooList"), &ooList);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
