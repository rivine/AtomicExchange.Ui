#include "ooList.h"
#include <QDebug>
#include <QProcess>

#include <ctime>

OoList::OoList(QObject *parent) : QObject(parent)
{
    mItems.append({ QStringLiteral("Bitcoin"), QStringLiteral("20/03/2018 10:39"), QStringLiteral("0.15"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Threefold"), QStringLiteral("20/03/2018 11:30"), QStringLiteral("1500"), QStringLiteral("0.1 BTC"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ethereum"), QStringLiteral("20/03/2018 16:56"), QStringLiteral("0.8"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ripple"), QStringLiteral("20/03/2018 17:12"), QStringLiteral("0.15"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
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

void OoList::initiatorAcceptorActivated(QString editText)
{
    role = editText;
    QObject *rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *coin = rootObject->findChild<QObject*>("coin");
    QObject *destinationCoin = rootObject->findChild<QObject*>("destinationCoin");
    if(editText == "Initiator"){
        coin->setProperty("currentIndex", 0);
        destinationCoin->setProperty("currentIndex", 0);
    
    }else if(editText == "Acceptor"){
        coin->setProperty("currentIndex", 1);
        destinationCoin->setProperty("currentIndex", 1);
    }
}

void OoList::confirmNewOrder(){
    QObject *rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *output = rootObject->findChild<QObject*>("output");

    if(role == "Initiator"){
        qInfo("Initiator 1");
        QProcess* initiatorProcess;
        qInfo("Initiator 1.1");
        //QString scriptFile =  QCoreApplication::applicationDirPath() + "python/initiator.py";
        QStringList pythonCommandArguments = QStringList()  << "/home/kristof/exchangeNodes/initiator.py" << "-o" << "987" << "-m" << "1234" << "-d";
        qInfo("Initiator 1.01");
        initiatorProcess->setProcessChannelMode(QProcess::ForwardedChannels);
qInfo("Initiator 1.2");
        initiatorProcess->start ("python", pythonCommandArguments);
        initiatorProcess->waitForFinished(-1);
qInfo("Initiator 1.2");
        QString outputString = initiatorProcess->readAllStandardOutput();
        //QString outputString = acceptorProcess.readAllStandardOutput();
        qInfo() <<"output " << outputString;
       
        output->setProperty("text", outputString);
        qInfo("Initiator 2");
    }else if(role == "Acceptor"){
        qInfo("Acceptor 1");
        QProcess* acceptorProcess = new QProcess; // TODO REMOVE
        //QString scriptFile =  QCoreApplication::applicationDirPath() + "python/acceptor.py";
        QStringList pythonCommandArguments = QStringList()  << "/home/kristof/exchangeNodes/acceptor.py" << "-o" << "1234" << "-m" << "987" << "-d";
        acceptorProcess->setProcessChannelMode(QProcess::ForwardedChannels);

        acceptorProcess->start ("python", pythonCommandArguments);
        acceptorProcess->waitForFinished(-1);

        QString outputString = acceptorProcess->readAllStandardOutput();
        //QString outputString = acceptorProcess.readAllStandardOutput();
        qInfo() <<"output " << outputString;
        //connect(&acceptorProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readData()));
        
        qInfo() << "read output" << acceptorProcess->readAllStandardOutput();
        output->setProperty("text", outputString);
        qInfo("Acceptor 2");
    }
}
void OoList::readData(){
    qInfo("here");
}
void OoList::appendItem()
{
    emit preItemAppended();

    QObject *rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
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

QString getDateTime(){
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
  std::string str(buffer);

  //qInfo() << str;
  return QString::fromStdString(str);
}