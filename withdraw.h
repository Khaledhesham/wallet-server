#ifndef WITHDRAW_H
#define WITHDRAW_H
#include "transaction.h"

class Withdraw : public Transaction
{
public:
    Withdraw(unsigned int amount);
    unsigned int process(unsigned int account_amount, QString & error);
    QString getType();
    ~Withdraw();
};

#endif // WITHDRAW_H
