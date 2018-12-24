#ifndef TRANSACTIONBUILDER_H
#define TRANSACTIONBUILDER_H
#include "transaction.h"
#include <QString>
#include "deposit.h"
#include "withdraw.h"

class TransactionFactory
{
public:
    static Transaction *NewTransaction(const QString &type, unsigned int amount);
};

#endif // TRANSACTIONBUILDER_H
