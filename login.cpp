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
    setSmsCode("");
    setTotpCode("");
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
QString Login::getSmsCode()
{
    return smsCode;
}
QString Login::getTotpCode()
{
    return totpCode;
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
void Login::setSmsCode( QString value )
{
    if ( smsCode != value ){
        smsCode = value;
        emit smsCodeChanged();
    }
}
void Login::setTotpCode( QString value )
{
    if ( totpCode != value ){
        totpCode = value;
        emit totpCodeChanged();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////

void Login::get2faFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");

    QObject *startLoginPane = rootObject->findChild<QObject *>("startLoginPane");
    QObject *selectAuthenticatorPane = rootObject->findChild<QObject *>("selectAuthenticatorPane"); 


    if(loginNote == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
        userNameHeader == nullptr || userImage == nullptr || startLoginPane == nullptr || selectAuthenticatorPane == nullptr){
            qInfo() << "nullpointer in loginFinished";
            return;
    }

    if (exitCode == 0)
    {
        output = loginProcess.readAllStandardOutput();
        QJsonObject jsonObj = ObjectFromString(output);
        
        cookie = jsonObj["cookie"].toString();
        startLoginPane->setProperty("visible", false);
        selectAuthenticatorPane->setProperty("visible", true);        
    }
    else if (exitCode == 1)
    {
 
        loginNote->setProperty("visible", true);
        loginNote->setProperty("text", "Username / password is not correct.");
    }
    else
    {
        loginNote->setProperty("visible", true);
        loginNote->setProperty("text", "Something went wrong, please contact support.");
    }
}
void Login::selectAuthenticator(){
    QObject *authenticatorMethodObject = rootObject->findChild<QObject *>("authenticatorMethod");
    QObject *selectAuthenticatorPane = rootObject->findChild<QObject *>("selectAuthenticatorPane");
    QObject *loginTotpPane = rootObject->findChild<QObject *>("loginTotpPane");
    QObject *loginSmsPane = rootObject->findChild<QObject *>("loginSmsPane");

    if(authenticatorMethodObject == nullptr || selectAuthenticatorPane == nullptr || loginTotpPane == nullptr || loginSmsPane == nullptr){
            qInfo() << "nullpointer in selectAuthenticator";
            return;
    }
    selectAuthenticatorPane->setProperty("visible", false);
    if(authenticatorMethodObject->property("currentIndex") == 0){
        authenticatorMethod = "totp";
        loginTotpPane->setProperty("visible", true);    

    }else if(authenticatorMethodObject->property("currentIndex") == 1){
        authenticatorMethod = "sms";
        loginSmsPane->setProperty("visible", true);    

        QStringList commandArguments = QStringList() << cookie ;
        loginProcessInitiateSms.start("dist/scripts/iyo/login_sms_initiate.php", commandArguments);
        QObject::connect(&loginProcessInitiateSms, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(loginInitiateSmsFinished(int, QProcess::ExitStatus)));

    }
}
void Login::loginTotp(){
        QObject *totpCodeNote = rootObject->findChild<QObject *>("totpCodeNote");
        if(totpCodeNote == nullptr){
            qInfo() << "nullpointer in loginTotp";
            return;
        }
        totpCodeNote->setProperty("visible", false);

        QStringList commandArguments = QStringList() << cookie << totpCode;
        loginProcessTotp.start("dist/scripts/iyo/login_totp.php", commandArguments);
        QObject::connect(&loginProcessTotp, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(loginTotpFinished(int, QProcess::ExitStatus)));
}
void Login::loginSms(){            
        QObject *smsCodeNote = rootObject->findChild<QObject *>("smsCodeNote");
        if(smsCodeNote == nullptr){
            qInfo() << "nullpointer in loginSms";
            return;
        }
        smsCodeNote->setProperty("visible", false);

        QStringList commandArguments2 = QStringList() << cookie2Sms << smsCode;
        loginProcessSendSmsCode.start("dist/scripts/iyo/login_sms_sendcode.php", commandArguments2);
        QObject::connect(&loginProcessSendSmsCode, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(smsCodeFinished(int, QProcess::ExitStatus)));
        
}
void Login::loginInitiateSmsFinished(int exitCode, QProcess::ExitStatus exitStatus){   
        if(exitStatus == 0){     
            cookie2Sms = loginProcessInitiateSms.readAllStandardOutput();

            QStringList commandArguments = QStringList() << cookie2Sms;
            loginProcessPollingSms.start("dist/scripts/iyo/login_sms_polling.php", commandArguments);
        QObject::connect(&loginProcessPollingSms, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(pollingSmsFinished(int, QProcess::ExitStatus)));
        }else{
            qInfo() << "somethinw went wrong in loginInitiateSmsFinished"
        }
}
void Login::pollingSmsFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitCode == 0){
        finishLogin();
    }else if(exitCode == 1){
        qInfo() << "something went wrong pollingSmsFinished";
    }
}
void Login::smsCodeFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QObject *smsCodeNote = rootObject->findChild<QObject *>("smsCodeNote");
    if(smsCodeNote == nullptr){
        qInfo() << "nullpointer in smsCodeFinished";
        return;
    }

    if(exitCode == 0){
        loginProcessPollingSms.kill();
        finishLogin();
    }else if(exitCode == 1){        
        smsCodeNote->setProperty("visible", true);
    }
}
void Login::finishLogin(){
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");

    if(loginNote == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
        userNameHeader == nullptr || userImage == nullptr){
            qInfo() << "nullpointer in finishLogin";
            return;
    }
    userNameHeader->setProperty("text", username);
    scrollViewLogin->setProperty("visible", false);
    scrollView->setProperty("visible", true);
    userNameHeader->setProperty("visible", true);
    userImage->setProperty("visible", true);
}
void Login::loginTotpFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *totpCodeNote = rootObject->findChild<QObject *>("totpCodeNote");
   
    if(totpCodeNote == nullptr){
            qInfo() << "nullpointer in loginTotpFinished";
            return;
    }

    if (exitCode == 0){
        finishLogin();
    }
    else if(exitCode == 1){
        totpCodeNote->setProperty("visible", true);
    }
}

void Login::signOut()
{
    setUsername("");
    setPassword("");
    setTotpCode("");
    setSmsCode("");
    emit signOutEvent();

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *userNameHeader = rootObject->findChild<QObject *>("userNameHeader");
    QObject *userImage = rootObject->findChild<QObject *>("userImage");
    QObject *scrollView = rootObject->findChild<QObject *>("scrollView");
    QObject *scrollViewLogin = rootObject->findChild<QObject *>("scrollViewLogin");
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");
    QObject *footerPane = rootObject->findChild<QObject *>("footerPane");
    QObject *loginSmsPane = rootObject->findChild<QObject *>("loginSmsPane");
    QObject *loginTotpPane = rootObject->findChild<QObject *>("loginTotpPane");
    QObject *selectAuthenticatorPane = rootObject->findChild<QObject *>("selectAuthenticatorPane");
    QObject *startLoginPane = rootObject->findChild<QObject *>("startLoginPane");
    QObject *totpCodeNote = rootObject->findChild<QObject *>("totpCodeNote");
    QObject *smsCodeNote = rootObject->findChild<QObject *>("smsCodeNote");

    if(userNameHeader == nullptr || userImage == nullptr || scrollView == nullptr || scrollViewLogin == nullptr || 
       loginNote == nullptr || footerPane == nullptr || totpCodeNote == nullptr || smsCodeNote == nullptr || 
        loginSmsPane == nullptr || loginTotpPane == nullptr || selectAuthenticatorPane == nullptr || startLoginPane == nullptr){
            qInfo() << "nullpointer in signout";
            return;
    }

    userNameHeader->setProperty("visible", false);
    userImage->setProperty("visible", false);
    scrollViewLogin->setProperty("visible", true);
    scrollView->setProperty("visible", false);
    loginNote->setProperty("visible", false);
    footerPane->setProperty("outputLogTextVisible", false);

    loginSmsPane->setProperty("visible", false);
    loginTotpPane->setProperty("visible", false);
    selectAuthenticatorPane->setProperty("visible", false);

    totpCodeNote->setProperty("visible", false);
    smsCodeNote->setProperty("visible", false);

    startLoginPane->setProperty("visible", true);            
}

void Login::startLoginProcess()
{
    QString validUser = qgetenv("VALIDUSER");
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *loginNote = rootObject->findChild<QObject *>("loginNote");

    if(loginNote == nullptr){
        qInfo() << "nullpointer in startLoginProgress";
    }
    
    if (validUser != "" && validUser != QString(username))
    {
        qInfo() << "Invalid user";
        loginNote->setProperty("visible", true);
        loginNote->setProperty("text", "Invalid user.");
        return;
    }
    QStringList commandArguments = QStringList() << username << password;
    loginProcess.start("dist/scripts/iyo/get2fa.php", commandArguments);
    QObject::connect(&loginProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(get2faFinished(int, QProcess::ExitStatus)));
}

QJsonObject Login::ObjectFromString(const QString &in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if (!doc.isNull()){
        if (doc.isObject()){
            obj = doc.object();
        }
        else{
            qInfo() << "Document is not an object" << endl;
        }
    }
    else{
        qInfo() << "Invalid JSON...\n"
                << in << endl;
    }
    return obj;
}