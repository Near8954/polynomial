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
    for (auto l = db.get_head(); l != nullptr; l = l->getNext()) {
        ui->listWidget->addItem(QString::fromStdString(std::to_string(cnt) + ") ") + QString::fromStdString(l->toString()));
        ++cnt;
    }
}

void MainWindow::on_add_polynomial_button_clicked() {
    QString pol = QInputDialog::getText(this, "Input Polynomial", "Input Polynomial: ");
    try {
        auto p = new Polynomial(pol.toStdString());
        p->normalize();
        db.insert_back(p);
        rend();
    } catch(const WrongMonomial &mn) {
        QMessageBox mess;
        if (mn.c == 'Z') {
            mess.setText(QString::fromStdString(mn.errorType));
        } else {
            mess.setText(QString::fromStdString(mn.errorType) + QChar::fromLatin1(mn.c));
        }

        mess.exec();
    }
}


void MainWindow::on_remove_polynomial_button_clicked() {
    try {
        int n = QInputDialog::getInt(this, "Delete Polynomial", "Input id: ");
        if (n >= db.size()) {
            throw "Incorrect id";
        }
        Polynomial* p = db.get(n);
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
        Polynomial p1 = *db.get(id1);
        Polynomial p2 = *db.get(id2);
        Polynomial sm = p1 + p2;
        QString ans = QString::fromStdString(sm.toString());
        QMessageBox msgBox;
        msgBox.setText(ans);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Question);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            auto p3 = new Polynomial(sm);
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
        Polynomial p1 = *db.get(id1);
        Polynomial p2 = *db.get(id2);
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
        Polynomial p1 = *db.get(id1);
        Polynomial p2 = *db.get(id2);
        Polynomial sm = p1 * p2;
        QString ans = QString::fromStdString(sm.toString());
        QMessageBox msgBox;
        msgBox.setText(ans);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Question);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            auto p3 = new Polynomial(sm);
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"),
                                                    "../Polynomial/file.txt",
                                                    tr("Text files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setInformativeText("File dont exist");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString s = in.readLine();
        try {
            auto pol = new Polynomial(s.toStdString());
            db.insert_back(pol);
            rend();
        } catch(WrongMonomial mn) {
            QMessageBox msgBox;
            msgBox.setInformativeText(QString::fromStdString(mn.errorType));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
    file.close();
    rend();
}


void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "../Polynomial/file.txt",
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
    for (auto l = db.get_head(); l != nullptr; l=l->getNext()) {
        out << QString::fromStdString(l->toString()) << "\n";
    }
    file.close();
}


void MainWindow::on_value_clicked()
{
    int id = QInputDialog::getInt(this, "Id input", "Input id");
    try {
        Polynomial* p = db.get(id);
        std::set<char> vars;
        for (auto curr = p->getHead(); curr!= nullptr; curr=curr->next) {
            for (int i = 0; i < curr->powers.size(); ++i) {
                if (curr->powers[i]) {
                    vars.insert('a' + i);
                }
            }
        }
        std::vector<int64_t> powers(26, 0);
        for (auto e : vars) {
            std::string tmp = "";
            tmp.push_back(e);
            int val = QInputDialog::getInt(this, QString::fromStdString("Enter value for " + tmp), QString::fromStdString(tmp + ": "));
            powers[e - 'a'] = val;
        }
        int64_t valueInPoint = p->getValueInPoint(powers);
        QMessageBox mess;
        mess.setText(QString::fromStdString("Value in point is: " + std::to_string(valueInPoint)));
        mess.exec();
    }catch(char* c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
}


void MainWindow::on_multiply_3_clicked()
{
    int id = QInputDialog::getInt(this, "Enter Id", "Enter Id");
    try {
        auto p = db.get(id);
        std::vector<int64_t> v = p->getRoots();
        std::string ans;
        for (auto e : v) {
            ans += (std::to_string(e) + " ");
        }
        if (ans.empty()) {
            ans = "There is no roots";
        }
        QMessageBox mess;
        mess.setText(QString::fromStdString(ans));
        mess.exec();
    } catch(char *c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
}


void MainWindow::on_multiply_2_clicked()
{
    int id = QInputDialog::getInt(this, "Enter Id", "Enter Id");
    try {
        auto p = db.get(id);
        QString c = QInputDialog::getText(this, "Enter variable", "Enter variable");
        int n = QInputDialog::getInt(this, "Enter n", "Enter n");
        auto ans = p->getDerivative(n, c[0].toLatin1());
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(ans.toString()));
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setIcon(QMessageBox::Question);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            auto p3 = new Polynomial(ans);
            db.insert_back(p3);
            rend();
        }
    } catch(char *c) {
        QMessageBox mess;
        mess.setText(QString::fromStdString(c));
        mess.exec();
    }
}

