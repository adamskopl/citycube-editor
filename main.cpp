#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "welcomewindow.h"
#include "lucidbeaver.h"

#include <counter.h>
#include <primitives/field.h>
#include <primitives/lbstairs.h>
#include <primitives/lbpassage.h>
#include <primitives/floor.h>

using namespace std;

int main(int argc, char *argv[])
{

    lucidBeaver beaver;

    QApplication app(argc, argv);
    MainWindow mainWin;
    welcomeWindow welcomeWin;

    welcomeWin.setWindowFlags(Qt::FramelessWindowHint);


    mainWin.show();
    //welcomeWin.show();

    /*    cout << "application ends: what wasn't deleted?" << endl <<
            "floors: " << Counter<LBFloor>::howMany() << endl <<
            "stairs: " << Counter<LBStairs>::howMany() << endl <<
            "fields: " << Counter<LField>::howMany() << endl <<
            "passages: " << Counter<lbpassage>::howMany() << endl;
    */
            return app.exec();
}

