#ifndef LOGIN_H
#define LOGIN_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QVector>
#include "applicationContext.h"
#include <QProcess>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);
    Q_INVOKABLE void startLoginProcess(const QString username, const QString password);
    Q_INVOKABLE void signOut();
    
public slots:
    void loginFinished(int,  QProcess::ExitStatus);

private:
    QObject *rootObject;
    QProcess loginProcess;
    QString userName;   
};

#endif // Login
