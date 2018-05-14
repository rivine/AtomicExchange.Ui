#include "ooModel.h"

#include "ooList.h"

OoModel::OoModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int OoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant OoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const OoItem item = mList->items().at(index.row());
    switch (role) {
    case CoinRole:
        return QVariant(item.coin);
    case PlacedRole:
        return QVariant(item.placed);
    case AmountRole:
        return QVariant(item.amount);
    case BuySellRole:
        return QVariant(item.buySell);
    case PriceRole:
        return QVariant(item.price);
    case StatusRole:
        return QVariant(item.status);
    }

    return QVariant();
}

bool OoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    OoItem item = mList->items().at(index.row());
    switch (role) {
        case CoinRole:
            item.coin = value.toString();
            break;
        case PlacedRole:
            item.placed = value.toString();
            break;
        case AmountRole:
            item.amount = value.toString();
            break;
        case BuySellRole:
            item.buySell = value.toString();
            break;
        case PriceRole:
            item.price = value.toString();
            break;        
        case StatusRole:
            item.status = value.toString();
            break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags OoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> OoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[CoinRole] = "coin";
    names[PlacedRole] = "placed";
    names[AmountRole] = "amount";
    names[BuySellRole] = "buySell";
    names[PriceRole] = "price";
    names[StatusRole] = "status";
    return names;
}

OoList *OoModel::list() const
{
    return mList;
}

void OoModel::setList(OoList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &OoList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &OoList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &OoList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &OoList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
