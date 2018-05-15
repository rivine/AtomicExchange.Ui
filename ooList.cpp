#include "ooList.h"

OoList::OoList(QObject *parent) : QObject(parent)
{
    mItems.append({ QStringLiteral("Bitcoin"), QStringLiteral("20/03/2018 10:39"), QStringLiteral("0.15"), QStringLiteral("Buy"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("TFT"), QStringLiteral("20/03/2018 11:30"), QStringLiteral("1500"), QStringLiteral("Buy"), QStringLiteral("0.1 BTC"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ethereum"), QStringLiteral("20/03/2018 16:56"), QStringLiteral("0.8"), QStringLiteral("Sell"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ripple"), QStringLiteral("20/03/2018 17:12"), QStringLiteral("0.15"), QStringLiteral("Buy"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
}

QVector<OoItem> OoList::items() const
{
    return mItems;
}

bool OoList::setItemAt(int index, const OoItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const OoItem &oldItem = mItems.at(index);
    if (item.coin == oldItem.coin && item.placed == oldItem.placed && item.amount == oldItem.amount && item.buySell == oldItem.buySell && item.price == oldItem.price && item.status == oldItem.status)
        return false;

    mItems[index] = item;
    return true;
}

void OoList::newOrder()
{
    QObject *rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *newOrder = rootObject->findChild<QObject*>("newOrder");
    QObject *openOrder = rootObject->findChild<QObject*>("openOrder");
    newOrder->setProperty("visible", true);
    openOrder->setProperty("visible", false);
}
void OoList::cancelNewOrder()
{
    QObject *rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *newOrder = rootObject->findChild<QObject*>("newOrder");
    QObject *openOrder = rootObject->findChild<QObject*>("openOrder");
    newOrder->setProperty("visible", false);
    openOrder->setProperty("visible", true);
}
void OoList::confirmNewOrder()
{
    QObject *rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *newOrder = rootObject->findChild<QObject*>("newOrder");
    QObject *openOrder = rootObject->findChild<QObject*>("openOrder");
    newOrder->setProperty("visible", false);
    openOrder->setProperty("visible", true);
}

void OoList::appendItem()
{
    emit preItemAppended();

    OoItem item;
    //item.done = false;
    mItems.append(item);

    emit postItemAppended();
}

void OoList::removeCompletedItems()
{
    // for (int i = 0; i < mItems.size(); ) {
    //     if (mItems.at(i).done) {
    //         emit preItemRemoved(i);

    //         mItems.removeAt(i);

    //         emit postItemRemoved();
    //     } else {
    //         ++i;
    //     }
    // }
}
