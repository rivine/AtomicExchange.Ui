#ifndef OOLIST_H
#define OOLIST_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QVector>
#include "applicationContext.h"
#include <QProcess>

struct OoItem
{
    QString coin;
    QString placed;
    QString amount;
    QString price;
    QString status;
};

class OoList : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QString getIp();
    Q_INVOKABLE QString getBalanceBTC();
    Q_INVOKABLE QString getBalanceTFT();
    Q_INVOKABLE void createBTCAddress();
    Q_INVOKABLE void createTFTAddress();
    Q_INVOKABLE void login(const QString username, const QString password);
    Q_INVOKABLE QString getSyncStatusBTC();
    Q_INVOKABLE QString getSyncStatusTFT();
    Q_INVOKABLE void showOutputLog();
    explicit OoList(QObject *parent = nullptr);
    QVector<OoItem> items() const;

    bool setItemAt(int index, const OoItem &item);
    QJsonObject ObjectFromString(const QString& in);


signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void confirmNewOrder();
    void initiatorAcceptorActivated(QString editText);
    void readOutput();
    void readErrors();

private:
    QVector<OoItem> mItems;
    QString getDateTime();
    void printJsonObject(const QJsonObject& jsonObject);
    QString role;
    QProcess process;
    QString errors;
    QString output;
    QString ipAddress;
    QObject *rootObject;
    QQmlApplicationEngine* engine;
    QString outputLog;
    bool syncStatusTFTFinished;
    bool syncStatusBTCFinished;
    
};

#endif // OOLIST_H
