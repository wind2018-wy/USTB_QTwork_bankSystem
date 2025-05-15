#include "rigistwindow.h"
#include "ui_rigistwindow.h"
#include "account.h"

rigistWindow::rigistWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::rigistWindow)
{
    ui->setupUi(this);
}

rigistWindow::~rigistWindow()
{
    delete ui;
}

void rigistWindow::recvRigistWindow(){
    this->show();
}

void rigistWindow::on_rigistOK_clicked()
{

}

