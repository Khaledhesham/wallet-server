#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>
#include <transaction.h>
#include <QVector>
#include <QtMath>
#include <QDebug>

class Account
{
public:
    Account(const QString & name, const unsigned short & age, const QString & national_id, const QString & email, const QString & mobile_number, int accounts_count);

    //setters
    void setName(const QString & name);
    void setAge(const unsigned short & age);
    void setNationalId(const QString & national_id);
    void setEmail(const QString & email);
    void setMobileNumber(const QString & mobile_number);
    void setAmount(const unsigned int & amount);

    //getters
    QString getName();
    unsigned int getId();
    unsigned short getAge();
    QString getNationalId();
    QString getEmail();
    QString getMobileNumber();
    unsigned int getAmount();
    QVector<Transaction *> getTransactions();

    bool addTransaction(Transaction * transaction);
    void generateId(int accounts_count);
    ~Account();

private:
    unsigned int id;
    unsigned int amount;
    QString name;
    unsigned short age;
    QString national_id;
    QString email;
    QString mobile_number;
    QVector<Transaction *> transactions;

};

#endif // ACCOUNT_H
