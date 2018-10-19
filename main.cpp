#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName(QString("ARCSOLU"));
    QCoreApplication::setApplicationName(QString("VtPrdStat"));
    MainWindow w;
    w.setWindowTitle("VtPrdStat");
    w.show();

    return a.exec();
}
