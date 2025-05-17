#include "operatewd.h"
#include "ui_operatewd.h"
#include "account.h"
#include <QString>
#include <QMessageBox>
#include <vector>
#include <iomanip>

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

void operateWD::on_bDeposit_clicked()
{
    bool ok;
    QString QSmoney=ui->moneyEdit->text();
    double amount=QSmoney.toDouble(&ok);
    if(!ok){
        QMessageBox::warning(this,tr("warning"),tr("请输入有效金额"));
        return;
    }
    if(amount<=0){
        QMessageBox::warning(this,tr("warning"),tr("金额应为正数"));
        return;
    }
    QString QSthing=ui->thingEdit->text();
    (*paccounts)[index]->deposit(*ptdate, amount, QSthing);
    QMessageBox::information(this, tr("提示"), tr("存钱成功"));
}


void operateWD::on_bWithdraw_clicked()
{
    bool ok;
    QString QSmoney=ui->moneyEdit->text();
    double amount=QSmoney.toDouble(&ok);
    if(!ok){
        QMessageBox::warning(this,tr("warning"),tr("请输入有效金额"));
        return;
    }
    if(amount<=0){
        QMessageBox::warning(this,tr("warning"),tr("金额应为正数"));
        return;
    }
    QString QSthing=ui->thingEdit->text();
    if((*paccounts)[index]->balance-amount<-(*paccounts)[index]->credit){
        QMessageBox::information(this, tr("提示"), tr("取钱失败，超出信用额度"));
    }
    (*paccounts)[index]->withdraw(*ptdate, amount, QSthing);
    QMessageBox::information(this, tr("提示"), tr("取钱成功"));
    clear:
    ui->moneyEdit->clear();
    ui->thingEdit->clear();
}


void operateWD::on_changeDate_clicked()
{
    Date datea=(*ptdate);
    QDate dateanow=ui->dateEdit->date();
    int year=dateanow.year();
    int month=dateanow.month();
    int day=dateanow.day();
    bool before=false;
    if(year>datea.year)
        goto beforea;
    if(year<datea.year){
        before=true;
        goto beforea;
    }
    if(month<datea.month){
        before=true;
        goto beforea;
    }
    if(month>datea.month)
        goto beforea;
    if(day<=datea.day)
        before=true;
    beforea:
    if(before){
        QMessageBox::warning(this,tr("warning"),tr("请输入当前日期之后的日期"));
        return;
    }

    for(;;){
        if(year>(*ptdate).year)
            goto monthTake;
        else{
            if(month>(*ptdate).month){
                goto monthTake;
            }
            else
                break;
        }
        monthTake:
        if ((*ptdate).getMonth() == 12)
            (*ptdate) = Date((*ptdate).getYear() + 1, 1, 1);
        else
            (*ptdate) = Date((*ptdate).getYear(), (*ptdate).getMonth() + 1, 1);
        for (std::vector<Account*>::iterator iter = (*paccounts).begin(); iter != (*paccounts).end(); iter++)
        {
            if ((*iter)->id[0] != 'C' && (*ptdate).getMonth() != 1)continue;
            else { (*iter)->settle((*ptdate)); }
        }
    }
        (*ptdate) = Date((*ptdate).getYear(), (*ptdate).getMonth(), day);
        int accountsLength = (*paccounts).size();
        for (int i = 0; i < accountsLength; i++) {
            if ((*paccounts)[i]->id[0] == 'C' && (*paccounts)[i]->balance >= 0) {
                (*paccounts)[i]->date = (*ptdate);
                continue;
            }
            else {
                (*paccounts)[i]->accumulation += diffDate((*paccounts)[i]->date, (*ptdate)) * (*paccounts)[i]->balance;
                (*paccounts)[i]->date = (*ptdate);
            }
        }
        QMessageBox::information(this, tr("提示"), tr("日期跳转成功"));
}


void operateWD::on_showMessage_clicked()
{
    Date date1,date2;
    QDate Qdate1=ui->dateBegin->date(),Qdate2=ui->dateEnd->date();
    date1.setDate(Qdate1.year(),Qdate1.month(),Qdate1.day());
    date2.setDate(Qdate2.year(),Qdate2.month(),Qdate2.day());
    if(date1>date2){
        QMessageBox::warning(this,tr("warning"),tr("结束日期应晚于起始日期"));
        return;
    }
    std::multimap<Date, AccountRecord>::iterator iter;//迭代器相当于一个结构体，类型为std::multimap<Date, AccountRecord>
    for (iter = (*paccounts)[index]->recordmap.begin(); iter != (*paccounts)[index]->recordmap.end(); iter++) {
        if (iter->first < date1)continue;
        if (iter->first > date2)break;
        ui->queryBrow->setText(QString::number(iter->first.year)+'-'+QString::number(iter->first.month)+'-'+QString::number(iter->first.day)+"          "+iter->second.account->id+' '+QString::number(iter->second.balance));

    }
}

