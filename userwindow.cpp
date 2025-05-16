#include "userwindow.h"
#include "ui_userwindow.h"
#include "account.h"
#include "global.h"
#include <QString>
#include <vector>
#include <map>
#include <QDebug>
#include <QMessageBox>
#include "operatewd.h"
userWindow::userWindow(QWidget *parent,Date* ttdate,std::vector<Account*>* accountss)
    : QWidget(parent)
    , ui(new Ui::userWindow)
{
    ui->setupUi(this);
    ptdate=ttdate;
    paccounts=accountss;
}

userWindow::~userWindow()
{
    delete ui;
}
void userWindow::recvUserSlots(){
    this->show();
}

void userWindow::on_sign_clicked()
{
    QString tname=ui->nameE->text();
    QString tpass=ui->passE->text();
    int lengtha=(*paccounts).size();
    bool getAccount=false;
    int numAccount=-1;
    for(int i=0;i<lengtha;i++){
        if(tname==(*paccounts)[i]->id){
            if(tpass==(*paccounts)[i]->pass){
                getAccount=true;numAccount=i;
            }
            else{
                getAccount=true;
                QMessageBox::warning(this,tr("warning"),tr("密码错误，请重新输入"));
                return;
            }
        }
    }
    if(!getAccount){
        QMessageBox::warning(this,tr("warning"),tr("未找到该用户"));
        return;
    }

    static operateWD riwin(nullptr,ptdate,paccounts,numAccount);
    QObject::connect(this,SIGNAL(showOperateWD()),&riwin,SLOT(recvOperateWD()));
    emit showOperateWD();

}

