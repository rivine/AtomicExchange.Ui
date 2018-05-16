#ifndef OHMODEL_H
#define OHMODEL_H

#include <QAbstractListModel>

class OhList;

class OhModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(OhList *list READ list WRITE setList)

public:
    explicit OhModel(QObject *parent = nullptr);

    enum {
        CoinRole,
        PlacedRole,
        AmountRole,
        PriceRole,
        StatusRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    OhList *list() const;
    void setList(OhList *list);

private:
    OhList *mList;
};

#endif // OHMODEL_H
