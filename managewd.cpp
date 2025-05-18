#include "managewd.h"
#include "ui_managewd.h"
#include "account.h"
#include <QDebug>

manageWD::manageWD(QWidget *parent,Date* ttdate,std::vector<Account*>* accountss)
    : QWidget(parent)
    , ui(new Ui::manageWD)
{
    ui->setupUi(this);
    ptdate=ttdate;
    paccounts=accountss;
}

manageWD::~manageWD()
{
    delete ui;
}

void manageWD::recvManaWD(){
    this->show();
}

void manageWD::on_bShow_clicked()
{
    std::size_t length;
    if (paccounts != nullptr) {
        length = paccounts->size();
    } else {
        return;
    }
    ui->accountsShow->setRowCount(length+1);
    ui->accountsShow->setColumnCount(3);
    for (int i = 0; i < length; ++i) {
        QTableWidgetItem* item1 = new QTableWidgetItem((*paccounts)[i]->id);
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::number((*paccounts)[i]->balance));
        QTableWidgetItem* item3 = new QTableWidgetItem(
            ((*paccounts)[i]->id[0] == 'C') ? "信用卡" : "储蓄卡"
            );
        ui->accountsShow->setItem(i, 0, item1);
        ui->accountsShow->setItem(i, 1, item2);
        ui->accountsShow->setItem(i, 2, item3);
    }
}

