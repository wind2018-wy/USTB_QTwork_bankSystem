#include "mainwindow.h"
#include <QApplication>
#include "account.h"
#include <vector>
#include <QDebug>
#include <fstream>

Date tdate(2008,11,1);
std::vector<Account*> accounts;
Date*ptdate=&tdate;
std::vector<Account*>* paccounts = &accounts;
int main(int argc, char *argv[])
{
    accounts.clear();
    QApplication a(argc, argv);
    MainWindow w;
    std::string aCommand="";
    int index;
    char c,type;
    QString cc,cthing,id,mpass,desc;
    double mrate,mcredit,mfee,amount;
    int cIndex=0;
    int blankIndex;
    Account *account;
    std::vector<std::string> getCommands;
    std::ifstream file("commands.txt");
    if (file.is_open()) {
        while (std::getline(file, aCommand)) {
            if (aCommand.length() != 0) {
                getCommands.push_back(aCommand);
            }
        }
        file.close();
    }
    else {
        qDebug()<<"打不开txt文件";
    }
    int commandsLength = getCommands.size();
    int commandTake=0;



    for(;;){
        if(commandTake>=commandsLength)
            break;
        aCommand=getCommands[commandTake];

        if(aCommand.length()==0)
            continue;

        c=aCommand[cIndex];
        cIndex+=2;
        if(c=='a'){
            type=aCommand[cIndex];
            cIndex+=2;
            blankIndex = aCommand.find(' ', cIndex);
            id = QString::fromStdString(aCommand.substr(cIndex, blankIndex - cIndex));
            cIndex=blankIndex+1;
            blankIndex = aCommand.find(' ', cIndex);
            mpass  = QString::fromStdString(aCommand.substr(cIndex, blankIndex - cIndex));
            cIndex=blankIndex+1;
            if(type=='s'){
                mrate = std::stod(aCommand.substr(cIndex));
                account = new SavingsAccount((*ptdate), id, mrate,mpass);
            }
            else{
                blankIndex = aCommand.find(' ', cIndex);
                mcredit = std::stod(aCommand.substr(cIndex, blankIndex - cIndex));
                cIndex = blankIndex + 1;
                blankIndex = aCommand.find(' ', cIndex);
                mrate = std::stod(aCommand.substr(cIndex, blankIndex - cIndex));
                cIndex = blankIndex + 1;//stod
                blankIndex = aCommand.find(' ', cIndex);
                mfee = std::stod(aCommand.substr(cIndex));
                cIndex = blankIndex + 1;
                account = new CreditAccount((*ptdate), id,mcredit, mrate, mfee,mpass);
            }
            (*paccounts).push_back(account);

        }

        if(c=='d'){
            blankIndex = aCommand.find(' ', cIndex);
            index = std::stod(aCommand.substr(cIndex, blankIndex - cIndex));
            cIndex = blankIndex + 1;
            if (aCommand.find(' ', cIndex) == std::string::npos) {
                amount = std::stod(aCommand.substr(cIndex));
                desc = "";
            }
            else {
                blankIndex = aCommand.find(' ', cIndex);
                amount = std::stod(aCommand.substr(cIndex, blankIndex - cIndex));
                cIndex = blankIndex + 1;
                desc = QString::fromStdString(aCommand.substr(cIndex));
            }
            (*paccounts)[index]->deposit((*ptdate), amount, desc);
        }

        if(c=='w'){
            blankIndex = aCommand.find(' ', cIndex);
            index = std::stod(aCommand.substr(cIndex, blankIndex - cIndex));
            cIndex = blankIndex + 1;
            if (aCommand.find(' ', cIndex) == std::string::npos) {
                amount = std::stod(aCommand.substr(cIndex));
                desc = "";
            }
            else {
                blankIndex = aCommand.find(' ', cIndex);
                amount = std::stod(aCommand.substr(cIndex, blankIndex - cIndex));
                cIndex = blankIndex + 1;
                desc = QString::fromStdString(aCommand.substr(cIndex));
            }
            (*paccounts)[index]->withdraw((*ptdate), amount, desc);
        }

        if(c=='c'){
            int day=std::stod(aCommand.substr(cIndex));
            int month=(*ptdate).month,year=(*ptdate).year;

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
        }

        if(c=='n'){
            int day=1,month,year;
            if((*ptdate).month==12){
                month=1;year=(*ptdate).year+1;
            }
            else{
                month++;
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
        }

        if(c=='q'){
            /*
            std::string d2=aCommand.substr(cIndex);
            int year1=std::stoi(d2.substr(0,4)),month1=std::stoi(d2.substr(5,2)),day1=std::stoi(d2.substr(8,2));
            int year2=std::stoi(d2.substr(0,4)),month2=std::stoi(d2.substr(5,2)),day2=std::stoi(d2.substr(8,2));
            Date date1,date2;
            date1.setDate(year1,month1,day1);
            date2.setDate(year2,month2,day2);
            std::multimap<Date, AccountRecord>::iterator iter;//迭代器相当于一个结构体，类型为std::multimap<Date, AccountRecord>
            for (iter = (*paccounts)[index]->recordmap.begin(); iter != (*paccounts)[index]->recordmap.end(); iter++) {
                if (iter->first < date1)continue;
                if (iter->first > date2)break;
                //ui->queryBrow->setText(QString::number(iter->first.year)+'-'+QString::number(iter->first.month)+'-'+QString::number(iter->first.day)+"          "+iter->second.account->id+' '+QString::number(iter->second.balance));

            }
*/
        }
        commandTake++;
        cIndex=0;
    }

    w.show();

    return a.exec();
}
