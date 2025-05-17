#include "account.h"
#include <QString>


CreditAccount::CreditAccount(Date triDate, QString strid, double credit, double rate, double fee,QString passa) :Account(strid, 0, rate,passa,credit),  fee(fee){
    accumulation = 0;
    this->date = triDate;
}
double CreditAccount::accumulate(Date date) {
    if (balance >= 0)
        return 0;
    accumulation += diffDate(this->date, date) * balance;

    this->date = date;
    return accumulation;
}
void CreditAccount::deposit(Date date, double amount, QString thing) {
    accumulation = accumulate(date);
    balance += amount;
    printDate(date);/*
    std::cout << '#' << id << ' ' << std::left << std::setw(8) << amount
              << std::setw(8) << balance << thing << std::endl;*/
    total += amount;
    record(date, amount, this);
}
void CreditAccount::withdraw(Date date, double amount, QString thing) {
    accumulation = accumulate(date);
    balance -= amount;
    printDate(date);/*
    std::cout << '#' << id << ' ' << std::left << std::setw(8) << -amount
              << std::setw(8) << balance << thing << std::endl;*/
    total -= amount;
    record(date, -amount, this);
}
void CreditAccount::settle(Date date) {
    double tail = 0;
    accumulation = accumulate(date);
    this->date = date;
    tail = accumulation * rate;
    tail = floor(tail * 100 + 0.5) / 100;
    balance += tail;
    if (date.month == 1 && date.day == 1) {
        balance -= fee; tail -= fee;
    }

    printDate(date);/*
    std::cout << '#' << id << ' ' << std::setw(8) << tail << balance;
    if (date.month == 1 && date.day == 1)std::cout << "   annual fee" << std::endl;
    else std::cout << "   interest" << std::endl;*/
    accumulation = 0;
}
void CreditAccount::show() {/*
    std::cout << std::left << std::setw(18) << id << "Balance: " << balance
              << "  Available credit: " << credit + balance;*/
}
