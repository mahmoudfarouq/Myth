#include "mainwindow.h"
#include "entringdialog.h"
#include "winningdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    EntringDialog d;
    d.show();

    return a.exec();
}


/*

DONT FORGET TO DELETE ALLLLLLLLLLLL THE ALLOCATED MEMORY, THIS APP IS SUCKS, SHIT

*/
