#ifndef OPERATEWD_H
#define OPERATEWD_H

#include <QWidget>
#include "account.h"

namespace Ui {
class operateWD;
}

class operateWD : public QWidget
{
    Q_OBJECT

public:
    Date* ptdate;
    std::vector<Account*>* paccounts;
    int index;
    explicit operateWD(QWidget *parent = nullptr,Date* =nullptr,std::vector<Account*>* =nullptr,int=0);
    ~operateWD();
private slots:
    void recvOperateWD();

private:
    Ui::operateWD *ui;
};

#endif // OPERATEWD_H
