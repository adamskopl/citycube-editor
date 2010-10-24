#ifndef GLOBALCONTAINER_H
#define GLOBALCONTAINER_H

#include "object.h"
#include "field.h"
#include "floor.h"

//global state of application (alias "what Designer is doing right now ?")
enum STATE {none, defining, editingField, connectingFields, addingFloor, definingStairs};
class QComboBox;
class QCheckBox;
class LField;
class QScrollArea;
class DesignWidget;
class QSlider;
class LBStairs;

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

    //pointer on actual floor - level 1 of the tree
    //it's field, to have floor's height.
    //IS IT NEEDED ?????
    LBFloor *actualFloor;
    int *floorsAmount;

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
    char stairsFieldBottomEdge;
    char stairsFieldTopEdge;

    /*
      vector used for drawing steps - their horizontal direction is equal
      to bottom field wall's normal vector
      */
    LVector stairsHorizontalVector;
    //help variable for deciding if user has chosen bottom field
    bool isBottomFieldSet;

};

#endif // GLOBALCONTAINER_H
