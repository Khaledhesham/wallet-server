#include "transaction.h"

Transaction::Transaction()
{
    this->amount = 0;
    this->date = QDateTime::currentDateTime();
    this->is_undone = false;
}

Transaction::Transaction(unsigned int amount)
{
    this->amount = amount;
    this->date = QDateTime::currentDateTime();
    this->is_undone = false;
}

void Transaction::undo()
{
    this->is_undone = true;
}

void Transaction::redo()
{
    this->is_undone = false;
}

bool Transaction::isUndone()
{
    return this->is_undone;
}

unsigned int Transaction::getAmount()
{
    return this->amount;
}

QDateTime Transaction::getDate()
{
    return this->date;
}

void Transaction::setAmount(unsigned int amount)
{
    this->amount = amount;
}

Transaction::~Transaction()
{
    delete this;
}
