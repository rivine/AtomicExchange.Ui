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
    Q_INVOKABLE void startLoginProcess();
    Q_INVOKABLE void signOut();
    
public slots:
    void loginFinished(int,  QProcess::ExitStatus);
    void setUsername( QString value );
    void setPassword( QString value );
signals:
    void usernameChanged();
    void passwordChanged();
    void signOutEvent();
private:
    QObject *rootObject;
    QProcess loginProcess;
    QString username;   
    QString password;
    NewOrder newOrder;

};

#endif // Login
