#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDate>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDate current = QDate::currentDate();
    QDate endOfLicense(2012, 12, 1);  // December 1, 2012

    if(current < endOfLicense){
        MainWindow w;
        w.show();

        return a.exec();
    } else {
        return 0;
    }
}
