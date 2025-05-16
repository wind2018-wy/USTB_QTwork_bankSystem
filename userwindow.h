#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "account.h"
#include <vector>

namespace Ui {
class userWindow;
}

class userWindow : public QWidget
{
    Q_OBJECT

public:
    Date* ptdate;
    std::vector<Account*>* paccounts;
    explicit userWindow(QWidget *parent = nullptr,Date* =nullptr,std::vector<Account*>* =nullptr);
    ~userWindow();
private slots:
    void recvUserSlots();
    void on_sign_clicked();
signals:
    void showOperateWD();
private:
    Ui::userWindow *ui;
};

#endif // USERWINDOW_H
