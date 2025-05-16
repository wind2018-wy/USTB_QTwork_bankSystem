#include "operatewd.h"
#include "ui_operatewd.h"
#include "account.h"

operateWD::operateWD(QWidget *parent,Date* ptdatea,std::vector<Account*>* paccountsa,int indexa)
    : QWidget(parent)
    , ui(new Ui::operateWD)
{
    ui->setupUi(this);
    ptdate=ptdatea;
    paccounts=paccountsa;
    index=indexa;
}

operateWD::~operateWD()
{
    delete ui;
}
void operateWD::recvOperateWD(){
    this->show();
}
