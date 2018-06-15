#include "ooList.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include "config.h"

#include <ctime>

OoList::OoList(QObject *parent) : QObject(parent)
{
    mItems.append({ QStringLiteral("Bitcoin"), QStringLiteral("20/03/2018 10:39"), QStringLiteral("0.15"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Threefold"), QStringLiteral("20/03/2018 11:30"), QStringLiteral("1500"), QStringLiteral("0.1 BTC"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ethereum"), QStringLiteral("20/03/2018 16:56"), QStringLiteral("0.8"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ripple"), QStringLiteral("20/03/2018 17:12"), QStringLiteral("0.15"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });


    engine = ApplicationContext::Instance().getEngine();

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
    if (item.coin == oldItem.coin && item.placed == oldItem.placed && item.amount == oldItem.amount && item.price == oldItem.price && item.status == oldItem.status)
        return false;

    mItems[index] = item;
    return true;
}

// QString OoList::getBalanceBTC(){
//     process.start("sh", QStringList() << "-c" << "bitcoin-cli getbalance");
//     process.waitForFinished();
//     QByteArray output = process.readAll();
//     return output;
// }
// QString OoList::getBalanceTFT(){
//     process.start("sh", QStringList() << "/dist/scripts/tft/getbalance.sh");
//     process.waitForFinished();
//     QByteArray output = process.readAll();
//     return output;
// }


void OoList::appendItem()
{
    emit preItemAppended();

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *coin = rootObject->findChild<QObject*>("coin");
    QObject *amount = rootObject->findChild<QObject*>("amount");
    QObject *value = rootObject->findChild<QObject*>("value");
    QObject *destinationCoin = rootObject->findChild<QObject*>("destinationCoin");

    OoItem item;

    item.coin = coin->property("text").toString();
    //item.placed = getDateTime();
    item.amount = amount->property("text").toString();
    item.price = value->property("text").toString() + " " + destinationCoin->property("text").toString();
    item.status = "waiting";
    mItems.append(item);

    emit postItemAppended();
}

// QString getDateTime(){
//   time_t rawtime;
//   struct tm * timeinfo;
//   char buffer[80];

//   time (&rawtime);
//   timeinfo = localtime(&rawtime);

//   strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
//   std::string str(buffer);

//   //qInfo() << str;
//   return QString::fromStdString(str);
// }
