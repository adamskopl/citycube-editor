#include "globalcontainer.h"
#include "field.h"
#include "lbstairs.h"

#include <QtGui>
#include "paintwidget.h"
globalContainer::globalContainer()
{

    math = new lbmathhelper();

    //create root
    floorsTree = new LObject;

    chosenField = NULL;
    chosenField2 = NULL;

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

    stuffArea = new QScrollArea;
    stuffArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    stuffArea->setFixedSize(100,100);

    stairsBottom = NULL;
    stairsTop = NULL;
    stairsFieldBottomEdge = 0;
    stairsFieldTopEdge = 0;
    isBottomFieldSet = false;

    stairsTree = new LBStairs;

    //////////
    IDAmount = 1000000;

    //IDPool - false means that particular ID is not available
    IDPool = new bool[IDAmount];

    //reset IDPool (ID 0 is reserved for all objects - it means, 
    //that object has no ID)
    IDPool[0] = false;
    for(int cnt = 1; cnt < IDAmount; cnt++)
      {
	IDPool[cnt] = true;
      }
    //////////
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

void globalContainer::stuffAreaDraw()
{
    QPainter *painter = new QPainter(stuffArea);

    QRectF target(0.0, 0.0, 100.0, 100.0);
    QRectF source(0.0, 0.0, 100.0, 100.0);
    QImage image("image.png");

    painter -> drawImage(target, image, source);
}

void
globalContainer::chooseNextFloor()
{
  actualFloor->setSFloor(noneFloor);
  actualFloor=(LBFloor*)(actualFloor -> next);
  actualFloor->setSFloor(chosenFloor);
}

void
globalContainer::choosePrevFloor()
{
  actualFloor->setSFloor(noneFloor);
  actualFloor=(LBFloor*)(actualFloor -> prev);
  actualFloor->setSFloor(chosenFloor);
}

int
globalContainer::giveFreeID()
{
  //start from 1, because 0 is reserved for "I have no ID"
  for(int cnt = 1; cnt < IDAmount; cnt++)
    {
      if(IDPool[cnt] == true)
	{
	  //from now on, this ID is not free
	  IDPool[cnt] = false;
	  return cnt;
	}
    }
}

void 
globalContainer::freeID(int freedID)
{
  IDPool[freedID] = true;
}

