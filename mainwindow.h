#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include "globalcontainer.h"
#include <vector>
#include <QCheckBox>
#include <QLabel>

class QComboBox;
class QLineEdit;

using namespace std;

class QScrollArea;
class DesignWidget;
class PreviewWidget;
class QTextEdit;
class QGridLayout;

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
    void createMenus();

    QWidget *centralWidget;

    //bigger area for designe (2d)
    QScrollArea *designArea;
    //smaller area for preview (3d)
    QScrollArea *previewArea1;
    QScrollArea *previewArea2;

    DesignWidget *designWidget;
    PreviewWidget *previewWidget1;
    PreviewWidget *previewWidget2;

    QTextEdit * reportWidget;
    QMenu *fileMenu;
    QMenu *helpMenu;

    QGridLayout *toolsLayout;
    QGridLayout *fieldEditLayout;
    QGridLayout *floorChooseLayout;
    QGridLayout *floorsLayout;

    QLineEdit *floorChooser;
    QComboBox *floorsComboBox;

    int maxFloorsAmount;
    QCheckBox drawBoxes[20];
    QCheckBox renderBoxes[20];
    QLabel floorsLabels[20];
    QLabel floorsHelpLabels[4];

    void mousePressEvent(QMouseEvent *event);

};

#endif // MAINWINDOW_H
