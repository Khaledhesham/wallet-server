#include "accountthread.h"

AccountThread::AccountThread(int socketDescriptor, WalletServer * wallet, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), wallet(wallet)
{
}

void AccountThread::run()
{
    tcpSocket = new QTcpSocket();
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket->error());
        return;
    }

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()), Qt::DirectConnection);
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    exec();
}

void AccountThread::readyRead()
{
    this->data += tcpSocket->readAll();
    qDebug() << socketDescriptor << " Data in " << data;
    if(this->data.contains(';')) {
        int bytes = data.indexOf(';');     // Find the end of message from the delimeter
        qDebug() << bytes;
        QByteArray message = this->data.left(bytes);  // Cut the message
        qDebug() << message;
        this->data = this->data.mid(bytes+1);                // begin the new data after the delimetere

        processMessage(message);

    }
}

void AccountThread::processMessage(QByteArray message)
{
    QString message_string = QString::fromUtf8(message);
    QString transactions;
    QString error = "";
    message_string = message_string.mid(2);
    unsigned int amount;
    switch (message[0]) {
    case 'c':
        this->account_id = this->wallet->createAccount(message_string,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(this->account_id));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 'l':
        this->account_id = message_string.toUInt();
        amount = this->wallet->checkAccount(this->account_id,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(amount));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 'w':
        amount = this->wallet->withdraw(this->account_id,message_string,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(amount));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 'd':
        amount = this->wallet->deposit(this->account_id,message_string,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(amount));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 'g':
        amount = this->wallet->getAmount(this->account_id,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(amount));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 't':
        transactions = this->wallet->getTransactions(this->account_id,message_string,error);
        if (error == "")
        {
            this->writeSuccessResponse(transactions);
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 'u':
        amount = this->wallet->undo(this->account_id,message_string,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(amount));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    case 'r':
        amount = this->wallet->redo(this->account_id,message_string,error);
        if (error == "")
        {
            this->writeSuccessResponse(QString::number(amount));
            this->wallet->displayInfo(this->account_id);
        }
        else
            this->writeFailureResponse(error);
        break;
    default:
        break;
    }
}

void AccountThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    tcpSocket->deleteLater();
    exit(0);
}

void AccountThread::writeSuccessResponse(QString response)
{
    QString reply = "";
    reply = QString("s ") + response + ";";
    this->tcpSocket->write(reply.toUtf8());
}

void AccountThread::writeFailureResponse(QString error)
{
    QString reply = "";
    reply = QString("f ") + error + ";";
    this->tcpSocket->write(reply.toUtf8());
}
