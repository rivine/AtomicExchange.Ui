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

    role = "Initiator";
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

void OoList::initiatorAcceptorActivated(QString editText)
{
    role = editText;
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *coin = rootObject->findChild<QObject*>("coin");
    QObject *destinationCoin = rootObject->findChild<QObject*>("destinationCoin");
    QObject *ipAcceptor = rootObject->findChild<QObject*>("ipAcceptorBox");
    if(editText == "Initiator"){
        coin->setProperty("currentIndex", 0);
        destinationCoin->setProperty("currentIndex", 0);
        ipAcceptor->setProperty("visible", 1);
    
    }else if(editText == "Acceptor"){
        coin->setProperty("currentIndex", 1);
        destinationCoin->setProperty("currentIndex", 1);
        ipAcceptor->setProperty("visible", 0);
    }
}

void OoList::confirmNewOrder(){
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *progressBar = rootObject->findChild<QObject*>("progressBar");

    QObject *amountField = rootObject->findChild<QObject*>("amount");
    QString amount = amountField->property("text").toString();

    QObject *valueField = rootObject->findChild<QObject*>("value");
    QString value = valueField->property("text").toString();

    QObject *ipField = rootObject->findChild<QObject*>("ipAcceptor");
    QString ipAcceptor = ipField->property("text").toString();

    QObject *amountNote = rootObject->findChild<QObject*>("amountNote");
    QObject *valueNote = rootObject->findChild<QObject*>("valueNote");
    QObject *ipNote = rootObject->findChild<QObject*>("ipNote");  

    amountNote->setProperty("visible", 0);
    valueNote->setProperty("visible", 0);
    ipNote->setProperty("visible", 0);

    QObject *submitButton = rootObject->findChild<QObject*>("submitButton");

    if(amount == "" || value == "" || (ipAcceptor == "" && role == "Initiator")){
        qInfo() << "something went wrong";
        if(amount == ""){
            amountNote->setProperty("visible", 1);
        }
        if(value == ""){
            valueNote->setProperty("visible", 1);
        }
        if(ipAcceptor == "" && role == "Initiator"){
            ipNote->setProperty("visible", 1);
        }
    }
    else{
        progressBar->setProperty("visible", 1);
        submitButton->setProperty("enabled", 0);

        if(role == "Initiator"){
            QStringList pythonCommandArguments = QStringList()  << "/home/kristof/jimber/AtomicExchange/exchangeNodes/initiator.py" << "-o" << amount << "-m" << value << "-d";
            
            //PATH IN CODE IS CORRECT BUT CODE IS NOT WORKING
            //QString scriptFile =  QCoreApplication::applicationDirPath() + "/../exchangeNodes/acceptor.py";
            //qInfo() << "path : " << scriptFile;
            //QStringList pythonCommandArguments = QStringList()  << scriptFile << "-o" << "1234" << "-m" << "987" << "-d";

            process.start("python", pythonCommandArguments);
            qInfo() << pythonCommandArguments;
            QObject::connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
            //QObject::connect(&initiatorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors()));  // when enabling errors, there is no ouput anymore after an error
            
        }else if(role == "Acceptor"){

            QStringList pythonCommandArguments = QStringList()  << "/home/kristof/jimber/AtomicExchange/exchangeNodes/acceptor.py" << "-o" << amount << "-m" << value << "-d" ;

            //PATH IN CODE IS CORRECT BUT CODE IS NOT WORKING
            //QString scriptFile =  QCoreApplication::applicationDirPath() + "/../exchangeNodes/acceptor.py";
            //qInfo() << "path : " << scriptFile;
            //QStringList pythonCommandArguments = QStringList()  << scriptFile << "-o" << "1234" << "-m" << "987" << "-d";

            process.start("python", pythonCommandArguments);
            qInfo() << pythonCommandArguments;
            QObject::connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
            //QObject::connect(&acceptorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors())); // when enabling errors, there is no ouput anymore after an error
        }
    }
}
void OoList::readOutput(){
    qInfo("readOutput");
    
    output = process.readAllStandardOutput();
    outputLog += output;
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    //QObject *outputBox = rootObject->findChild<QObject*>("outputMessages");
    QRegExp separator("\\n");
    QStringList list = output.split(separator);
    for( int i = 0; i < list.length() ; i++){
        qInfo() << "splitted string " << list[i]; //=> segmentation fault!?!?
        QJsonObject jsonObj = ObjectFromString(list[i]);
        printJsonObject(jsonObj);
    }

}
void OoList::showOutputLog(){
    QObject *outputLogTextfield = rootObject->findChild<QObject*>("outputLogText");
    outputLogTextfield->setProperty("text", outputLog);
}
void OoList::printJsonObject(const QJsonObject& object){

    int step = object.value("step").toInt();
    qInfo() << "step " << step;
    qInfo() << "stepName " << object.value("stepName");
    QObject *progressBar = rootObject->findChild<QObject*>("progressBar");
    //int step = object.value("step").toInt();
    if( step > 0 && step < 10 ){
         QObject *stepBox = rootObject->findChild<QObject*>("step" + QString::number(step) + "Box");
         QObject *stepCheckBox = rootObject->findChild<QObject*>("step" + QString::number(step) + "CheckBox");
         QObject *stepExtraInfo = rootObject->findChild<QObject*>("step" + QString::number(step) + "ExtraInfo");

         //qInfo() <<"testje" << object.value("step").toDouble() / 10;
         if(role == "Initiator"){
            progressBar->setProperty("value", object.value("step").toDouble() / INITIATOR_STEPS);
         }else if(role == "Acceptor"){
            progressBar->setProperty("value", object.value("step").toDouble() / INITIATOR_STEPS);
         }
         
         stepBox->setProperty("visible", 1);
         stepCheckBox->setProperty("text", object.value("stepName"));
         stepCheckBox->setProperty("checked", 1);
    }
    

}
void OoList::readErrors(){
    qInfo("fail");
    errors = process.readAllStandardError();

    QObject *errorMessages = rootObject->findChild<QObject*>("errorMessages");
    errorMessages->setProperty("text", errors);

    process.kill();
}

QString OoList::getIp(){
    process.start("sh", QStringList() << "-c" << "ip -br addr show | grep zt | cut -d' ' -f 16");
    process.waitForFinished();
    QByteArray output = process.readAll();
    return output;
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

QJsonObject OoList::ObjectFromString(const QString& in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull()){
        if(doc.isObject()){
            obj = doc.object();        
        }
        else{
            qInfo() << "Document is not an object" << endl;
        }
    }
    else{
        qInfo() << "Invalid JSON...\n" << in << endl;
    }

    return obj;
}