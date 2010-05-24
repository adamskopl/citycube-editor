#include <QtGui>
#include <QtOpenGL>
#include "mainwindow.h"
#include <string.h>
#include <sstream>

#include "paintwidget.h"
#include "glwidget.h"

 MainWindow::MainWindow()
 {
     centralWidget = new QWidget;
     setCentralWidget(centralWidget);

     reportWidget = new QTextEdit;
     reportWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     reportWidget->setFixedSize(600,100);

     designWidget = new DesignWidget(reportWidget);
     previewWidget = new PreviewWidget;

     previewArea = new QScrollArea;
     previewArea->setWidget(previewWidget);
     //previewArea->setWidgetResizable(true);
     //previewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     //previewArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     previewArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     //previewArea->setMinimumSize(50, 50);
     previewArea->setFixedSize(300, 300);

     designArea = new QScrollArea;
     designArea->setWidget(designWidget);
     designArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     designArea->setMinimumSize(100, 100);
     designArea->setFixedSize(600, 600);

     createMenus();

     QGridLayout *centralLayout = new QGridLayout;
     centralLayout->addWidget(designArea, 0, 0, 2, 1);
     centralLayout->addWidget(previewArea, 0, 2);
     centralLayout->addWidget(reportWidget, 2, 0);
     centralWidget->setLayout(centralLayout);
     setLayout(centralLayout);

     setWindowTitle(tr("World Editor"));
     //resize(800, 600);

    designWidget->update();
 }

 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     helpMenu = menuBar()->addMenu(tr("&Help"));
 }

 void MainWindow::mousePressEvent(QMouseEvent *event)
 {
 }

