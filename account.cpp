#include "account.h"

Account::Account(const QString & name, const unsigned short & age, const QString & national_id, const QString & email, const QString & mobile_number,int accounts_count)
{
    this->name = name;
    this->age = age;
    this->national_id = national_id;
    this->email = email;
    this->mobile_number = mobile_number;
    this->generateId(accounts_count);
    this->amount = 0;
}

void Account::setName(const QString & name)
{
    this->name = name;
}

void Account::setAge(const unsigned short & age)
{
    this->age = age;
}

void Account::setNationalId(const QString & national_id)
{
    this->national_id = national_id;
}

void Account::setEmail(const QString & email)
{
    this->email = email;
}

void Account::setMobileNumber(const QString & mobile_number)
{
    this->mobile_number = mobile_number;
}


void Account::setAmount(const unsigned int & amount)
{
    this->amount = amount;
}

QString Account::getName()
{
    return this->name;
}

unsigned int Account::getId()
{
    return this->id;
}

unsigned short Account::getAge()
{
    return this->age;
}

QString Account::getNationalId()
{
    return this->national_id;
}

QString Account::getEmail()
{
    return this->email;
}

QString Account::getMobileNumber()
{
    return this->mobile_number;
}

unsigned int Account::getAmount()
{
    return this->amount;
}

QVector<Transaction *> Account::getTransactions()
{
    return this->transactions;
}

bool Account::addTransaction(Transaction * transaction)
{
    this->transactions.push_back(transaction);
    return true;
}

void Account::generateId(int accounts_count)
{
    unsigned int random_number = (rand() % 9) + 1;
    this->id = (random_number * static_cast<unsigned int>(pow(10,8))) + static_cast<unsigned int>(accounts_count);
}

Account::~Account()
{
    qDeleteAll(this->transactions);
    this->transactions.clear();
}
