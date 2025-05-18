#ifndef ACCOUNT_H
#define ACCOUNT_H

#endif // ACCOUNT_H


//account.h
#pragma once
#include<iostream>
#include<string>
#include<map>
#include<any>
#include<vector>
#include<QString>
int monthDays(int, int);
class Date;
void printDate(Date);
bool isLetter(char);
bool toDouble(QString,double&);
class AccountRecord;
class Date {
public:
    int year, month, day;
    Date();
    Date(const Date&);
    Date(int, int, int);
    void setDate(int,int,int);
    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }
    int getMaxDay() { return monthDays(year, month); }
    void show() { printDate(*this); }
    bool operator < (const Date& date) const {
        if (year != date.year)return year < date.year;
        if (month != date.month)return month < date.month;
        return day < date.day;
    }
    bool operator>(const Date& date) const {
        if (year != date.year)return year > date.year;
        if (month != date.month)return month > date.month;
        return day > date.day;
    }
    static Date read(QString a) {
        Date da, db;
        da.year = a.mid(0, 4).toInt();
        da.month = a.mid(5, 2).toInt();
        da.day = a.mid(8, 2).toInt();
        return da;
    }
};
bool isLeapYear(int);
int diffDate(Date, Date);
class Account {
public:
    QString pass;
    Date date;
    QString id;
    QString getid();
    double credit;//信用额度
    double balance;
    double rate;
    double accumulation;
    static double total;
    Account(QString pid, double pbalance, double prate,QString passa) :id(pid), balance(pbalance), rate(prate),pass(passa) {}
    Account(QString pid, double pbalance, double prate,QString passa,double credita) :id(pid), balance(pbalance), rate(prate),pass(passa),credit(credita) {}
    static double getTotal();
    virtual void show() = 0;
    virtual void deposit(Date, double, QString) = 0;
    virtual void withdraw(Date, double, QString) = 0;
    virtual void settle(Date) = 0;
    static void record(Date, double, Account*);//记录
    static void query(Date, Date);//查询
    static std::multimap<Date, AccountRecord>recordmap;
};
class SavingsAccount :public Account {
public:

    SavingsAccount(Date, QString, double,QString);
    double accumulate(Date);
    void show();
    void deposit(Date, double, QString);
    void withdraw(Date, double, QString);
    void settle(Date);
};
class CreditAccount :public Account {
public:
    double fee;//年费
    CreditAccount(Date triDate, QString id, double credit, double rate, double fee,QString);
    void show();
    void deposit(Date, double, QString);
    void withdraw(Date, double, QString);
    void settle(Date);
    double accumulate(Date date);
};
class AccountRecord {
public:
    Date date;//日期
    const Account* account;//账户
    double amount;//金额
    double balance;//余额
    QString desc;//描述
};
