#include "rigistwindow.h"
#include "ui_rigistwindow.h"
#include "account.h"
#include "global.h"
#include <vector>
#include <QMessageBox>
#include <QMultiMap>

rigistWindow::rigistWindow(QWidget *parent,Date* ttdate,std::vector<Account*>* accountss)
    : QWidget(parent)
    , ui(new Ui::rigistWindow)
{
    ui->setupUi(this);
    ptdate=ttdate;
    paccounts=accountss;
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
    double rate,credit,fee;
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
    if(name.length()==0){
        QMessageBox::warning(this,tr("warning"),tr("账户名不能为空"));
        return;
    }
    if(pass.length()==0){
        QMessageBox::warning(this,tr("warning"),tr("密码不能为空"));
        return;
    }
    bool ok=false;
    if(ui->rateEdit->text().length()==0){
        QMessageBox::warning(this,tr("warning"),tr("利率不能为空"));
        this->hide();
        return;
        ok=toDouble(ui->rateEdit->text(),rate);
        if(!ok){
            QMessageBox::warning(this,tr("warning"),tr("利率不是数字"));
            return;
        }
    }
    if(ui->checkCredit->checkState()==Qt::Checked&&ui->creditEdit->text().length()==0){
        QMessageBox::warning(this,tr("warning"),tr("信用额度不能为空"));
        this->hide();
        return;
        ok=toDouble(ui->creditEdit->text(),credit);
        if(!ok){
            QMessageBox::warning(this,tr("warning"),tr("信用额度不是数字"));
            return;
        }
    }
    if(ui->checkCredit->checkState()==Qt::Checked&&ui->feeEdit->text().length()==0){
        QMessageBox::warning(this,tr("warning"),tr("年费不能为空"));
        return;
        ok=toDouble(ui->feeEdit->text(),fee);
        if(!ok){
            QMessageBox::warning(this,tr("warning"),tr("年费不是数字"));
            return;
        }
    }

    rate=ui->rateEdit->text().toDouble();
    credit=ui->creditEdit->text().toDouble();
    fee=ui->feeEdit->text().toDouble();
    Account *account;
    if(ui->checkSaving->checkState()==Qt::Checked){
        account=new SavingsAccount(*ptdate,name,rate,pass);
    }
    else{
        account=new CreditAccount(*ptdate,name,credit,rate,fee,pass);
    }


    if(name[0]!='C'&&ui->checkCredit->checkState()==Qt::Checked){
        QMessageBox::warning(this,tr("warning"),tr("信用卡账户名应以大写字母C开头"));
        return;
    }
    int lengtha=(*paccounts).size();
    for(int i=0;i<lengtha;i++){
        if(name==(*paccounts)[i]->id){
            QMessageBox::warning(this,tr("warning"),tr("存在账户同名，请重新填写"));
            return;
        }
    }

    (*paccounts).push_back(account);
    QMessageBox::information(this, tr("Information"), tr("注册成功"));
    this->hide();
}

