#include "ooList.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>

#include <ctime>

OoList::OoList(QObject *parent) : QObject(parent)
{
    mItems.append({ QStringLiteral("Bitcoin"), QStringLiteral("20/03/2018 10:39"), QStringLiteral("0.15"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Threefold"), QStringLiteral("20/03/2018 11:30"), QStringLiteral("1500"), QStringLiteral("0.1 BTC"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ethereum"), QStringLiteral("20/03/2018 16:56"), QStringLiteral("0.8"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });
    mItems.append({ QStringLiteral("Ripple"), QStringLiteral("20/03/2018 17:12"), QStringLiteral("0.15"), QStringLiteral("15000 TFT"), QStringLiteral("pending") });

    role = "Initiator";
    
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
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
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


    if(role == "Initiator"){
        QStringList pythonCommandArguments = QStringList()  << "/home/kristof/jimber/AtomicExchange/exchangeNodes/initiator.py" << "-o" << "1234" << "-m" << "987" << "-d";
        
        //PATH IN CODE IS CORRECT BUT CODE IS NOT WORKING
        //QString scriptFile =  QCoreApplication::applicationDirPath() + "/../exchangeNodes/acceptor.py";
        //qInfo() << "path : " << scriptFile;
        //QStringList pythonCommandArguments = QStringList()  << scriptFile << "-o" << "1234" << "-m" << "987" << "-d";

        initiatorProcess.start ("python", pythonCommandArguments);
        qInfo() << pythonCommandArguments;
        QObject::connect(&initiatorProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
        //QObject::connect(&initiatorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors()));  // when enabling errors, there is no ouput anymore after an error
        
    }else if(role == "Acceptor"){

        QStringList pythonCommandArguments = QStringList()  << "/home/kristof/jimber/AtomicExchange/exchangeNodes/acceptor.py" << "-o" << "987" << "-m" << "1234" << "-d" ;

        //PATH IN CODE IS CORRECT BUT CODE IS NOT WORKING
        //QString scriptFile =  QCoreApplication::applicationDirPath() + "/../exchangeNodes/acceptor.py";
        //qInfo() << "path : " << scriptFile;
        //QStringList pythonCommandArguments = QStringList()  << scriptFile << "-o" << "1234" << "-m" << "987" << "-d";

        acceptorProcess.start ("python", pythonCommandArguments);

        qInfo() << pythonCommandArguments;
        QObject::connect(&acceptorProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
        //QObject::connect(&acceptorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors())); // when enabling errors, there is no ouput anymore after an error
    }
}
void OoList::readOutput(){
    qInfo("output");

    output += acceptorProcess.readAllStandardOutput();
    QObject *outputMessages = rootObject->findChild<QObject*>("outputMessages");

    outputMessages->setProperty("text", output);

}
void OoList::readErrors(){
    qInfo("fail");
    errors += acceptorProcess.readAllStandardError();

    QObject *errorMessages = rootObject->findChild<QObject*>("errorMessages");
    errorMessages->setProperty("text", errors);

    acceptorProcess.kill();

}

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