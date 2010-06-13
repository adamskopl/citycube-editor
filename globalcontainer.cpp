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
        LBFloor * help = new LBFloor(cnt*10);
        ((LObject*)help) -> connectTo(floorsTree);
    }

    actualFloor = ((LBFloor*)(floorsTree -> child));
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

    LBFloor *chosenFloor;

    if(floorsTree -> hasChild())
        chosenFloor = (LBFloor*)(floorsTree -> child);
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
        chosenFloor = (LBFloor*)chosenFloor -> next;
        floorIndex--;
    }
}
