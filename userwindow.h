#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>

namespace Ui {
class userWindow;
}

class userWindow : public QWidget
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = nullptr);
    ~userWindow();
private slots:
    void recvUserSlots();
private:
    Ui::userWindow *ui;
};

#endif // USERWINDOW_H
