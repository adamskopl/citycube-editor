#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include "globalcontainer.h"
#include "lbxmlmanager.h"
#include <vector>
#include <QCheckBox>
#include <QLabel>

class QComboBox;
class QLineEdit;

using namespace std;

class QScrollArea;
class DesignWidget;
class DesignWidgetMini;
class PreviewWidget;
class QTextEdit;
class QGridLayout;
class QHBoxLayout;
class QSlider;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    globalContainer *globals;

public slots:
    void slotFloorChanged( int );
    void slotNewFloor();
    void slotDefineStairs();
    void slotDefineWindow();
    void slotDefineDoors();
    void slotAbout();

    void slotSaveAsXML();
    void slotLoadXML();
    void slotOpenFile();

    /*    void slotFloorSliderOneChanged(int);
    void slotFloorSliderTwoChanged(int);
    void slotFloorSliderThreeChanged(int);
    void slotFloorSliderFourChanged(int);*/

    void changeFloorsView();
    void designAreaScrollBarXChanged(int);
    void designAreaScrollBarYChanged(int);
    //TODO - make class that contains globalFields, camreaKid and so on - to pass
    // it for designWidget and previewWidget
    //keep globalFields and such somewhere else
    //vector <LField> globalFields;
    //object spied by camera - pointer passed to previewWidget and designWidget
    //LObject *cameraKid;


    //LObject *listRoot;


private:    
    lbXMLmanager *xmlManager;

    QSlider *createSlider();
    void createMenus();
    void createActions();
    

    QWidget *centralWidget;

    //bigger area for designe (2d)
    QScrollArea *designArea;
    QScrollArea *designAreaMini;
    //smaller area for preview (3d)
    QScrollArea *previewArea1;
    //    QScrollArea *previewArea2;

    DesignWidget *designWidget;
    DesignWidgetMini *designWidgetMini;
    PreviewWidget *previewWidget1;
    PreviewWidget *previewWidget2;

    QTextEdit * reportWidget;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu; 

    QAction *saveXMLAction;
    QAction *loadXMLAction;
    QAction *newFileAction;
    QAction *aboutAction;

    QGridLayout *toolsLayout;
    QHBoxLayout *fieldEditLayout;
    QGridLayout *floorChooseLayout;
    QGridLayout *floorsLayout;

    QLineEdit *floorChooser;
    QComboBox *floorsComboBox;

    int maxFloorsAmount;
    QCheckBox drawBoxes[20];
    QCheckBox renderBoxes[20];
    QLabel floorsLabels[20];
    QLabel floorsHelpLabels[4];

    //    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *);

    //sliders
    /*    QSlider *fieldSliderOne;
    QSlider *fieldSliderTwo;
    QSlider *fieldSliderThree;
    QSlider *fieldSliderFour;*/

    enum { MaxRecentFiles = 5};
    QAction *recentFileActs[MaxRecentFiles];
};

#endif // MAINWINDOW_H
