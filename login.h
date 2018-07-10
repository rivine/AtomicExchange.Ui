#ifndef LOGIN_H
#define LOGIN_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QVector>
#include "applicationContext.h"
#include "newOrder.h"
#include <QProcess>


class Login : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString username READ getUsername WRITE setUsername NOTIFY usernameChanged )
    Q_PROPERTY( QString password READ getPassword WRITE setPassword NOTIFY passwordChanged )
    Q_PROPERTY( QString totpCode READ getTotpCode WRITE setTotpCode NOTIFY totpCodeChanged )
    Q_PROPERTY( QString smsCode READ getSmsCode WRITE setSmsCode NOTIFY smsCodeChanged )
public:
    explicit Login(QObject *parent = nullptr);
    QString getUsername();
    QString getPassword();
    QString getTotpCode();
    QString getSmsCode();
    Q_INVOKABLE void startLoginProcess();
    Q_INVOKABLE void signOut();
    Q_INVOKABLE void selectAuthenticator();
    Q_INVOKABLE void loginTotp();
    Q_INVOKABLE void loginSms();
    
public slots:
    void get2faFinished(int, QProcess::ExitStatus);
    void loginTotpFinished(int, QProcess::ExitStatus);
    void loginInitiateSmsFinished(int, QProcess::ExitStatus);
    void pollingSmsFinished(int, QProcess::ExitStatus);
    void smsCodeFinished(int, QProcess::ExitStatus);
    void setUsername( QString value );
    void setPassword( QString value );
    void setTotpCode( QString value );
    void setSmsCode( QString value );
signals:
    void usernameChanged();
    void passwordChanged();
    void smsCodeChanged();
    void totpCodeChanged();
    void signOutEvent();
private:
    QObject *rootObject;
    QProcess loginProcess;
    QProcess loginProcessTotp;
    QProcess loginProcessInitiateSms;
    QProcess loginProcessPollingSms;
    QProcess loginProcessSendSmsCode;
    QString username;   
    QString password;
    QString totpCode;
    QString smsCode;
    QString output;
    QString cookie;
    QString cookie2Sms;
    QString authenticatorMethod;
    QJsonObject ObjectFromString(const QString  &in);
    void finishLogin();

};

#endif // Login
