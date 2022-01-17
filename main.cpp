#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationVersion("1.0.0");
    QCoreApplication::setApplicationName("Contrast Checker");
    QCoreApplication::setOrganizationName("Contrast Checker");
    MainWindow w;
    w.show();
    return a.exec();
}
