#include <QApplication>

#include "mainwindow.h"
#include "welcomewindow.h"
#include "lucidbeaver.h"
int main(int argc, char *argv[])
{

    lucidBeaver beaver;

    QApplication app(argc, argv);
    MainWindow mainWin;
    welcomeWindow welcomeWin;

    welcomeWin.setWindowFlags(Qt::FramelessWindowHint);


    mainWin.show();
    //welcomeWin.show();

    return app.exec();
}

