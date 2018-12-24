#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "walletserver.h"
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeName(const QString & name);
    void changeInfo(const QString & info);
    void listTransactions(const QVector<QStringList> & transactions);

private:
    Ui::MainWindow *ui;
    Server * server;
    QGridLayout * mainLayout;
};

#endif // MAINWINDOW_H
