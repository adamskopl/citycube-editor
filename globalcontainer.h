#ifndef GLOBALCONTAINER_H
#define GLOBALCONTAINER_H

#include "object.h"
#include "field.h"
#include "floor.h"

//global state of application (alias "what Designer is doing right now ?")
enum STATE {none, defining, connecting, addingFloor};
class QComboBox;
class LField;

class globalContainer
{
public:
    globalContainer();

    STATE *appState;

    /*floor tree
     for now it looks like this:
     - level 0 : root
     - level 1 : floors
     - level 2 : fields of floors
     */
    LObject *floorsTree;

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

};

#endif // GLOBALCONTAINER_H
