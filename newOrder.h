#ifndef NEWORDER_H
#define NEWORDER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QVector>
#include "applicationContext.h"
#include <QProcess>

class NewOrder : public QObject
{
    Q_OBJECT
public:
    explicit NewOrder(QObject *parent = nullptr);
    Q_INVOKABLE QString getIp();
    Q_INVOKABLE QString getBalanceBTC();
    Q_INVOKABLE QString getBalanceTFT();
    Q_INVOKABLE void createBTCAddress();
    Q_INVOKABLE void createTFTAddress();
    Q_INVOKABLE QString getSyncStatusBTC();
    Q_INVOKABLE QString getSyncStatusTFT();
    Q_INVOKABLE void showOutputLog();

    Q_INVOKABLE QString getCommitVersion();

    QJsonObject ObjectFromString(const QString& in);


// signals:
//     void preItemAppended();
//     void postItemAppended();

//     void preItemRemoved(int index);
//     void postItemRemoved();

public slots:
    void confirmNewOrder();
    void initiatorAcceptorActivated(QString editText);
    void readOutputInitiator();
    void readOutputAcceptor();
    //void readErrors();

private:
    QString getDateTime();
    void printJsonObject(const QJsonObject& jsonObject);
    QString role;
    QProcess processInitiator;
    QProcess processAcceptor;
    QString errors;
    QString output;
    QString ipAddress;
    QObject *rootObject;
    QQmlApplicationEngine* engine;
    QString outputLog;
    bool syncStatusTFTFinished;
    bool syncStatusBTCFinished;
    
};

#endif // NEWORDER_H
