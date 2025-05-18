#include "account.h"
#include <vector>
#include <QString>

SavingsAccount::SavingsAccount(Date triDate, QString strid, double rate,QString passa) :Account(strid, 0, rate,passa) {
    accumulation = 0;
    date = triDate;
    //printDate(triDate);
}
QString Account::getid(){
    return id;
}
void Date::setDate(int a,int b,int c){
    year=a;month=b;day=c;//record
}




double Account::total = 0;
std::multimap<Date, AccountRecord> Account::recordmap;//相当于元素为std::multimap<Date, AccountRecord>的容器
double Account::getTotal() {
    return total;
}
void Account::record(Date date, double amount, Account* cur) {
    AccountRecord a;
    a.date = date;
    a.amount = amount;
    a.account = cur;
    a.balance = cur->balance;
    recordmap.insert(std::pair<Date, AccountRecord>(date, a));
}
void Account::query(Date date1, Date date2) {
    std::multimap<Date, AccountRecord>::iterator iter;//迭代器相当于一个结构体，类型为std::multimap<Date, AccountRecord>
    for (iter = recordmap.begin(); iter != recordmap.end(); iter++) {
        if (iter->first < date1)continue;
        if (iter->first > date2)break;
        printDate(iter->first);
        /*
        std::cout << ' ' << iter->second.account->id;
        std::cout << ' ' << iter->second.amount
                  << ' ' << iter->second.balance << std::endl;
*/
    }
}
double SavingsAccount::accumulate(Date date) {
    accumulation += diffDate(this->date, date) * balance;
    this->date = date;
    return accumulation;
}
void SavingsAccount::deposit(Date date, double amount, QString thing) {
    accumulation = accumulate(date);//把之前余额的利息结一下
    balance += amount;//增加余额
    printDate(date);
    /*
    std::cout << '#' << id << ' ' << std::left << std::setw(8) << amount
              << std::setw(8) << balance << thing << std::endl;
*/
    total += amount;
    record(date, amount, this);
}
void SavingsAccount::withdraw(Date date, double amount, QString thing) {
    accumulation = accumulate(date);
    balance -= amount;
    printDate(date);
    /*
    std::cout << '#' << id << ' ' << std::left << std::setw(8) << -amount
              << std::setw(8) << balance << thing << std::endl;*/
    total -= amount;
    record(date, -amount, this);
}
void SavingsAccount::settle(Date date) {
    accumulation = accumulate(date);
    double tail = accumulation * rate / 366;
    tail = floor(tail * 100 + 0.5) / 100;
    balance += tail;
    printDate(date);/*
    std::cout << '#' << id << ' ' << std::setw(8) << tail << balance
              << "   interest" << std::endl;*/
    accumulation = 0;
}
void SavingsAccount::show() {/*
    std::cout << std::left << std::setw(18) << id << "Balance: " << balance;*/
}






Date::Date() :year(0), month(0), day(0) {}
Date::Date(const Date& a) {
    year = a.year; month = a.month; day = a.day;
}
Date::Date(int a, int b, int c) : year(a), month(b), day(c) {}
bool isLeapYear(int a) {
    if ((!(a % 4) && (a % 100)) || !(a % 400))return true;
    else return false;
}
int diffDate(Date da, Date db) {
    if (da.year == db.year && da.month == db.month && da.day == db.day)return 0;
    if(da.year == db.year && da.month == db.month)
        return db.day - da.day;
    int ya = da.year, yb = db.year;
    int days = 0;
    for (int i = ya + 1; i < yb; i++) {
        if (isLeapYear(i))days += 366;
        else days += 365;
    }
    for (int i = da.month + 1; i < 13; i++) {
        if (yb == ya) {
            break;
        }
        days += monthDays(ya, i);
    }
    for (int i = 1; i < db.month; i++) {
        if (yb == ya) {
            i = da.month;
            continue;
        }
        days += monthDays(yb, i);
    }
    days += monthDays(ya, da.month) - da.day;
    days += db.day;
    return days;
}
int monthDays(int y, int m) {
    int bigMonth[7] = { 1,3,5,7,8,10,12 };
    int littleMonth[4] = { 4,6,9,11 };
    for (int i = 0; i < 7; i++) {
        if (m == bigMonth[i])return 31;
    }
    for (int i = 0; i < 4; i++) {
        if (m == littleMonth[i])return 30;
    }
    if (isLeapYear(y))return 29;
    else return 28;
}
void printDate(Date a) {
    //std::cout << a.year << '-' << a.month << '-' << std::left << std::setw(10) << a.day;
}
bool toDouble(QString a,double&b){
    bool ok;
    b=a.toDouble(&ok);
    if(ok)
        return true;
    else
        return false;
}
bool isLetter(char a) {
    if (a >= 'a' && a <= 'z')return true;
    if (a >= 'A' && a <= 'Z')return true;
    return false;
}
