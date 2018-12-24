#include "deposit.h"

Deposit::Deposit(unsigned int amount) : Transaction (amount)
{

}

unsigned int Deposit::process(unsigned int account_amount, QString & error)
{
    if (!this->is_undone)
    {
        account_amount += this->amount;
        return account_amount;
    }
    else
    {
        if (this->amount > account_amount)
        {
            error = "Account amount is insufficient!";
            return 0;
        }
        account_amount -= this->amount;
        return account_amount;
    }
}

QString Deposit::getType()
{
    return "deposit";
}


Deposit::~Deposit()
{
    delete this;
}
