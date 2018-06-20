#include "newOrder.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include "config.h"

#include <ctime>

NewOrder::NewOrder(QObject *parent) : QObject(parent)
{
    role = "Initiator";
    syncStatusBTCFinished = false;
    syncStatusTFTFinished = false;
    engine = ApplicationContext::Instance().getEngine();

}

void NewOrder::initiatorAcceptorActivated(QString editText)
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

void NewOrder::confirmNewOrder(){
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
            //QStringList pythonCommandArguments = QStringList()  << "/home/kristof/jimber/AtomicExchange/exchangeNodes/initiator.py" << "-o" << amount << "-m" << value << "-d";
            
            QString scriptFile =  QCoreApplication::applicationDirPath() + "/exchangeNodes/initiator.py";
            QStringList pythonCommandArguments = QStringList()  << scriptFile << "-o" << amount << "-m" << value << "-d";

            process.start("python", pythonCommandArguments);
            qInfo() << pythonCommandArguments;
            QObject::connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
            //QObject::connect(&initiatorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors()));  // when enabling errors, there is no ouput anymore after an error
            
        }else if(role == "Acceptor"){

            //QStringList pythonCommandArguments = QStringList()  << "/home/kristof/jimber/AtomicExchange/exchangeNodes/acceptor.py" << "-o" << amount << "-m" << value << "-d" ;

            QString scriptFile =  QCoreApplication::applicationDirPath() + "/exchangeNodes/acceptor.py";
            QStringList pythonCommandArguments = QStringList()  << scriptFile << "-o" << amount << "-m" << value << "-d";

            process.start("python", pythonCommandArguments);
            qInfo() << pythonCommandArguments;
            QObject::connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
            //QObject::connect(&acceptorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors())); // when enabling errors, there is no ouput anymore after an error
        }
    }
}
void NewOrder::readOutput(){
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
void NewOrder::showOutputLog(){
    QObject *outputLogTextfield = rootObject->findChild<QObject*>("outputLogText");
    outputLogTextfield->setProperty("text", outputLog);
}
void NewOrder::printJsonObject(const QJsonObject& object){

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
void NewOrder::readErrors(){
    qInfo("fail");
    errors = process.readAllStandardError();

    QObject *errorMessages = rootObject->findChild<QObject*>("errorMessages");
    errorMessages->setProperty("text", errors);

    process.kill();
}

QString NewOrder::getIp(){
    process.start("sh", QStringList() << "-c" << "ip -br addr show | grep zt | cut -d' ' -f 16 | awk '{printf \"%.0f\n\", $1}'");
    process.waitForFinished();
    QByteArray output = process.readAll();
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    if(outputString != ""){
            rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
            QObject *getIpTimer = rootObject->findChild<QObject*>("getIpTimer");
            getIpTimer->setProperty("running", false);
    }
    return outputString;
}
QString NewOrder::getBalanceBTC(){
    process.start("sh", QStringList() << "-c" << "bitcoin-cli getbalance");
    process.waitForFinished();
    QByteArray output = process.readAll();
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString;
}
QString NewOrder::getBalanceTFT(){
    process.start("sh", QStringList() << "/dist/scripts/tft/getbalance.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString;
}
void NewOrder::createBTCAddress(){
    process.start("sh", QStringList() << "-c" << "bitcoin-cli getnewaddress "" legacy");
    process.waitForFinished();
    QByteArray output = process.readAll();

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *createdBTCAddessField = rootObject->findChild<QObject*>("createdBTCAddress");
    createdBTCAddessField->setProperty("text", output);
}
void NewOrder::createTFTAddress(){
    process.start("sh", QStringList() << "-c" << "tfchainc wallet address | cut -d' ' -f 4");
    process.waitForFinished();
    QByteArray output = process.readAll();

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *createdTFTAddress = rootObject->findChild<QObject*>("createdTFTAddress");
    createdTFTAddress->setProperty("text", output);
}
QString NewOrder::getSyncStatusBTC(){
    process.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    //TODO, stop timer when sync is 100
    if(output == "100"){
        syncStatusBTCFinished = true;
        if( syncStatusTFTFinished == true){
            rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
            QObject *syncStatusBTCTimer = rootObject->findChild<QObject*>("syncStatusBTCTimer");
            QObject *submitButton = rootObject->findChild<QObject*>("submitButton");
            syncStatusBTCTimer->setProperty("running", false);
            submitButton->setProperty("enabled", true);
        }
    }
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString +   " %";
}
QString NewOrder::getSyncStatusTFT(){
    process.start("sh", QStringList() << "/dist/scripts/tft/getsync.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    //TODO, stop timer when sync is 100
    if(output == "100"){
        syncStatusTFTFinished = true;
        if( syncStatusBTCFinished == true){            
            rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
            QObject *syncStatusTFTTimer = rootObject->findChild<QObject*>("syncStatusTFTTimer");
            QObject *submitButton = rootObject->findChild<QObject*>("submitButton");
            syncStatusTFTTimer->setProperty("running", false);
            submitButton->setProperty("enabled", true);
        }
        
    }
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString + " %";
}

QJsonObject NewOrder::ObjectFromString(const QString& in)
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