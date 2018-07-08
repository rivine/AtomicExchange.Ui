#include "newOrder.h"
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>

#include "config.h"

#include <ctime>

NewOrder::NewOrder(QObject *parent) : QObject(parent)
{
    setBuyAmount("");
    setSellAmount("");
    setIpPeer("");
    outputLog = "";
    role = "Initiator";
    syncStatusBTCFinished = false;
    syncStatusTFTFinished = false;
    engine = ApplicationContext::Instance().getEngine();
}

///////////////////////////////////////////////////////////////////////////////////////////////

QString NewOrder::getBuyAmount()
{
    return buyAmount;
}
QString NewOrder::getSellAmount()
{
    return sellAmount;
}
QString NewOrder::getIpPeer()
{
    return ipPeer;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void NewOrder::setBuyAmount( QString value )
{
    if ( buyAmount != value ){
        buyAmount = value;
        emit buyAmountChanged();
    }
}
void NewOrder::setSellAmount( QString value )
{
    if ( sellAmount != value ){
        sellAmount = value;
        emit sellAmountChanged();
    }
}
void NewOrder::setIpPeer( QString value )
{
    if ( ipPeer != value ){
        ipPeer = value;
        emit ipPeerChanged();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////

void NewOrder::coinChanged(const int index)
{
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *destinationCoin = rootObject->findChild<QObject *>("destinationCoin");

    if (destinationCoin == nullptr)
    {
        qInfo() << "nullptr in coinChanged";
        return;
    }
    if (index == 0)
    {
        qInfo() << "Role is initiator";
        role = "Initiator";
    }
    else if (index == 1)
    {
        qInfo() << "Role is acceptor";
        role = "Acceptor";
    }
    destinationCoin->setProperty("currentIndex", index);
}

void NewOrder::confirmNewOrder()
{

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *progressBar = rootObject->findChild<QObject *>("progressBar");

    QObject *amountNote = rootObject->findChild<QObject *>("amountNote");
    QObject *valueNote = rootObject->findChild<QObject *>("valueNote");
    QObject *ipNote = rootObject->findChild<QObject *>("ipNote");
    QObject *submitButton = rootObject->findChild<QObject *>("submitButton");

    if (progressBar == nullptr || amountNote == nullptr || 
        valueNote == nullptr || ipNote == nullptr || submitButton == nullptr)
    {

        qInfo() << "nullptr in confirmNewOrder";
        return;
    }
    amountNote->setProperty("visible", 0);
    valueNote->setProperty("visible", 0);
    ipNote->setProperty("visible", 0);

    if (sellAmount == "" || buyAmount == "" || (ipPeer == "" && role == "Initiator"))
    {
        qInfo() << "something went wrong";
        if (sellAmount == "")
        {
            amountNote->setProperty("visible", 1);
        }
        if (buyAmount == "")
        {
            valueNote->setProperty("visible", 1);
        }
        if (ipPeer == "" && role == "Initiator")
        {
            ipNote->setProperty("visible", 1);
        }
    }
    else
    {
        progressBar->setProperty("value", 0);
        progressBar->setProperty("visible", 1);

        qInfo() << "role" << role;
        if (role == "Initiator")
        {
            qInfo() << "In initiator";
            hideCheckboxes(INITIATOR_STEPS);
            QString scriptFile = "/dist/AtomicExchange.Scripts/initiator.py";
            QStringList pythonCommandArguments = QStringList() << scriptFile << "-m" << sellAmount << "-o" << buyAmount << "-i" << ipPeer;
            processInitiator.start("python", pythonCommandArguments);
            QObject::connect(&processInitiator, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutputInitiator()));
            QObject::connect(&processInitiator, SIGNAL(readyReadStandardError()), this, SLOT(readErrorsInitiator()));  // when enabling errors, there is no ouput anymore after an error
            QObject::connect(&processInitiator, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus))); 

            submitButton->setProperty("enabled", 0);
        }
        else if (role == "Acceptor")
        {
            hideCheckboxes(ACCEPTOR_STEPS);
            QString scriptFile = "/dist/AtomicExchange.Scripts/participant.py";
            QStringList pythonCommandArguments = QStringList() << scriptFile << "-m" << sellAmount << "-o" << buyAmount;

            processAcceptor.start("python", pythonCommandArguments);
            qInfo() << pythonCommandArguments;
            QObject::connect(&processAcceptor, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutputAcceptor()));
            QObject::connect(&processAcceptor, SIGNAL(readyReadStandardError()), this, SLOT(readErrorsAcceptor())); 
            QObject::connect(&processAcceptor, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));  

            //QObject::connect(&acceptorProcess, SIGNAL(readyReadStandardError()), this, SLOT(readErrors())); // when enabling errors, there is no ouput anymore after an error
            submitButton->setProperty("enabled", 0);
        }
    }
}
void NewOrder::readErrorsInitiator(){
    qInfo("error in script");
    qInfo() << processInitiator.readAllStandardError();

    QObject *submitButton = rootObject->findChild<QObject *>("submitButton");
    if ( submitButton == nullptr)
    {
        qInfo() << "nullptr in readErrorsInitiator";
        return;
    }

}
void NewOrder::readErrorsAcceptor(){
    qInfo("error in script");
    qInfo() << processAcceptor.readAllStandardError();

    QObject *submitButton = rootObject->findChild<QObject *>("submitButton");
    if ( submitButton == nullptr)
    {
        qInfo() << "nullptr in readErrorsInitiator";
        return;
    }

}
void NewOrder::readOutputInitiator()
{
    qInfo("readOutput");
    output = processInitiator.readAllStandardOutput();
    outputLog += output;
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QRegExp separator("\\n");
    QStringList list = output.split(separator);
    for (int i = 0; i < list.length(); i++)
    {
        qInfo() << "splitted string nr " << i << ": " << list[i];
        QJsonObject jsonObj = ObjectFromString(list[i]);
        enableCheckbox(jsonObj);
    }
}
void NewOrder::readOutputAcceptor()
{
    qInfo() << "readOutput";
    output = processAcceptor.readAllStandardOutput();
    outputLog += output;
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();

    QRegExp separator("\\n");
    QStringList list = output.split(separator);
    for (int i = 0; i < list.length(); i++)
    {
        qInfo() << "splitted string " << list[i]; 
        QJsonObject jsonObj = ObjectFromString(list[i]);
        enableCheckbox(jsonObj);
    }
}
void NewOrder::processFinished(int code, QProcess::ExitStatus status){
    qInfo() << "processFinished";
    QObject *submitButton = rootObject->findChild<QObject *>("submitButton");
    QObject *progressBar = rootObject->findChild<QObject *>("progressBar");

    if (submitButton == nullptr || progressBar == nullptr){

        qInfo() << "nullptr in processFinished";
        return;
    }
    submitButton->setProperty("enabled", 1);
    progressBar->setProperty("visible", 0);
    resetData();
}

void NewOrder::resetData(){
    setBuyAmount("");
    setSellAmount("");
    setIpPeer("");
}
void NewOrder::showOutputLog()
{
    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();

    QObject *outputLogTextfield = rootObject->findChild<QObject *>("outputLogText");

    if (outputLogTextfield == nullptr)
    {
        qInfo() << "nullptr in showOutputLog";
        return;
    }
    outputLogTextfield->setProperty("text", outputLog);
}
void NewOrder::enableCheckbox(const QJsonObject &object)
{
    
    double step = object.value("step").toDouble();

    QObject *progressBar = rootObject->findChild<QObject *>("progressBar");
    QObject *stepBox = rootObject->findChild<QObject *>("step" + QString::number(step) + "Box");
    QObject *stepCheckBox = rootObject->findChild<QObject *>("step" + QString::number(step) + "CheckBox");
    QObject *submitButton = rootObject->findChild<QObject *>("submitButton");

    QObject *step4Box = rootObject->findChild<QObject *>("step4Box");
    QObject *step5Box = rootObject->findChild<QObject *>("step5Box");

    if (progressBar == nullptr || stepBox == nullptr || stepCheckBox == nullptr || submitButton == nullptr
    || step4Box == nullptr || step5Box == nullptr)
    {
        qInfo() << "nullptr in enableCheckbox";
        return;
    }
    //int step = object.value("step").toInt();
    if (step > 0 && step <= 4)
    {

        //qInfo() <<"testje" << object.value("step").toDouble() / 10;
        if (role == "Initiator")
        {
            progressBar->setProperty("value", object.value("step").toDouble() / INITIATOR_STEPS);
        }
        else if (role == "Acceptor")
        {
            progressBar->setProperty("value", object.value("step").toDouble() / ACCEPTOR_STEPS);
        }

        stepBox->setProperty("visible", true);
        stepCheckBox->setProperty("text", object.value("stepName"));
        stepCheckBox->setProperty("checked", true);

        if(step == 3){
            step4Box->setProperty("visible", true);
            step5Box->setProperty("visible", true);
        }
        if(step == 4){
            progressBar->setProperty("visible", false);
            step5Box->setProperty("visible", false);
        }
    }
}
void NewOrder::hideCheckboxes(const int steps){
    qInfo() << "hideCheckboxes  steps"<< steps;
    for(int i=1; i <= steps; i++ ){
        QObject *progressBar = rootObject->findChild<QObject *>("progressBar");
        QObject *stepBox = rootObject->findChild<QObject *>("step" + QString::number(i) + "Box");
        QObject *stepCheckBox = rootObject->findChild<QObject *>("step" + QString::number(i) + "CheckBox");

        if (progressBar == nullptr || stepBox == nullptr || stepCheckBox == nullptr)
        {
            qInfo() << "nullptr in disableCheckboxes";
            return;
        }
        stepBox->setProperty("visible", false);
        stepCheckBox->setProperty("checked", false);
    }
}

QString NewOrder::getIp()
{
    QProcess process;
    process.start("sh", QStringList() << "/dist/scripts/sys/getztaddr.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));

    if (outputString != "")
    {
        rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();

        QObject *getIpTimer = rootObject->findChild<QObject *>("getIpTimer");
        if (getIpTimer == nullptr)
        {
            qInfo() << "nullptr in getIp";
            return "";
        }
        getIpTimer->setProperty("running", false);
    }
    ipAddress = outputString;
    return outputString;
}
QString NewOrder::getBalanceBTC()
{
    qInfo() << "getbalance";
    QProcess process;
    process.start("sh", QStringList() << "-c"
                                      << "bitcoin-cli getbalance");
    process.waitForFinished();
    QByteArray output = process.readAll();
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString;
}
QString NewOrder::getBalanceTFT()
{
    qInfo() << "getbalance tft";
    QProcess process;
    process.start("sh", QStringList() << "/dist/scripts/tft/getbalance.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString;
}


void NewOrder::createBTCAddress()
{
    qInfo() << "create btc";
    QProcess process;
    process.start("sh", QStringList() << "-c"
                                      << "bitcoin-cli getnewaddress "
                                         " legacy");
    process.waitForFinished();
    QByteArray output = process.readAll();

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *createdBTCAddessField = rootObject->findChild<QObject *>("createdBTCAddress");
    if (createdBTCAddessField == nullptr)
    {
        qInfo() << "Nullptr in createbtcaddress";
    }
    createdBTCAddessField->setProperty("text", output);
}
void NewOrder::createTFTAddress()
{
    qInfo() << "create tft";
    QProcess process;
    process.start("sh", QStringList() << "-c"
                                      << "tfchainc wallet address | cut -d' ' -f 4");
    process.waitForFinished();
    QByteArray output = process.readAll();

    rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
    QObject *createdTFTAddress = rootObject->findChild<QObject *>("createdTFTAddress");
    if (createdTFTAddress == nullptr)
    {
        qInfo() << "nullptr in create tft failed";
        return;
    }
    createdTFTAddress->setProperty("text", output);
}
QString NewOrder::getSyncStatusBTC()
{
    qInfo() << "getsync ";
    QProcess process;
    process.start("sh", QStringList() << "/dist/scripts/btc/getsync.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    //TODO, stop timer when sync is 100
    if (output == "100")
    {
        syncStatusBTCFinished = true;
        if (syncStatusTFTFinished == true)
        {
            rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
            QObject *syncStatusBTCTimer = rootObject->findChild<QObject *>("syncStatusBTCTimer");
            QObject *submitButton = rootObject->findChild<QObject *>("submitButton");
            if (syncStatusBTCTimer == nullptr && submitButton == nullptr)
            {
                qInfo() << "getsyncStatusBtc error";
                return "";
            }

            syncStatusBTCTimer->setProperty("running", false);
            submitButton->setProperty("enabled", true);
        }
    }
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString + " %";
}
QString NewOrder::getSyncStatusTFT()
{
    qInfo() << "get sync tft";
    QProcess process;
    process.start("sh", QStringList() << "/dist/scripts/tft/getsync.sh");
    process.waitForFinished();
    QByteArray output = process.readAll();
    //TODO, stop timer when sync is 100
    if (output == "100")
    {
        syncStatusTFTFinished = true;
        if (syncStatusBTCFinished == true)
        {
            rootObject = ApplicationContext::Instance().getEngine()->rootObjects().first();
            QObject *syncStatusTFTTimer = rootObject->findChild<QObject *>("syncStatusTFTTimer");
            QObject *submitButton = rootObject->findChild<QObject *>("submitButton");
            if (syncStatusTFTTimer == nullptr && submitButton == nullptr)
            {
                qInfo() << "error sync status tft";
            }
            syncStatusTFTTimer->setProperty("running", false);
            submitButton->setProperty("enabled", true);
        }
    }
    QString outputString(output);
    outputString.remove(QRegExp("[\n\t\r]"));
    return outputString + " %";
}

QJsonObject NewOrder::ObjectFromString(const QString &in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if (!doc.isNull())
    {
        if (doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qInfo() << "Document is not an object" << endl;
        }
    }
    else
    {
        qInfo() << "Invalid JSON...\n"
                << in << endl;
    }
    return obj;
}

QString NewOrder::getCommitVersion()
{
    qInfo() << "get commit";
    QFile file("dist/commit");
    QString fileContent;
    if (file.open(QIODevice::ReadOnly))
    {
        QString line;
        QTextStream t(&file);
        do
        {
            line = t.readLine();
            fileContent += line;
        } while (!line.isNull());

        file.close();
    }
    else
    {
        qInfo() << "Something went wrong. Commitfile not found";
    }
    fileContent += " ";
    QFile hostNameFile("/etc/hostname");
    if (hostNameFile.open(QIODevice::ReadOnly))
    {
        QString line;
        QTextStream t(&hostNameFile);
        do
        {
            line = t.readLine();
            fileContent += line;
        } while (!line.isNull());

        hostNameFile.close();
    }
    else
    {
        qInfo() << "Something went wrong in hostname.";
    }
    return fileContent;
}