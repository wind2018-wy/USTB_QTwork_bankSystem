#ifndef MANAGEWD_H
#define MANAGEWD_H

#include"account.h"
#include <QWidget>

namespace Ui {
class manageWD;
}

class manageWD : public QWidget
{
    Q_OBJECT

public:
    Date* ptdate;
    std::vector<Account*>* paccounts;
    explicit manageWD(QWidget *parent = nullptr,Date* =nullptr,std::vector<Account*>* =nullptr);
    ~manageWD();
private slots:
    void recvManaWD();
    void on_bShow_clicked();

private:
    Ui::manageWD *ui;
};

#endif // MANAGEWD_H
