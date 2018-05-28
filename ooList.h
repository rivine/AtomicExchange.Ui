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
    void uiCreated(QObject *object, const QUrl &url);

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
    
};

#endif // OOLIST_H
