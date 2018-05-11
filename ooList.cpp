#include "ooList.h"

OoList::OoList(QObject *parent) : QObject(parent)
{
    mItems.append({ true, QStringLiteral("Wash the car") });
    mItems.append({ false, QStringLiteral("Fix the sink") });
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
    if (item.done == oldItem.done && item.description == oldItem.description)
        return false;

    mItems[index] = item;
    return true;
}

void OoList::appendItem()
{
    emit preItemAppended();

    OoItem item;
    item.done = false;
    mItems.append(item);

    emit postItemAppended();
}

void OoList::removeCompletedItems()
{
    for (int i = 0; i < mItems.size(); ) {
        if (mItems.at(i).done) {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
