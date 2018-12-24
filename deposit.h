#ifndef DEPOSIT_H
#define DEPOSIT_H
#include "transaction.h"
#include <QDebug>
class Deposit : public Transaction
{
public:
    Deposit(unsigned int amount);
    unsigned int process(unsigned int account_amount, QString & error);
    QString getType();
    ~Deposit();
};

#endif // DEPOSIT_H
