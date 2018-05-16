#include "ohList.h"
#include <QDebug>
#include <ctime>

OhList::OhList(QObject *parent) : QObject(parent)
{
    mItems.append({ QStringLiteral("Ethereum"), QStringLiteral("20/02/2018 10:39"), QStringLiteral("0.18"), QStringLiteral("10000 TFT"), QStringLiteral("Done") });
    mItems.append({ QStringLiteral("Threefold"), QStringLiteral("14/03/2018 11:30"), QStringLiteral("1500"), QStringLiteral("0.15 BTC"), QStringLiteral("Done") });
    mItems.append({ QStringLiteral("Bitcoin"), QStringLiteral("12/03/2018 16:56"), QStringLiteral("0.81"), QStringLiteral("12000 TFT"), QStringLiteral("Done") });
}

QVector<OhItem> OhList::items() const
{
    return mItems;
}

bool OhList::setItemAt(int index, const OhItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const OhItem &oldItem = mItems.at(index);
    if (item.coin == oldItem.coin && item.placed == oldItem.placed && item.amount == oldItem.amount && item.price == oldItem.price && item.status == oldItem.status)
        return false;

    mItems[index] = item;
    return true;
}
