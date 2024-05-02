#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "../base/base.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void rend();
private slots:
    void on_add_polynomial_button_clicked();

    void on_remove_polynomial_button_clicked();

    void on_sum_button_clicked();

    void on_equal_button_clicked();

    void on_multiply_clicked();

    void on_load_clicked();

    void on_save_clicked();

    void on_value_clicked();

    void on_multiply_3_clicked();

    void on_multiply_2_clicked();

private:
    Ui::MainWindow *ui;
    base db;
};
#endif // MAINWINDOW_H
