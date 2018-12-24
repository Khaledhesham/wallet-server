#ifndef ACCOUNTTHREAD_H
#define ACCOUNTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QObject>
#include <QTextCodec>
#include <QDataStream>
#include "walletserver.h"

class AccountThread : public QThread
{
    Q_OBJECT
public:
    AccountThread(int socketDescriptor, WalletServer * wallet, QObject *parent);

    void run() override;
    void processMessage(QByteArray message);

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    void writeSuccessResponse(QString response);
    void writeFailureResponse(QString error);
    QTcpSocket * tcpSocket;
    int socketDescriptor;
    unsigned int account_id;
    QByteArray data;
    WalletServer * wallet;

};

#endif // ACCOUNTTHREAD_H
