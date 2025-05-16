#include "mainwindow.h"
#include <QApplication>
#include "account.h"
#include <vector>

Date tdate(2008,11,1);
std::vector<Account*> accounts;
Date*ptdate=&tdate;
std::vector<Account*>* paccounts = &accounts;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
