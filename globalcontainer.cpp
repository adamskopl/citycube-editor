#include "globalcontainer.h"
#include "field.h"
#include <QtGui>
globalContainer::globalContainer()
{

    //create root
    floorsTree = new LObject;

    floorsAmount = new int; 
    *floorsAmount = 1;


    for(int cnt = 0; cnt < *floorsAmount; cnt++)
    {
        LField * help = new LField();
        ((LObject*)help) -> connectTo(floorsTree);
    }

    actualFloor = ((LField*)(floorsTree -> child));
    actualFloor -> height = 0.0f;
    appState = new STATE;

    cameraKid = new LObject();
    cameraKid -> position = LVector(500.0f, 0.0f, 500.0f);
    cameraKid -> direction = -45.0f;

    *appState = none;
    floorsComboBox = new QComboBox;

}

void globalContainer::changeFloor(int floorIndex)
{

    LField *chosenFloor;
    chosenFloor = (LField*)floorsTree;

    if(chosenFloor -> hasChild())
        chosenFloor = (LField*)chosenFloor -> child;
    else
        return;

    //break this while(), when proper floor is chosen
    while(1)
    {
        if(!floorIndex)
        {
            actualFloor = chosenFloor;
            break;
        }
        chosenFloor = (LField*)chosenFloor -> next;
        floorIndex--;
    }
}
