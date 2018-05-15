#ifndef OOLIST_H
#define OOLIST_H

#include <QObject>
#include <QVector>
#include "applicationContext.h"

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
    void removeCompletedItems();
    void newOrder();
    void confirmNewOrder();
    void cancelNewOrder();

private:
    QVector<OoItem> mItems;
    QString getDateTime();
};

#endif // OOLIST_H
