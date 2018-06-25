#include "login.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>

Login::Login(QObject *parent) : QObject(parent)
{
    userName = "";
}

void Login::loginFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qInfo() << exitCode;
    qInfo() << exitStatus;
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *loginButton = rootObject->findChild<QObject *>("loginButton");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");


    if(loginNote == nullptr || loginButton == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
        userNameHeader == nullptr || userImage == nullptr){
            qInfo() << "nullpointer in loginFinished";
            return;
    }

    if (exitCode == 1)
    {
        loginButton->setProperty("visible", true);
        loginNote->setProperty("text", "Username / password is not correct.");
    }
    else if (exitCode == 0)
    {
        userNameHeader->setProperty("text", userName);
        scrollViewLogin->setProperty("visible", false);
        scrollView->setProperty("visible", true);
        userNameHeader->setProperty("visible", true);
        userImage->setProperty("visible", true);
    }
    else
    {
        loginButton->setProperty("visible", true);
        loginNote->setProperty("text", "Something went wrong, please contact support.");
    }
}
void Login::signOut()
{
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *loginButton = rootObject->findChild<QObject *>("loginButton");
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *usernameInput = rootObject->findChild<QObject *>("usernameInput");
    QObject *passwordInput = rootObject->findChild<QObject *>("passwordInput");
    QObject *footerPane = rootObject->findChild<QObject *>("footerPane");

    if(userNameHeader == nullptr || userImage == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
        loginButton == nullptr || loginNote == nullptr || usernameInput == nullptr || passwordInput == nullptr || footerPane == nullptr){
            qInfo() << "nullpointer in signout";
            return;
    }

    userNameHeader->setProperty("visible", false);
    userImage->setProperty("visible", false);
    scrollViewLogin->setProperty("visible", true);
    scrollView->setProperty("visible", false);
    loginButton->setProperty("visible", true);
    loginNote->setProperty("visible", false);
    footerPane->setProperty("visible", false);
    usernameInput->setProperty("text", "");
    passwordInput->setProperty("text", "");
}

void Login::startLoginProcess(const QString userN, const QString password)
{
    userName = userN;
    QString validUser = qgetenv("VALIDUSER");
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginButton = rootObject->findChild<QObject *>("loginButton");
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");

    if(loginButton == nullptr || loginNote == nullptr){
        qInfo() << "nullpointer in startLoginProgress";
    }
    
        loginButton->setProperty("visible", false);
    if (validUser != "" && validUser != QString(userN))
    {
        qInfo() << "Invalid user";
        loginNote->setProperty("visible", true);
        loginNote->setProperty("text", "Invalid user.");
             loginButton->setProperty("visible", true);
        return;
    } else{
        loginNote->setProperty("visible", true);
        loginNote->setProperty("text", "You will receive a text message to login.");
    }
    //QString scriptFile =  QCoreApplication::applicationDirPath() + "/scripts/iyo/login.sh";
    QStringList commandArguments = QStringList() << userN << password;
    loginProcess.start("dist/scripts/iyo/login.php", commandArguments);
    //loginProcess.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");

    QObject::connect(&loginProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(loginFinished(int, QProcess::ExitStatus)));

}