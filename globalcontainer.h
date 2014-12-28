#ifndef GLOBALCONTAINER_H
#define GLOBALCONTAINER_H

#include <typeinfo>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <cstdio>
#include <iostream>
#include <QPrinter>
#include <QtGui>
#include "object.h"
#include <primitives/field.h>
#include <primitives/floor.h>
#include <primitives/lbstairs.h>
#include "lbmathhelper.h"

//global state of application (alias "what Designer is doing right now ?")
enum STATE {none, defining, editingField, connectingFields, breakingHole, addingFloor, definingStairs, definingWindow};
class QComboBox;
class QCheckBox;
class LField;
class QScrollArea;
class DesignWidget;
class QSlider;
//class LBStairs;

enum drawStyle {invisible, drawStyleField, drawStyleDefinedField, stylePointedField, styleChosenField, pointer, connection, drawStyleWall,
                normal, inactive, floorLine, fieldSide, wallInactive, drawStyleChosenWall, styleStairsTriangle, drawStyleGrid, drawStyleBigPoint, drawStyleWallChoose,
		drawStyleHighlightParts, drawStyleWallWindow, drawStyleTextDist,
		drawStyleHighlightPartsD};

class globalContainer
{
public:
    globalContainer();

    STATE *appState;

    /*floor tree
     for now it looks like this:
     - level 0 : root (abstract building)
     - level 1 : floors
     - level 2 : fields of floors
     - level 3 : walls (always in number fileds*4
     - level 4 : passages for every wall 
     */
    LObject *floorsTree;

    /*stairs tree

    - level 0 : root
    - level 1 : stairs
      */
    LBStairs *stairsTree;

    //fields chosen to edit in classes using globalContainer
    LField *chosenField;
    LField *chosenField2;

    //pointer on actual floor - level 1 of the tree
    //it's field, to have floor's height.
    //IS IT NEEDED ?????
    LBFloor *actualFloor;
    int floorsAmount;

    //object spied by camera - pointer passed to previewWidget and designWidget
    LObject *cameraKid;

    //interface
    QComboBox *floorsComboBox;

    void changeFloor(int);

    QCheckBox *drawBoxes;
    QCheckBox *renderBoxes;

    QScrollArea *stuffArea;
    void stuffAreaDraw();
    QScrollArea *designArea;

    QSlider *fieldSliderOne;
    QSlider *fieldSliderTwo;
    QSlider *fieldSliderThree;
    QSlider *fieldSliderFour;

    //pointers on fields defining stairs
    LField *stairsBottom;
    LField *stairsTop;

    //indexes of walls
    int stairsFieldBottomEdge;
    int stairsFieldTopEdge;

    /*
      vector used for drawing steps - their horizontal direction is equal
      to bottom field wall's normal vector
      */
    LVector stairsHorizontalVector;
    //help variable for deciding if user has chosen bottom field
    bool isBottomFieldSet;

    //temporary: set to true if new passage will be with doors
    bool isPassWithDoors;

    lbmathhelper *math;

    void chooseNextFloor();
    void choosePrevFloor();

 private:
    int IDAmount;
    bool *IDPool;

 public:
    int giveFreeID();
    void freeID(int);
    bool reserveID(int);

    //operations connected with lbxmlnagaer
    void refreshPrimitives();

    //returns pointer on new added floor
    float worldSize;
    LBFloor* addFloor(int ID, float);    

    //searching functions
    LField* findField(int ID);
    LBStairs* findStairs(int ID);
    LBWindow* findWindow(int ID);
    lbpassage* findPassage(int ID);
};

#endif // GLOBALCONTAINER_H
