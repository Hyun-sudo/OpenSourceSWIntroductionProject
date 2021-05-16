#include "mainwindow.h"

#include <QApplication>


/*
 * Main function
 * 버스들과 Aura Controller를 찾고, main window에 연다.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
