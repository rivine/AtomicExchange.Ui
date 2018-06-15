#include "login.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>

Login::Login(QObject *parent) : QObject(parent)
{
}

void Login::loginFinished(int exitCode,  QProcess::ExitStatus exitStatus){
    qInfo() << exitCode;
    qInfo() << exitStatus;
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginNote = rootObject->findChild<QObject*>("loginNote");
    QObject *loginButton = rootObject->findChild<QObject*>("loginButton");


     if(exitCode == 1){        
        loginButton->setProperty("visible", true);        
        loginNote->setProperty("text", "Username / password combination is not correct.");
    }else if(exitCode == 0){
        QObject *scrollView = rootObject->findChild<QObject*>("scrollView");
        QObject *scrollViewLogin = rootObject->findChild<QObject*>("scrollViewLogin");
        scrollViewLogin->setProperty("visible", false);
        scrollView->setProperty("visible", true);        

    }else{
        loginButton->setProperty("visible", true);
        loginNote->setProperty("text", "Something went wrong, please contact support.");
    }

}
void Login::startLoginProcess(const QString username, const QString password){

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginButton = rootObject->findChild<QObject*>("loginButton");
    QObject *loginNote = rootObject->findChild<QObject*>("loginNote");
    loginButton->setProperty("visible", false);


    //QString scriptFile =  QCoreApplication::applicationDirPath() + "/scripts/iyo/login.sh";
    QStringList commandArguments = QStringList() << username << password;
    loginProcess.start("dist/scripts/iyo/login.php", commandArguments);
    //loginProcess.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");

    QObject::connect(&loginProcess , SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(loginFinished(int, QProcess::ExitStatus)));
    loginNote->setProperty("visible", true);
    loginNote->setProperty("text", "You will receive a text message to login.");
}
