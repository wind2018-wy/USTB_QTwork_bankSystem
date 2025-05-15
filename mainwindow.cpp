#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rigistwindow.h"
#include <QObject>
#include "userwindow.h"

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
    static rigistWindow riwin;
    QObject::connect(this,SIGNAL(showRigistWindow()),&riwin,SLOT(recvRigistWindow()));
    emit showRigistWindow();
}


void MainWindow::on_buttSign_clicked()
{
    static userWindow riwin;
    QObject::connect(this,SIGNAL(showUserWindow()),&riwin,SLOT(recvUserSlots()));
    emit showUserWindow();
}

