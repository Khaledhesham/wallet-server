#include "transactionfactory.h"

Transaction * TransactionFactory::NewTransaction(const QString &type, unsigned int amount)
{
    if (type == "deposit")
    {
        return new Deposit(amount);
    }
    else if (type == "withdraw")
    {
        return new Withdraw(amount);
    }
    return nullptr;
}
