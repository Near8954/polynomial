/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *add_polynomial_button;
    QPushButton *remove_polynomial_button;
    QPushButton *sum_button;
    QPushButton *equal_button;
    QPushButton *save;
    QPushButton *load;
    QPushButton *value;
    QPushButton *multiply;
    QListWidget *listWidget;
    QPushButton *multiply_2;
    QPushButton *multiply_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        add_polynomial_button = new QPushButton(centralwidget);
        add_polynomial_button->setObjectName(QString::fromUtf8("add_polynomial_button"));
        add_polynomial_button->setGeometry(QRect(420, 10, 171, 41));
        remove_polynomial_button = new QPushButton(centralwidget);
        remove_polynomial_button->setObjectName(QString::fromUtf8("remove_polynomial_button"));
        remove_polynomial_button->setGeometry(QRect(620, 10, 171, 41));
        sum_button = new QPushButton(centralwidget);
        sum_button->setObjectName(QString::fromUtf8("sum_button"));
        sum_button->setGeometry(QRect(420, 60, 171, 41));
        equal_button = new QPushButton(centralwidget);
        equal_button->setObjectName(QString::fromUtf8("equal_button"));
        equal_button->setGeometry(QRect(620, 60, 171, 41));
        save = new QPushButton(centralwidget);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(620, 500, 171, 41));
        load = new QPushButton(centralwidget);
        load->setObjectName(QString::fromUtf8("load"));
        load->setGeometry(QRect(420, 500, 171, 41));
        value = new QPushButton(centralwidget);
        value->setObjectName(QString::fromUtf8("value"));
        value->setGeometry(QRect(620, 110, 171, 41));
        multiply = new QPushButton(centralwidget);
        multiply->setObjectName(QString::fromUtf8("multiply"));
        multiply->setGeometry(QRect(420, 110, 171, 41));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 401, 531));
        multiply_2 = new QPushButton(centralwidget);
        multiply_2->setObjectName(QString::fromUtf8("multiply_2"));
        multiply_2->setGeometry(QRect(420, 160, 171, 41));
        multiply_3 = new QPushButton(centralwidget);
        multiply_3->setObjectName(QString::fromUtf8("multiply_3"));
        multiply_3->setGeometry(QRect(620, 160, 171, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        add_polynomial_button->setText(QCoreApplication::translate("MainWindow", "add polynomial", nullptr));
        remove_polynomial_button->setText(QCoreApplication::translate("MainWindow", "remove polynomial", nullptr));
        sum_button->setText(QCoreApplication::translate("MainWindow", "sum", nullptr));
        equal_button->setText(QCoreApplication::translate("MainWindow", "equal", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
        load->setText(QCoreApplication::translate("MainWindow", "load", nullptr));
        value->setText(QCoreApplication::translate("MainWindow", "value", nullptr));
        multiply->setText(QCoreApplication::translate("MainWindow", "multiply", nullptr));
        multiply_2->setText(QCoreApplication::translate("MainWindow", "get derivative", nullptr));
        multiply_3->setText(QCoreApplication::translate("MainWindow", "roots", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
