#include <QApplication>

#include "mainwindow.h"
#include "welcomewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
    welcomeWindow welcomeWin;

    welcomeWin.setWindowFlags(Qt::FramelessWindowHint);


    mainWin.show();
    //welcomeWin.show();

    return app.exec();
}

