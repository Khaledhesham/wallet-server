#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "accountthread.h"
#include "walletserver.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(WalletServer * wallet = nullptr, QObject *parent = nullptr);
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
    WalletServer * wallet;
};

#endif // SERVER_H
