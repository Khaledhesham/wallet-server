#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QDateTime>

class Transaction
{
public:
    Transaction();
    Transaction(unsigned int amount);
    void undo();
    void redo();
    void setAmount(unsigned int amont);
    unsigned int getAmount();
    bool isUndone();
    QDateTime getDate();
    virtual unsigned int process(unsigned int account_amount, QString & error) = 0;
    virtual QString getType() = 0;
    virtual ~Transaction();

protected:
    unsigned int amount;
    QDateTime date;
    bool is_undone;

};

#endif // TRANSACTION_H
