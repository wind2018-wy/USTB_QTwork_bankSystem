#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rigistwindow.h"
#include <QObject>
#include "userwindow.h"
#include <vector>
#include "managewd.h"
extern Date* ptdate;
extern std::vector<Account*>* paccounts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttRigist_clicked()
{
    static rigistWindow riwin(nullptr,ptdate,paccounts);
    QObject::connect(this,SIGNAL(showRigistWindow()),&riwin,SLOT(recvRigistWindow()));
    emit showRigistWindow();
}


void MainWindow::on_buttSign_clicked()
{
    static userWindow riwin(nullptr,ptdate,paccounts);
    QObject::connect(this,SIGNAL(showUserWindow()),&riwin,SLOT(recvUserSlots()));
    emit showUserWindow();
}

void MainWindow::on_buttManage_clicked()
{
    static manageWD riwin(nullptr,ptdate,paccounts);
    QObject::connect(this,SIGNAL(showManaWD()),&riwin,SLOT(recvManaWD()));
    emit showManaWD();
}

