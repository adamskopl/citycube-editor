#include <QtGui>
#include <QtOpenGL>
#include "mainwindow.h"
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "paintwidget.h"
#include "designwidgetmini.h"
#include "glwidget.h"

MainWindow::MainWindow()
{
  (void)statusBar();

    globals = new globalContainer();
    xmlManager = new lbXMLmanager(globals);

    maxFloorsAmount = 20;

    centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    reportWidget = new QTextEdit;
    reportWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    reportWidget->setFixedSize(500,90);

    designWidgetMini = new DesignWidgetMini(globals);
    designWidget = new DesignWidget(globals, reportWidget, designWidgetMini);

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

    //previewArea2 = new QScrollArea;
    //    previewArea2->setWidget(previewWidget2);
    //    previewArea2->setWidgetResizable(true);
    //previewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //previewArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    previewArea2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //previewArea->setMinimumSize(50, 50);
    //    previewArea2->setFixedSize(300, 300);
    designAreaMini = new QScrollArea;
    designAreaMini->setWidget(designWidgetMini);
    designAreaMini->setWidgetResizable(true);
    designAreaMini->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    designAreaMini->setFixedSize(300, 300);


    designArea = new QScrollArea;
    //globals -> designArea = designArea;
    designArea->setWidget(designWidget);
    designArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    designArea->setMinimumSize(100, 100);
    designArea->setFixedSize(600, 600);

    //    designArea->horizontalScrollBar()->setSliderPosition(30);

    //erm ... are these kinds of connections OK ?
    connect(designArea -> horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(designAreaScrollBarXChanged(int)));
    connect(designArea -> verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(designAreaScrollBarYChanged(int)));

    ///////////////////////////////////////////////////////
    QGroupBox *toolsGroup = new QGroupBox(tr("Tools"));
    QGroupBox *fieldEditGroup = new QGroupBox(tr("Field"));
    QGroupBox *floorsGroup = new QGroupBox(tr("Floors"));
    QGroupBox *floorChooseGroup = new QGroupBox();
    QGroupBox *objectsGroup = new QGroupBox(tr("Objects"));


    QPushButton *newFloorButton = new QPushButton(tr("ADD"));

    QLabel *floorLabel = new QLabel(tr("floor:"));
    floorsComboBox = globals -> floorsComboBox;

    //add button for adding new floors
    /*    for(int cnt = 0; cnt < globals -> floorsAmount; cnt++)
    {
        QString *floorName = new QString("floor" + QString::number(cnt));
        floorsComboBox -> addItem(tr(floorName->toAscii()));
	}*/

    connect(newFloorButton, SIGNAL(clicked()),
            this, SLOT(slotNewFloor()));
    connect(floorsComboBox, SIGNAL(activated(int)),
            this, SLOT(slotFloorChanged(int)));

    floorChooseLayout = new QGridLayout();
    floorChooseLayout -> addWidget(floorLabel, 0, 0, Qt::AlignTop);
    floorChooseLayout -> addWidget(floorsComboBox, 0, 1, Qt::AlignTop);
    floorChooseLayout -> addWidget(newFloorButton,0,2,Qt::AlignTop);
    floorChooseGroup -> setLayout(floorChooseLayout);

    fieldEditLayout = new QHBoxLayout;
    /*    fieldEditLayout -> addWidget(fieldSliderOne);
    fieldEditLayout -> addWidget(fieldSliderTwo);
    fieldEditLayout -> addWidget(fieldSliderThree);
    fieldEditLayout -> addWidget(fieldSliderFour);
    */
    fieldEditGroup -> setLayout(fieldEditLayout);

    QVBoxLayout *objectsGroupLayout = new QVBoxLayout;
    QPushButton *newStairsButton = new QPushButton(tr("Stairs"));
    QPushButton *newWindowButton = new QPushButton(tr("Window"));
    QPushButton *newDoorsButton = new QPushButton(tr("Doors"));

    objectsGroupLayout -> addWidget(newStairsButton);
    objectsGroupLayout -> addWidget(newWindowButton);
    objectsGroupLayout -> addWidget(newDoorsButton);
    objectsGroup -> setLayout(objectsGroupLayout);

    connect(newStairsButton, SIGNAL(clicked()),
            this, SLOT(slotDefineStairs()));

    connect(newWindowButton, SIGNAL(clicked()),
            this, SLOT(slotDefineWindow()));

    connect(newDoorsButton, SIGNAL(clicked()),
	    this, SLOT(slotDefineDoors()));

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

	/*        if(cnt >= globals->floorsAmount)
        {
            drawBoxes[cnt].setDisabled(true);
            renderBoxes[cnt].setDisabled(true);
        }
        else
        {
            drawBoxes[cnt].setChecked(true);
            renderBoxes[cnt].setChecked(true);
	    }*/

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


        if(cnt >= globals->floorsAmount)
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
    toolsLayout -> addWidget(floorsGroup, 0, 1, 2, 1);
    toolsLayout -> addWidget(fieldEditGroup, 0, 0, 1, 1);
    toolsLayout -> addWidget(objectsGroup, 1, 0, 1, 1);

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
    createActions();

    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(designArea, 0, 0, 2, 1);
    centralLayout->addWidget(designAreaMini, 0, 2, 1, 1);
    centralLayout->addWidget(previewArea1, 0, 1, 1, 1);
    centralLayout->addWidget(reportWidget, 2, 0, 1, 2);
    //centralLayout->addWidget(globals -> stuffArea, 2, 0, 1, 1, Qt::AlignLeft);
    centralLayout->addWidget(toolsGroup, 1, 1, 2, 2);
    centralWidget->setLayout(centralLayout);
    //setLayout(centralLayout);

    centralLayout -> setMenuBar(menuBar);

    setWindowTitle(tr("World Editor"));
    //resize(800, 600);

    designWidget->update();
    previewWidget1->update();

    globals -> drawBoxes = drawBoxes;
    globals -> renderBoxes = renderBoxes;

    globals->addFloor(globals->giveFreeID(), globals->worldSize);
    //    globals->floorsAmount = 1;
}

void MainWindow::createMenus()
{
  menuBar = new QMenuBar;
//    fileMenu = menuBar()->addMenu(tr("&File"));
  //    fileMenu = menuBar()->addMenu(tr("&View"));
  //    helpMenu = menuBar()->addMenu(tr("&Help"));
  fileMenu = new QMenu(tr("&File"), this);
  helpMenu = new QMenu(tr("&Help"), this);
  menuBar -> addMenu(fileMenu);
  menuBar -> addMenu(helpMenu);
}

void
MainWindow::createActions()
{
  newFileAction = fileMenu->addAction(tr("&New building"));
  newFileAction->setShortcuts(QKeySequence::New);
  newFileAction->setStatusTip(tr("Create new building"));
  connect(newFileAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));

  loadXMLAction = fileMenu->addAction(tr("&Open XML file"));
  loadXMLAction->setShortcuts(QKeySequence::Open);
  loadXMLAction->setStatusTip(tr("Open existing XML lucidia building"));
  connect(loadXMLAction, SIGNAL(triggered()), this, SLOT(slotLoadXML()));

  saveXMLAction = fileMenu->addAction(tr("&Save as XML"));  
  saveXMLAction->setShortcuts(QKeySequence::Save);
  saveXMLAction->setStatusTip(tr("Save building as XML"));
  connect(saveXMLAction, SIGNAL(triggered()), this, SLOT(slotSaveAsXML()));

  aboutAction = helpMenu->addAction(tr("&About Lucidbeaver"));
  aboutAction->setStatusTip(tr("Short information about Lucidbeaver"));
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

void MainWindow::slotFloorChanged(int floorIndex)
{
    //activate florIndexed floor
    globals -> changeFloor(floorIndex);
    designWidget -> setFocus();
}

void MainWindow::slotNewFloor()
{
    //QLabel *floorLabel3 = new QLabel(tr("floor:"));
    //toolsLayout -> addWidget(floorLabel3,3,1,Qt::AlignLeft);
    *(globals -> appState) = addingFloor;
    designWidget -> setFocus();
}

void MainWindow::changeFloorsView()
{
    LBFloor *actualFloor;
    int cnt = 0;

    //for every floor draw its fields
    if(globals -> floorsTree -> hasChild())
        actualFloor = ((LBFloor*)(globals -> floorsTree -> child));
    else
      {
	//printError();
	//	printf("MainWindow:changeFloorsView error");
	return;
      }

    //break this while(), when last floor is drawn
    while(1)
    {
     LBFloor *helpFloor = (LBFloor*)actualFloor;

        if( ! drawBoxes[cnt].isChecked())
            helpFloor -> isItDrawn = false;
        else
            helpFloor -> isItDrawn = true;

        if( ! renderBoxes[cnt].isChecked())
            helpFloor -> isItRendered = false;
        else
            helpFloor -> isItRendered = true;


        if(actualFloor -> isLast())
            break;
        actualFloor = (LBFloor*)actualFloor -> next;
        cnt ++;
    }

    designWidget -> setFocus();
    //print check
    if(globals -> floorsTree -> hasChild())
        actualFloor = (LBFloor*)(globals -> floorsTree -> child);

    while(1)
    {    

        if(actualFloor -> isLast())
            break;

        actualFloor = (LBFloor*)(actualFloor -> next);
    }
}

void MainWindow::designAreaScrollBarXChanged(int x)
{
    designWidget -> scrollX = x;
    designWidget -> setFocus();
}

void MainWindow::designAreaScrollBarYChanged(int y)
{
    designWidget -> scrollY = y;
    designWidget -> setFocus();
}

void MainWindow::slotDefineStairs()
{
    *(globals -> appState) = definingStairs;
    designWidget -> printInfo("Choose bottom field for stairs ... ");
    designWidget -> setFocus();
}

void
MainWindow::slotDefineWindow()
{
  if(*(globals -> appState) != editingField)
    {
      designWidget -> printInfo("Choose field and it's wall first.");      
      return;
    }
  *(globals -> appState) = definingWindow;
  //  designWidget -> setFocus();
  //  designWidgetMini->setEditedField(designWidget->chosenField, designWidget->chosenWall);
  designWidgetMini -> beginNewEditing(globals->chosenField, designWidget->chosenWall);
  designWidgetMini -> setFocus();
}


QSlider *MainWindow::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 100);
    slider->setSingleStep(5);
    slider->setPageStep(20);
    //slider->setTickInterval(20);

    slider->setTickPosition(QSlider::TicksRight);
    slider -> setDisabled(true);
    return slider;
}


/*void MainWindow::slotFloorSliderOneChanged(int value)
{
    //     designWidget -> printInfo(QString::number(value));
    designWidget -> chosenField -> walls[0] = value;
}
void MainWindow::slotFloorSliderTwoChanged(int value)
{
    designWidget -> chosenField -> walls[1] = value;
}
void MainWindow::slotFloorSliderThreeChanged(int value)
{
    designWidget -> chosenField -> walls[2] = value;
}
void MainWindow::slotFloorSliderFourChanged(int value)
{
    designWidget -> chosenField -> walls[3] = value;
}
*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    switch(event -> key())
    {
        //previous wall
    case(Qt::Key_A):
        {
            switch(*(globals -> appState))
            {
            case(editingField):
                {
                    designWidget -> chosenWall --;
                    if (designWidget -> chosenWall < 0)
                        designWidget -> chosenWall = 3;
                    designWidget -> repaint();
                    break;
                }
            case(definingStairs):
                {
                    //if bottom field is not done, but is chosen
                    if( ! (globals -> isBottomFieldSet) && globals -> stairsBottom )
                    {
                        globals -> stairsFieldBottomEdge--;
                        if(globals -> stairsFieldBottomEdge < 0)
                            globals -> stairsFieldBottomEdge = 3;

                        designWidget -> repaint();
                    }
                    else
                    {
                        //if top field is chosen
                        if(globals -> stairsTop)
                        {
                            globals -> stairsFieldTopEdge--;
                            if(globals -> stairsFieldTopEdge < 0)
                                globals -> stairsFieldTopEdge = 3;

                            designWidget -> repaint();
                        }
                    }
                    break;
                }
            default:
                {
                    break;
                }
            }
            break;
        }
        //next wall
    case(Qt::Key_D):
        {
            switch(*(globals -> appState))
            {
            case(editingField):
                {
                    designWidget -> chosenWall ++;
                    if (designWidget -> chosenWall > 3)
                        designWidget -> chosenWall = 0;
                    designWidget -> repaint();
                    break;
                }
            case(definingStairs):
                {
                    if( !(globals -> isBottomFieldSet) && !(globals -> stairsTop))
                    {
                        globals -> stairsFieldBottomEdge++;
                        if(globals -> stairsFieldBottomEdge > 3)
                            globals -> stairsFieldBottomEdge = 0;

                        designWidget -> repaint();
                    }
                    else
                    {
                        //if top field is chosen
                        if(globals -> stairsTop)
                        {
                            globals -> stairsFieldTopEdge++;
                            if(globals -> stairsFieldTopEdge > 3)
                                globals -> stairsFieldTopEdge = 0;

                            designWidget -> repaint();
                        }
                    }

                    break;
                }
            default:
                {
                    break;
                }
            }
            break;
        }
    case(Qt::Key_W):
        {
            switch(*(globals -> appState))
            {
                //increase wall's height
            case(editingField):
                {
                    int wallIndex = designWidget -> chosenWall;

		    //wall higher on 0.5m (1 pix = 5cm)
                    globals -> chosenField -> walls[wallIndex] += 10.0f;
		    designWidget -> update();
                    break;
                }
                //higher floor
            case(none):
                {
		  /*		  globals->actualFloor
				  globals->actualFloor = (LBFloor*)(globals -> actualFloor -> next);*/
		  globals->chooseNextFloor();
		  designWidget -> repaint();
                    break;
                }
	    case(definingStairs):
	      {
		globals->chooseNextFloor();
		break;
	      }
	      
	    default:
	      {
		break;
	      }
            }

            break;
        }
    case(Qt::Key_S):
        {
            switch(*(globals -> appState))
            {
            case(editingField):
                {
                    int wallIndex = designWidget -> chosenWall;
                    globals -> chosenField -> walls[wallIndex] -= 10.0f;
		    designWidget -> update();
                    break;
                }
                //lower floor
            case(none):
                {
		  //                    globals -> actualFloor = (LBFloor*)(globals -> actualFloor -> prev);
		  globals->choosePrevFloor();
		  designWidget -> repaint();
                    break;
                }
            case(definingStairs):
                {
		  //                    globals -> actualFloor = (LBFloor*)(globals -> actualFloor -> prev);
		  globals->choosePrevFloor();
		  designWidget -> repaint();
                    break;
                }
	    default:
	      {
		break;
	      }
            }
            break;
        }
    default:
        {
            break;
        }
    }

}

void 
MainWindow::slotDefineDoors()
{
  if( *(globals -> appState) == connectingFields)
    {
      globals -> isPassWithDoors = true;
    }
  designWidget -> update();
}

void
MainWindow::slotSaveAsXML()
{

  QString qFileName = QFileDialog::getSaveFileName(this);
  //my_qstring.toStdString().c_str()

  if(! qFileName.isEmpty())
    {
      if(xmlManager->saveXML(qFileName.toStdString().c_str()))
	statusBar()->showMessage(tr("File saved."), 2000);
      else
	statusBar()->showMessage(tr("Error: file not saved."), 2000);
    }
}

void
MainWindow::slotLoadXML()
{
  QString qFileName = QFileDialog::getOpenFileName(this);
  
  if(! qFileName.isEmpty())
    {
      if(xmlManager->loadXML(qFileName.toStdString().c_str()) == SLOADING)
	statusBar()->showMessage(tr("Refreshing building's data ..."), 2000);
      else
	statusBar()->showMessage(tr("Error: not loaded."), 2000);

      //refresh all buildings primitives
      globals->refreshPrimitives();

      statusBar()->showMessage(tr("File loaded."), 2000);
    }
}

void
MainWindow::slotOpenFile()
{
  
}

void
MainWindow::slotAbout()
{
  QMessageBox::about(this, tr("About Lucidbeaver"),
		     tr("The <b>Lucidbeaver</b> is used to define XML files describing"
			" topology of buildings used in City Cuber program."));
}
