#include <QtGui>
#include <QtOpenGL>
#include "mainwindow.h"
#include <string.h>
#include <sstream>

#include "paintwidget.h"
#include "glwidget.h"

 MainWindow::MainWindow()
 {
     globals = new globalContainer();
     maxFloorsAmount = 20;

     centralWidget = new QWidget;
     setCentralWidget(centralWidget);

     reportWidget = new QTextEdit;
     reportWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     reportWidget->setFixedSize(600,100);

     designWidget = new DesignWidget(globals, reportWidget);
     previewWidget1 = new PreviewWidget(globals);
     previewWidget2 = new PreviewWidget(globals);

     previewArea1 = new QScrollArea;
     previewArea1->setWidget(previewWidget1);
     previewArea1->setWidgetResizable(true);
     //previewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     //previewArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     previewArea1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     //previewArea->setMinimumSize(50, 50);
     previewArea1->setFixedSize(300, 300);

     previewArea2 = new QScrollArea;
     previewArea2->setWidget(previewWidget2);
     previewArea2->setWidgetResizable(true);
     //previewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     //previewArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     previewArea2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     //previewArea->setMinimumSize(50, 50);
     previewArea2->setFixedSize(300, 300);


     designArea = new QScrollArea;
     designArea->setWidget(designWidget);
     designArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     designArea->setMinimumSize(100, 100);
     designArea->setFixedSize(600, 600);

     ///////////////////////////////////////////////////////
     QGroupBox *toolsGroup = new QGroupBox(tr("Tools"));
     QGroupBox *fieldEditGroup = new QGroupBox(tr("Field"));
     QGroupBox *floorsGroup = new QGroupBox(tr("Floors"));
     QGroupBox *floorChooseGroup = new QGroupBox();


     QPushButton *newFloorButton = new QPushButton(tr("ADD"));

     QLabel *floorLabel = new QLabel(tr("floor:"));
     floorsComboBox = globals -> floorsComboBox;

    //add button for adding new floors
     for(int cnt = 0; cnt < *(globals -> floorsAmount); cnt++)
     {
         QString *floorName = new QString("floor" + QString::number(cnt));
         floorsComboBox -> addItem(tr(floorName->toAscii()));
     }

     connect(newFloorButton, SIGNAL(clicked()),
             this, SLOT(slotNewFloor()));
     connect(floorsComboBox, SIGNAL(activated(int)),
             this, SLOT(slotFloorChanged(int)));

     floorChooseLayout = new QGridLayout();
     floorChooseLayout -> addWidget(floorLabel, 0, 0, Qt::AlignTop);
     floorChooseLayout -> addWidget(floorsComboBox, 0, 1, Qt::AlignTop);
     floorChooseLayout -> addWidget(newFloorButton,0,2,Qt::AlignTop);
     floorChooseGroup -> setLayout(floorChooseLayout);

     QCheckBox *drawBox1 = new QCheckBox(tr("draw"));
     QCheckBox *drawBox2 = new QCheckBox(tr("draw"));
     QCheckBox *drawBox3 = new QCheckBox(tr("draw"));
     QLabel *floorLabel1 = new QLabel(tr("floor:"));
     QLabel *floorLabel2 = new QLabel(tr("floor:"));

     QGridLayout *drawLayout = new QGridLayout;
     QGroupBox *drawGroup = new QGroupBox(tr("draw floors"));


     fieldEditLayout = new QGridLayout;
     fieldEditGroup -> setLayout(fieldEditLayout);

     floorsLayout = new QGridLayout;

     QGroupBox *floorsList1 = new QGroupBox();
     QGroupBox *floorsList2 = new QGroupBox();
     QGridLayout *floorsList1Layout = new QGridLayout();
     QGridLayout *floorsList2Layout = new QGridLayout();


     for(int cnt = 0; cnt < maxFloorsAmount/2; cnt++)
     {
         floorsLabels[cnt].setText("floor"+QString::number(cnt));
         floorsList1Layout -> addWidget(&floorsLabels[cnt], cnt+1,1, 1, 1, Qt::AlignTop);

         floorsList1Layout -> addWidget(&drawBoxes[cnt], cnt+1,2, 1, 1, Qt::AlignTop);
         floorsList1Layout -> addWidget(&renderBoxes[cnt], cnt+1,3, 1, 1, Qt::AlignTop);

         if(cnt >= *(globals->floorsAmount))
         {
             drawBoxes[cnt].setDisabled(true);
             renderBoxes[cnt].setDisabled(true);
         }
         else
         {
             drawBoxes[cnt].setChecked(true);
             renderBoxes[cnt].setChecked(true);
         }

         connect(&drawBoxes[cnt], SIGNAL(toggled(bool)),
                 this, SLOT(changeFloorsView()));
         connect(&renderBoxes[cnt], SIGNAL(toggled(bool)),
                 this, SLOT(changeFloorsView()));
     }
     for(int cnt = maxFloorsAmount/2; cnt < maxFloorsAmount; cnt++)
     {
         floorsLabels[cnt].setText("floor"+QString::number(cnt));
         floorsList2Layout -> addWidget(&floorsLabels[cnt], cnt+1-maxFloorsAmount/2,1, 1, 1, Qt::AlignTop);

         floorsList2Layout -> addWidget(&drawBoxes[cnt], cnt+1-maxFloorsAmount/2,2, 1, 1, Qt::AlignTop);
         floorsList2Layout -> addWidget(&renderBoxes[cnt], cnt+1-maxFloorsAmount/2,3, 1, 1, Qt::AlignTop);


         if(cnt >= *(globals->floorsAmount))
         {
             drawBoxes[cnt].setDisabled(true);
             renderBoxes[cnt].setDisabled(true);
         }
         else
         {
             drawBoxes[cnt].setChecked(true);
             renderBoxes[cnt].setChecked(true);
         }
         connect(&drawBoxes[cnt], SIGNAL(toggled(bool)),
                 this, SLOT(changeFloorsView()));
         connect(&renderBoxes[cnt], SIGNAL(toggled(bool)),
                 this, SLOT(changeFloorsView()));
     }

     floorsList1 -> setLayout(floorsList1Layout);
     floorsList2 -> setLayout(floorsList2Layout);

     floorsLayout -> addWidget(floorChooseGroup, 0, 1, 1, 2);
     floorsLayout -> addWidget(floorsList1, 1, 1);
     floorsLayout -> addWidget(floorsList2, 1, 2);
     floorsGroup -> setLayout(floorsLayout);

     toolsLayout = new QGridLayout;    
     toolsLayout -> addWidget(fieldEditGroup, 0, 0, 1, 1);
     toolsLayout -> addWidget(floorsGroup, 0, 1, 2, 1);
     //toolsLayout -> addWidget(floorLabel, 0, 0, Qt::AlignTop);
     //toolsLayout -> addWidget(floorsComboBox, 0, 1, Qt::AlignTop);
     //toolsLayout -> addWidget(newFloorButton,0,2,Qt::AlignTop);
     //toolsLayout -> addWidget(drawGroup, 1,0,1,1, Qt::AlignLeft);
     //     toolsLayout -> addWidget(drawBox1,1,0,Qt::AlignLeft);
//     toolsLayout -> addWidget(drawBox2,2,0,Qt::AlignLeft);
//     toolsLayout -> addWidget(drawBox3,3,0,Qt::AlignLeft);
//     toolsLayout -> addWidget(floorLabel1,1,1,Qt::AlignLeft);
//     toolsLayout -> addWidget(floorLabel2,2,1,Qt::AlignLeft);

     toolsGroup -> setLayout(toolsLayout);
     toolsGroup -> setFixedWidth(600);



     ///////////////////////////////////////////////////////
     createMenus();

     QGridLayout *centralLayout = new QGridLayout;
     centralLayout->addWidget(designArea, 0, 0, 2, 1);
     centralLayout->addWidget(previewArea1, 0, 1, 1, 1);
     centralLayout->addWidget(previewArea2, 0, 2, 1, 1);
     centralLayout->addWidget(reportWidget, 2, 0);
     centralLayout->addWidget(toolsGroup, 1, 1, 2, 2);
     centralWidget->setLayout(centralLayout);
     //setLayout(centralLayout);

     setWindowTitle(tr("World Editor"));
     //resize(800, 600);

    designWidget->update();
    previewWidget1->update();
 }

 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu = menuBar()->addMenu(tr("&View"));
     helpMenu = menuBar()->addMenu(tr("&Help"));
 }

 void MainWindow::mousePressEvent(QMouseEvent *event)
 {
 }

 void MainWindow::slotFloorChanged(int floorIndex)
 {
     //activate florIndexed floor
     globals -> changeFloor(floorIndex);
     designWidget -> setFocus();
 }

 void MainWindow::slotNewFloor()
 {
QLabel *floorLabel3 = new QLabel(tr("floor:"));
     toolsLayout -> addWidget(floorLabel3,3,1,Qt::AlignLeft);
     *(globals -> appState) = addingFloor;
     designWidget -> setFocus();
 }

 void MainWindow::changeFloorsView()
 {

     printf("!\n");
     LObject *actualFloor;
     int cnt = 0;

     //for every floor draw its fields
     if(globals -> floorsTree -> hasChild())
         actualFloor = ((LField*)(globals -> floorsTree -> child));

     //break this while(), when last floor is drawn
     while(1)
     {\
        LField *helpField = (LField*)actualFloor;

         if( ! drawBoxes[cnt].isChecked())
             helpField -> draw = false;
         else
             helpField -> draw = true;

         if( ! renderBoxes[cnt].isChecked())
             helpField -> render = false;
         else
             helpField -> render = true;


         if(actualFloor -> isLast())
             break;
         actualFloor = (LField*)actualFloor -> next;
         cnt ++;
     }

     designWidget -> setFocus();
 }
