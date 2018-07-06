#include "login.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include "newOrder.h"

Login::Login(QObject *parent) : QObject(parent)
{
    setUsername("");
    setPassword("");
    connect(this, SIGNAL(signOutEvent()), &newOrder, SLOT(resetData()));
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString Login::getUsername()
{
    return username;
}
QString Login::getPassword()
{
    return password;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Login::setUsername( QString value )
{
    if ( username != value ){
        username = value;
        emit usernameChanged();
    }
}
void Login::setPassword( QString value )
{
    if ( password != value ){
        password = value;
        emit passwordChanged();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////

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
        userNameHeader->setProperty("text", username);
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
    setUsername("");
    setPassword("");
    emit signOutEvent();
    // newOrder.setBuyAmount("");
    // in login.cpp maak ik een signal signoutevent,
    //in newOrder.cpp een slot resetData()
    //emit signOutEvent();

    // newOrder.setSellAmount("");
    // newOrder.setIpPeer("");
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *loginButton = rootObject->findChild<QObject *>("loginButton");
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *footerPane = rootObject->findChild<QObject *>("footerPane");

    if(userNameHeader == nullptr || userImage == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
        loginButton == nullptr || loginNote == nullptr || footerPane == nullptr){
            qInfo() << "nullpointer in signout";
            return;
    }

    userNameHeader->setProperty("visible", false);
    userImage->setProperty("visible", false);
    scrollViewLogin->setProperty("visible", true);
    scrollView->setProperty("visible", false);
    loginButton->setProperty("visible", true);
    loginNote->setProperty("visible", false);
    footerPane->setProperty("outputLogTextVisible", false);

}

void Login::startLoginProcess()
{
    QString validUser = qgetenv("VALIDUSER");
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginButton = rootObject->findChild<QObject *>("loginButton");
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");

    if(loginButton == nullptr || loginNote == nullptr){
        qInfo() << "nullpointer in startLoginProgress";
    }
    
        loginButton->setProperty("visible", false);
    if (validUser != "" && validUser != QString(username))
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
    QStringList commandArguments = QStringList() << username << password;
    loginProcess.start("dist/scripts/iyo/login.php", commandArguments);
    //loginProcess.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");

    QObject::connect(&loginProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(loginFinished(int, QProcess::ExitStatus)));

}