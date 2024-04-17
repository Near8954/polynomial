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
    ui->listWidget->clear();
    int cnt = 0;
    for (auto l = db.get_head(); l != nullptr; l = l->get_next()) {
        ui->listWidget->addItem(QString::fromStdString(std::to_string(cnt) + ") ") + QString::fromStdString(l->to_string()));
        ++cnt;
    }
}

void MainWindow::on_add_polynomial_button_clicked() {
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


void MainWindow::on_remove_polynomial_button_clicked() {
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

void MainWindow::on_sum_button_clicked() {
    int id1 = QInputDialog::getInt(this, "Input first id", "Input first id");
    int id2 = QInputDialog::getInt(this, "Input second id", "Input second id");
    try {
        polynomial p1 = *db.get(id1);
        polynomial p2 = *db.get(id2);
        polynomial sm = p1 + p2;
        QString ans = QString::fromStdString(sm.to_string());
        QMessageBox msgBox;
        msgBox.setText(ans);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Question);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            auto p3 = new polynomial(sm);
            db.insert_back(p3);
            rend();
        }

    } catch (const char* c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
}
void MainWindow::on_equal_button_clicked()
{
    int id1 = QInputDialog::getInt(this, "Input first id", "Input first id");
    int id2 = QInputDialog::getInt(this, "Input second id", "Input second id");
    try {
        polynomial p1 = *db.get(id1);
        polynomial p2 = *db.get(id2);
        QMessageBox mess;
        std::string ans = "false";
        if (p1 == p2) {
            ans = "true";
        }
        mess.setText(QString::fromStdString(ans));
        mess.exec();
    } catch (const char* c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
}


void MainWindow::on_multiply_clicked()
{
    int id1 = QInputDialog::getInt(this, "Input first id", "Input first id");
    int id2 = QInputDialog::getInt(this, "Input second id", "Input second id");
    try {
        polynomial p1 = *db.get(id1);
        polynomial p2 = *db.get(id2);
        polynomial sm = p1 * p2;
        QString ans = QString::fromStdString(sm.to_string());
        QMessageBox msgBox;
        msgBox.setText(ans);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Question);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            auto p3 = new polynomial(sm);
            db.insert_back(p3);
            rend();
        }

    } catch (const char* c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
}


void MainWindow::on_load_clicked()
{

}


void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "../polynomial/file.txt",
                                                    tr("Text files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setInformativeText("File dont exist");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QTextStream out(&file);
    for (auto l = db.get_head(); l != nullptr; l=l->get_next()) {
        out << QString::fromStdString(l->to_string()) << "\n";
    }
    file.close();
}

