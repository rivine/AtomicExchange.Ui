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
public:
    explicit Login(QObject *parent = nullptr);
    QString getUsername();
    QString getPassword();
    QString getAuthenticatorAppCode();
    Q_INVOKABLE void startLoginProcess();
    Q_INVOKABLE void signOut();
    Q_INVOKABLE void selectAuthenticator();
    Q_INVOKABLE void loginPotp();
    
public slots:
    void get2faFinished(int,  QProcess::ExitStatus);
    void loginTotpFinished(int,  QProcess::ExitStatus);
    void setUsername( QString value );
    void setPassword( QString value );
    void setAuthenticatorAppCode( QString value );
signals:
    void usernameChanged();
    void passwordChanged();
    void authenticatorAppCodeChanged();
    void signOutEvent();
private:
    QObject *rootObject;
    QProcess loginProcess;
    QString username;   
    QString password;
    QString authenticatorAppCode;
    QString output;
    QString cookie;
    QString authenticatorMethod;
    QJsonObject ObjectFromString(const QString  &in);

};

#endif // Login
