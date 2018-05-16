#ifndef OHLIST_H
#define OHLIST_H

#include <QObject>
#include <QVector>
#include "applicationContext.h"
#include "ooList.h"

class OhList : public QObject
{
    Q_OBJECT
public:
    explicit OhList(QObject *parent = nullptr);
    QVector<OoItem> items() const;

    bool setItemAt(int index, const OoItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

private:
    QVector<OoItem> mItems;
    QString getDateTime();
};

#endif // OHLIST_H
