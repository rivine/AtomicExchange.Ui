#ifndef OOLIST_H
#define OOLIST_H

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
    explicit OoList(QObject *parent = nullptr);
    QVector<OoItem> items() const;

    bool setItemAt(int index, const OoItem &item);

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
    QString role;
    QProcess acceptorProcess;
    QProcess initiatorProcess;
    QString errors;
    QString output;
    QObject *rootObject;
};

#endif // OOLIST_H
