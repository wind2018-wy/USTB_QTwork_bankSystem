#ifndef MANAGEWD_H
#define MANAGEWD_H

#include <QWidget>

namespace Ui {
class manageWD;
}

class manageWD : public QWidget
{
    Q_OBJECT

public:
    explicit manageWD(QWidget *parent = nullptr);
    ~manageWD();
private slots:
    void recvManaWD();
private:
    Ui::manageWD *ui;
};

#endif // MANAGEWD_H
