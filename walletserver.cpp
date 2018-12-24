#include "walletserver.h"

WalletServer* WalletServer::instance = nullptr;

WalletServer* WalletServer::getInstance(QObject *parent){
    if (!instance){
        instance = new WalletServer(parent);
    }
    return instance;
}

WalletServer::WalletServer(QObject *parent) : QObject(parent)
{

}

void WalletServer::destroy()
{
    delete instance;
    instance = nullptr;
}

unsigned int WalletServer::createAccount(QString info, QString & error)
{
    QStringList info_list = info.split(',');
    if (info_list.size() == 5)
    {
        Account * acc = new Account(info_list[0],info_list[1].toUShort(),info_list[2],info_list[3],info_list[4],this->accounts.size());
        this->accounts.insert(acc->getId(),acc);
        return acc->getId();
    }
    else
    {
        error = "Incorrect parameters count received!";
        return 0;
    }
}

unsigned int WalletServer::checkAccount(unsigned int account_id, QString & error)
{
    if (this->accounts.contains(account_id))
    {
        return this->accounts[account_id]->getAmount();
    }
    else {
        error = "Account doesn't exist!";
        return 0;
    }
}

void WalletServer::displayInfo(unsigned int account_id)
{
    Account * acc = this->accounts[account_id];
    QString name = acc->getName();
    QString info = "Age: " + QString::number(acc->getAge()) + "\n";
    info += "National Id: " + acc->getNationalId() + "\n";
    info += "Email: " + acc->getEmail() + "\n";
    info += "Mobile Number: " + acc->getMobileNumber() + "\n";
    info += "Account Amount: " + QString::number(acc->getAmount());
    QVector<Transaction *>  transactions = this->accounts[account_id]->getTransactions();
    QVector<QStringList> transactions_table;
    for (int i = 0; i < transactions.size(); ++i) {
        Transaction * t = transactions.at(i);
        QStringList row;
        row << QString::number(i+1);
        row << t->getType();
        row << QString::number(t->getAmount());
        row << t->getDate().toString();
        if ( t->isUndone())
        {
            row << "yes";
        }
        else
        {
            row << "no";
        }
        transactions_table.push_back(row);
    }
    emit changeName(name);
    emit changeInfo(info);
    emit listTransactions(transactions_table);
}

unsigned int WalletServer::withdraw(unsigned int account_id, QString amount, QString & error)
{
    if (amount.toInt() <= 0)
    {
        error = "Amount cannot be zero or negative!";
        return 0;
    }
    if (this->accounts.contains(account_id))
    {
        Account * acc = this->accounts[account_id];
        Transaction * t = TransactionFactory::NewTransaction("withdraw",amount.toUInt());
        unsigned int account_amount = acc->getAmount();
        account_amount = t->process(account_amount, error);
        if (error != "")
        {
            return 0;
        }
        acc->setAmount(account_amount);
        this->accounts[account_id]->addTransaction(t);
        return account_amount;
    }
    else {
        error = "Account doesn't exist!";
        return 0;
    }
}

unsigned int WalletServer::deposit(unsigned int account_id, QString amount, QString & error)
{
    if (amount.toUInt() == 0)
    {
        error = "Amount cannot be zero or negative!";
        return 0;
    }
    if (this->accounts.contains(account_id))
    {
        Account * acc = this->accounts[account_id];
        qDebug() << amount.toUInt();
        Transaction * t = TransactionFactory::NewTransaction("deposit",amount.toUInt());
        unsigned int account_amount = acc->getAmount();
        account_amount = t->process(account_amount,error);
        if (error != "")
        {
            return 0;
        }
        acc->setAmount(account_amount);
        this->accounts[account_id]->addTransaction(t);
        return account_amount;
    }
    else {
        error = "Account doesn't exist!";
        return 0;
    }
}

unsigned int WalletServer::getAmount(unsigned int account_id, QString & error)
{
    if (this->accounts.contains(account_id))
    {
        return this->accounts[account_id]->getAmount();
    }
    else {
        error = "Account doesn't exist!";
        return 0;
    }
}

QString WalletServer::getTransactions(unsigned int account_id, QString type, QString & error)
{
    bool undone;
    if (type == "u")
    {
        undone = false;
    }
    else if (type == "r")
    {
        undone = true;
    }
    else
    {
        error = "No type specified!";
        return "";
    }
    if (this->accounts.contains(account_id))
    {
        QString transactions_string = "";
        QVector<Transaction *>  transactions = this->accounts[account_id]->getTransactions();
        for (int i = 0; i < transactions.size(); ++i) {
            Transaction * t = transactions.at(i);
            if (t->isUndone() != undone)
                continue;
            if (transactions_string != "")
                transactions_string += ",";
            transactions_string += QString::number(i+1) + " " + t->getType() + " " + QString::number(t->getAmount()) + " " + t->getDate().toString();
        }
        if (transactions_string == "")
        {
            error = "No Transactions exist!";
            return "";
        }
        return transactions_string;
    }
    else {
        error = "Account doesn't exist!";
        return "";
    }
}

unsigned int WalletServer::undo(unsigned int account_id, QString transaction_id, QString & error)
{
    if (this->accounts.contains(account_id))
    {
        Account * acc = this->accounts[account_id];
        if (transaction_id.toInt() > acc->getTransactions().size() || transaction_id.toInt() <= 0)
        {
            error = "Transaction id wrong!";
            return 0;
        }
        if (Transaction * t = acc->getTransactions().at(transaction_id.toInt() - 1))
        {
            if (t->isUndone() == true)
            {
                error = "Transaction already undone!";
                return 0;
            }
            t->undo();
            unsigned int account_amount = acc->getAmount();
            account_amount = t->process(account_amount, error);
            if (error != "")
            {
                t->redo();
                return 0;
            }
            acc->setAmount(account_amount);
            return account_amount;
        }
        else
        {
            error = "Transaction doesn't exist!";
            return 0;
        }
    }
    else {
        error = "Account doesn't exist!";
        return 0;
    }
}

unsigned int WalletServer::redo(unsigned int account_id, QString transaction_id, QString & error)
{
    if (this->accounts.contains(account_id))
    {
        Account * acc = this->accounts[account_id];
        if (Transaction * t = acc->getTransactions().at(transaction_id.toInt() - 1))
        {
            if (t->isUndone() == false)
            {
                error = "Transaction is not undone!";
                return 0;
            }
            t->redo();
            unsigned int account_amount = acc->getAmount();
            account_amount = t->process(account_amount, error);
            if (error != "")
            {
                t->undo();
                return 0;
            }
            acc->setAmount(account_amount);
            return account_amount;
        }
        else
        {
            error = "Transaction doesn't exist!";
            return 0;
        }
    }
    else {
        error = "Account doesn't exist!";
        return 0;
    }
}

WalletServer::~WalletServer()
{
    qDeleteAll(this->accounts);
    this->accounts.clear();
}
