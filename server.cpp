#include "server.h"

Server::Server(WalletServer * wallet, QObject *parent)
    : QTcpServer(parent), wallet(wallet)
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Connecting .... " << socketDescriptor;
    AccountThread *thread = new AccountThread(socketDescriptor,wallet, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void Server::startServer()
{
    if (!this->listen(QHostAddress::Any,3500))
    {
        qDebug() << "could not start the server";
    }
    else
    {
        qDebug() << "Listening";
        qDebug() << "Server is Listening on port " + QString::number(this->serverPort());
    }
}
