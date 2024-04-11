#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rend() {
    ui->textEdit->setText(QString::fromStdString(db.to_string()));
}

void MainWindow::on_pushButton_clicked()
{
    QString pol = QInputDialog::getText(this, "Input polynomial", "Input polynomial: ");
    try {
        auto p = new polynomial(pol.toStdString());
        p->normalize();
        db.insert_back(p);
        rend();
    } catch(const wrong_monomial &mn) {
        QMessageBox mess;
        if (mn.c == 'Z') {
            mess.setText(QString::fromStdString(mn.error_type));
        } else {
            mess.setText(QString::fromStdString(mn.error_type) + QChar::fromLatin1(mn.c));
        }

        mess.exec();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    try {
        int n = QInputDialog::getInt(this, "Delete polynomial", "Input id: ");
        if (n >= db.size()) {
            throw "Incorrect id";
        }
        polynomial* p = db.get_head();
        for (int i = 0; i < n; ++i) {
            p = p->get_next();
        }
        db.remove(p);

    } catch(const char* c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
    rend();
}

