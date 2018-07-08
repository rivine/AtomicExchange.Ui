#include "login.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>

#include "newOrder.h"

Login::Login(QObject *parent) : QObject(parent)
{
    setUsername("");
    setPassword("");
    setAuthenticatorAppCode("");
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
QString Login::getAuthenticatorAppCode()
{
    return authenticatorAppCode;
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
void Login::setAuthenticatorAppCode( QString value )
{
    if ( authenticatorAppCode != value ){
        authenticatorAppCode = value;
        emit authenticatorAppCodeChanged();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////

void Login::get2faFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qInfo() << "code "  << exitCode;
    qInfo() << "status " << exitStatus;
   

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *loginButton = rootObject->findChild<QObject *>("loginButton");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");

    QObject *startLoginPane = rootObject->findChild<QObject *>("startLoginPane");
    QObject *selectAuthenticatorPane = rootObject->findChild<QObject *>("selectAuthenticatorPane"); 


    if(loginNote == nullptr || loginButton == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
        userNameHeader == nullptr || userImage == nullptr || startLoginPane == nullptr || selectAuthenticatorPane == nullptr){
            qInfo() << "nullpointer in loginFinished";
            return;
    }

    if (exitCode == 0)
    {
        output = loginProcess.readAllStandardOutput();
        QJsonObject jsonObj = ObjectFromString(output);
        
        cookie = jsonObj["cookie"].toString();

        qInfo() << "cookie : " << cookie;

        startLoginPane->setProperty("visible", false);
        selectAuthenticatorPane->setProperty("visible", true);        
    }
    else if (exitCode == 1)
    {
        loginButton->setProperty("visible", true);
        loginNote->setProperty("text", "Username / password is not correct.");
    }
    else
    {
        loginButton->setProperty("visible", true);
        loginNote->setProperty("text", "Something went wrong, please contact support.");
    }
}
void Login::selectAuthenticator(){
    QObject *authenticatorMethodObject = rootObject->findChild<QObject *>("authenticatorMethod");

    if(authenticatorMethodObject == nullptr){
            qInfo() << "nullpointer in selectAuthenticator";
            return;
    }

    if(authenticatorMethodObject->property("currentIndex") == 0){
        authenticatorMethod = "totp";
    }else if(authenticatorMethodObject->property("currentIndex") == 1){
        authenticatorMethod = "sms";
    }

    if(authenticatorMethod == "totp"){
        //zet scherm totp klaar
    }else if(authenticatorMethod == "sms"){
        //zet scherm sms klaar
    }
}
void Login::loginPotp(){
        QStringList commandArguments = QStringList() << "\"" << cookie << "\""  << authenticatorAppCode;
        loginProcess.start("dist/scripts/iyo/login.php", commandArguments);
        loginProcess.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");

        QObject::connect(&loginProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(loginTotpFinished(int, QProcess::ExitStatus)));
}
void Login::loginTotpFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qInfo() << "loginTotpFinished";
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


    if (exitCode == 0){
        userNameHeader->setProperty("text", username);
        scrollViewLogin->setProperty("visible", false);
        scrollView->setProperty("visible", true);
        userNameHeader->setProperty("visible", true);
        userImage->setProperty("visible", true);
    }
    else if(exitCode == 1){
        loginButton->setProperty("visible", true);
        //loginNote->setProperty("text", "Username / password is not correct.");
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
    setAuthenticatorAppCode("");
    emit signOutEvent();

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
    } //else{
    //    loginNote->setProperty("visible", true);
    //    loginNote->setProperty("text", "You will receive a text message to login.");
    //}
    //QString scriptFile =  QCoreApplication::applicationDirPath() + "/scripts/iyo/login.sh";
    QStringList commandArguments = QStringList() << username << password;
    loginProcess.start("dist/scripts/iyo/get2fa.php", commandArguments);
    //loginProcess.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");

    QObject::connect(&loginProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(get2faFinished(int, QProcess::ExitStatus)));

}

QJsonObject Login::ObjectFromString(const QString &in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if (!doc.isNull())
    {
        if (doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qInfo() << "Document is not an object" << endl;
        }
    }
    else
    {
        qInfo() << "Invalid JSON...\n"
                << in << endl;
    }
    return obj;
}