#ifndef OHLIST_H
#define OHLIST_H

#include <QObject>
#include <QVector>
#include "applicationContext.h"
#include "ohList.h"

struct OhItem
{
    QString coin;
    QString placed;
    QString amount;
    QString price;
    QString status;
};

class OhList : public QObject
{
    Q_OBJECT
public:
    explicit OhList(QObject *parent = nullptr);
    QVector<OhItem> items() const;

    bool setItemAt(int index, const OhItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

private:
    QVector<OhItem> mItems;
    QString getDateTime();
};

#endif // OHLIST_H
