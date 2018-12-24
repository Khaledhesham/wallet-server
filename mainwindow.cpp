#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    QMainWindow::showMaximized();
    WalletServer * wallet = WalletServer::getInstance(this);
    qRegisterMetaType<QVector<QStringList> >("QVector<QStringList>");
    bool success;
    connect(wallet,SIGNAL(changeName(const QString &)),this,SLOT(changeName(const QString &)));
    connect(wallet,SIGNAL(changeInfo(const QString &)),this,SLOT(changeInfo(const QString &)));
    success =connect(wallet,SIGNAL(listTransactions(const QVector<QStringList> &)),this,SLOT(listTransactions(const QVector<QStringList> &)));
    qDebug() << success;
    server = new Server(wallet);
    server->startServer();

    setWindowTitle(tr("Smart Wallet Server"));
    this->ui->transactions->setColumnCount(5);
    QStringList headers;
    headers << "ID" << "TYPE" << "AMOUNT" << "DATE" << "UNDONE";
    this->ui->transactions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->transactions->setHorizontalHeaderLabels(headers);
}

void MainWindow::changeName(const QString & name)
{
    this->ui->name->setText(name);
}

void MainWindow::changeInfo(const QString & info)
{
    this->ui->info->setText(info);
}

void MainWindow::listTransactions(const QVector<QStringList> & transactions)
{
    qDebug() << "test";
    this->ui->transactions->clear();
    this->ui->transactions->setRowCount(transactions.size());
    for (auto r=0; r<transactions.size(); r++)
         for (auto c=0; c<5; c++)
         {
             this->ui->transactions->setItem( r, c, new QTableWidgetItem(transactions[r][c]));
             this->ui->transactions->item(r,c)->setTextAlignment(Qt::AlignCenter);
         }
    QStringList headers;
    headers << "ID" << "TYPE" << "AMOUNT" << "DATE" << "UNDONE";
    this->ui->transactions->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete server;
    WalletServer::destroy();
    delete ui;
}
