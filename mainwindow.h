#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttRigist_clicked();
    void on_buttSign_clicked();

    void on_buttManage_clicked();

signals:
    void showRigistWindow();
    void showUserWindow();
    void showManaWD();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
