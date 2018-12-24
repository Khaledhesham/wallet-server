#ifndef WALLETSERVER_H
#define WALLETSERVER_H

#include <QString>
#include <QHash>
#include <account.h>
#include "transactionfactory.h"
#include "ui_mainwindow.h"

class WalletServer : public QObject
{
Q_OBJECT
public:
    static WalletServer * getInstance(QObject *parent);
    static void destroy();
    unsigned int createAccount(QString info, QString & error);  // returns account id
    unsigned int checkAccount(unsigned int account_id, QString & error);    // returns account amount
    void displayInfo(unsigned int account_id);
    unsigned int withdraw(unsigned int account_id, QString amount, QString & error);    // returns account amount
    unsigned int deposit(unsigned int account_id, QString amount, QString & error);    // returns account amount
    unsigned int undo(unsigned int account_id, QString transaction_id, QString & error);    // returns account amount
    unsigned int redo(unsigned int account_id, QString transaction_id, QString & error);    // returns account amount
    unsigned int getAmount(unsigned int account_id, QString & error);    // returns account amount
    QString getTransactions(unsigned int account_id, QString type, QString & error);   // returns account transactions in sort of string

signals:
    void changeName(const QString &);
    void changeInfo(const QString &);
    void listTransactions(const QVector<QStringList> &);

private:
    WalletServer() = default;
    explicit WalletServer(QObject *parent = 0);
    WalletServer(const WalletServer&) = default;
    ~WalletServer();
    static WalletServer* instance;
    QHash<unsigned int, Account *> accounts;
};

#endif // WALLETSERVER_H
