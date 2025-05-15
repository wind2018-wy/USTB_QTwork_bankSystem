#include "rigistwindow.h"
#include "ui_rigistwindow.h"
#include "account.h"
#include "global.h"
#include <vector>
#include <QMessageBox>
#include <QMultiMap>
extern Date tdate;
extern vector<Account*> accounts;

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
    if(ui->checkSaving->checkState()==Qt::Checked&&ui->checkCredit->checkState()==Qt::Checked){
        QMessageBox::warning(this,tr("warning"),tr("只能选择一种账户类型"));
        return;
    }
    if(ui->checkSaving->checkState()!=Qt::Checked&&ui->checkCredit->checkState()!=Qt::Checked){
        QMessageBox::warning(this,tr("warning"),tr("请选择一种账户类型"));
        return;
    }
    QString name=ui->nameEdit->text();
    QString pass=ui->passEdit->text();
    double rate=ui->rateEdit->text().toDouble();
    double credit=ui->creditEdit->text().toDouble();
    double fee=ui->feeEdit->text().toDouble();
    Account *account;
    if(ui->checkSaving->checkState()==Qt::Checked){
        account=new SavingsAccount(tdate,name,rate,pass);
    }
    else{
        account=new CreditAccount(tdate,name,credit,rate,fee,pass);
    }

    accounts.push_back(account);
    this->hide();
}

