#include "src/window/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "en");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
