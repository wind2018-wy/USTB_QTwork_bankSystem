#include "managewd.h"
#include "ui_managewd.h"

manageWD::manageWD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::manageWD)
{
    ui->setupUi(this);
}

manageWD::~manageWD()
{
    delete ui;
}

void manageWD::recvManaWD(){
    this->show();
}
