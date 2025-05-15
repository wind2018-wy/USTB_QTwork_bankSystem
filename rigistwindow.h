#ifndef RIGISTWINDOW_H
#define RIGISTWINDOW_H

#include <QWidget>

namespace Ui {
class rigistWindow;
}

class rigistWindow : public QWidget
{
    Q_OBJECT

public:
    explicit rigistWindow(QWidget *parent = nullptr);
    ~rigistWindow();
private slots:
    void recvRigistWindow();
    void on_rigistOK_clicked();

private:
    Ui::rigistWindow *ui;
};

#endif // RIGISTWINDOW_H
