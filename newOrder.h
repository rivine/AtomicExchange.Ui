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
        Q_PROPERTY( QString buyAmount READ getBuyAmount WRITE setBuyAmount NOTIFY buyAmountChanged )
        Q_PROPERTY( QString sellAmount READ getSellAmount WRITE setSellAmount NOTIFY sellAmountChanged )
        Q_PROPERTY( QString ipPeer READ getIpPeer WRITE setIpPeer NOTIFY ipPeerChanged )
public:
    explicit NewOrder(QObject *parent = nullptr);
    QString getBuyAmount();
    QString getSellAmount();
    QString getIpPeer();
    Q_INVOKABLE void coinChanged(const int);
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

public slots:
    void setBuyAmount( QString value );
    void setSellAmount( QString value );
    void setIpPeer( QString value );
    void confirmNewOrder();
    void readOutputInitiator();
    void readOutputAcceptor();
    void readErrorsInitiator();
    void readErrorsAcceptor();
    void processFinished(int, QProcess::ExitStatus);
    void resetData();

signals:
    void buyAmountChanged();
    void sellAmountChanged();
    void ipPeerChanged();

private:
    QString getDateTime();
    void enableCheckbox(const QJsonObject& jsonObject);
    void hideCheckboxes(const int);
    QString getTestOutput();
    QString buyAmount;
    QString sellAmount;
    QString ipPeer;
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