#ifndef RIGISTWINDOW_H
#define RIGISTWINDOW_H

#include <QWidget>
#include "account.h"

namespace Ui {
class rigistWindow;
}

class rigistWindow : public QWidget
{
    Q_OBJECT

public:
    Date* ptdate;
    std::vector<Account*>* paccounts;
    explicit rigistWindow(QWidget *parent = nullptr,Date* =nullptr,std::vector<Account*>* =nullptr);
    ~rigistWindow();
private slots:
    void recvRigistWindow();
    void on_rigistOK_clicked();

private:
    Ui::rigistWindow *ui;
};

#endif // RIGISTWINDOW_H
