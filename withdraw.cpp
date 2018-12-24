#include "withdraw.h"

Withdraw::Withdraw(unsigned int amount) : Transaction (amount)
{

}

unsigned int Withdraw::process(unsigned int account_amount, QString & error)
{
    if (this->is_undone)
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

QString Withdraw::getType()
{
    return "withdraw";
}


Withdraw::~Withdraw()
{
    delete this;
}
