#include "globalcontainer.h"
#include "paintwidget.h"
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qscrollarea.h>
#include <qpushbutton.h>

globalContainer::globalContainer()
{

    math = new lbmathhelper();

    //create root
    floorsTree = new LObject;

    chosenField = NULL;
    chosenField2 = NULL;

    floorsAmount = 0;

    
    for(int cnt = 0; cnt < floorsAmount; cnt++)
    {
      //      addFloor(cnt*10);
      /*      LBFloor * help = new LBFloor(cnt*10);
	      ((LObject*)help) -> connectTo(floorsTree);*/
    }
    /*
    actualFloor = ((LBFloor*)(floorsTree -> child));
    actualFloor -> height = 0.0f;*/
    appState = new STATE;
    actualFloor = NULL;

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

    stairsTree = new LBStairs(0, 0, 0);

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
    QImage image("images/image.png");

    painter -> drawImage(target, image, source);
}

void
globalContainer::chooseNextFloor()
{
  if(actualFloor ==NULL)
    return;

  actualFloor->setSFloor(noneFloor);
  actualFloor=(LBFloor*)(actualFloor -> next);
  actualFloor->setSFloor(chosenFloor);
}

void
globalContainer::choosePrevFloor()
{
  if(actualFloor == NULL)
    return;

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
  return 0;//should not happen, but if there are no free ids, return 0
}

void 
globalContainer::freeID(int freedID)
{
  IDPool[freedID] = true;
}

//return false if something goes wrong
bool
globalContainer::reserveID(int ID)
{
  if(IDPool[ID] == false)
    {
      return false; //failure! this ID is already reserved
    }
  IDPool[ID] = false;
  return true;
}

LBFloor* globalContainer::addFloor(int floorID, float height)
{
    //actualize checkboxes
    drawBoxes[floorsAmount].setDisabled(false);
    drawBoxes[floorsAmount].setChecked(true);
    renderBoxes[floorsAmount].setDisabled(false);
    renderBoxes[floorsAmount].setChecked(true);

    //new floor will be returned, helpFloor will help in connecting
    LBFloor *newFloor = new LBFloor(floorID, worldSize - height);
    LBFloor *helpFloor = newFloor;

    //SORT OPERATION (connect floor without breaking order of heights)
    LBFloor *tempTree = new LBFloor(0, 0);
    while( floorsTree -> hasChild() )
      {
	LBFloor *discFloor = (LBFloor*)(floorsTree->child);
	discFloor -> connectTo(tempTree);
      }

    //all floors are in tempTree. connect them again, check where is place for
    //tempFloor
    while(tempTree -> hasChild())
      {
	if(helpFloor != NULL)
	  {
	    LBFloor *tempTreeChild = ((LBFloor*)(tempTree->child));
	    if(helpFloor -> height < tempTreeChild -> height)
	      {
		((LObject*)helpFloor) -> connectTo(floorsTree);
		helpFloor = NULL;
	      }
	  }
	tempTree->child->connectTo(floorsTree);
      }

    //if floor is not yet connected, it goes to the end
    if(helpFloor != NULL)
      {
	((LObject*)helpFloor) -> connectTo(floorsTree);
      }
    //SORT OPERATION (connect floor without breaking order of heights)


    QString *floorName = new QString("floor" + QString::number(floorsAmount));
    floorsComboBox -> addItem(*floorName);
    floorsAmount++;

    if(actualFloor != NULL){actualFloor->setSFloor(noneFloor);}
    actualFloor = ((LBFloor*)(newFloor));
    actualFloor->setSFloor(chosenFloor);

    return newFloor;
}

LField*
globalContainer::findField(int ID)
{
  //fields are in floorTree, so search through floors
  LBFloor *helpFloor;
  LField *helpField;

  if(floorsTree->hasChild())
    helpFloor = (LBFloor*)floorsTree -> child;
  else
    return NULL;// error -> field with that ID does not exist

  while(1)
    {
      //if helpFlor has any child, search children to find field with ID
      if(helpFloor->hasChild())
	{
	  helpField = (LField*)helpFloor->child;

	  while(1)
	    {
	      if(helpField->giveID() == ID)
		{
		  //success - return helpField
		  return helpField;
		}
	      if(! helpField -> isLast())
		helpField = (LField*)(helpField -> next);
	      else
		break;//floor searched
	    }
	}
      if(! helpFloor -> isLast())
	helpFloor = (LBFloor*)(helpFloor -> next);
      else
	break;
    }
  return NULL;// error -> field with that ID does not exist
}

LBStairs*
globalContainer::findStairs(int ID)
{
  LBStairs *helpStairs;

  if(stairsTree->hasChild())
    helpStairs = (LBStairs*)stairsTree->child;
  else
    return NULL;//error - no stairs

  while(1)
    {
      if(helpStairs -> giveID() == ID)
	return helpStairs;

      if(! helpStairs -> isLast())
	helpStairs = (LBStairs*)(helpStairs -> next);
      else
	break;
    }

  return NULL;// error -> stairs with that ID does not exist
}

LBWindow*
globalContainer::findWindow(int ID)
{
  LBFloor *helpFloor;
  LField *helpField;
  LBWindow *helpWindow;


  if(floorsTree->hasChild())
    helpFloor = (LBFloor*)floorsTree -> child;
  else
    return NULL;// error -> field with that ID does not exist

  while(1)
    {
      //if helpFlor has any child, search children to find field's window with ID
      if(helpFloor->hasChild())
	{
	  helpField = (LField*)helpFloor->child;

	  while(1)
	    {
	      //check if any wall has window with ID
	      for(int cntW = 0; cntW < 4; cntW++)
		{
		  if(helpField->windowTree[cntW]->hasChild())
		    {
		      helpWindow = (LBWindow*)helpField->windowTree[cntW]->child;
		      
		      while(1)
			{
			  if(helpWindow->giveID() == ID)//success!
			    return helpWindow;
			  
			  if(!helpWindow -> isLast())
			    helpWindow = (LBWindow*)(helpWindow -> next);
			  else
			    break;
			}
		    }
		}//for cntW
	      
	      if(! helpField -> isLast())
		helpField = (LField*)(helpField -> next);
	      else
		break;//floor searched
	    }
	}
      if(! helpFloor -> isLast())
	helpFloor = (LBFloor*)(helpFloor -> next);
      else
	break;
    }
  
  return NULL;
}

lbpassage*
globalContainer::findPassage(int ID)
{
  LBFloor *helpFloor;
  LField *helpField;
  lbpassage *helpPassage;


  if(floorsTree->hasChild())
    helpFloor = (LBFloor*)floorsTree -> child;
  else
    return NULL;// error -> field with that ID does not exist

  while(1)
    {
      //if helpFlor has any child, search children to find field's window with ID
      if(helpFloor->hasChild())
	{
	  helpField = (LField*)helpFloor->child;

	  while(1)
	    {
	      //check if any wall has passage with ID
	      for(int cntP = 0; cntP < 4; cntP++)
		{
		  if(helpField->passageTree[cntP]->hasChild())
		    {
		      helpPassage = (lbpassage*)helpField->passageTree[cntP]->child;
		      
		      while(1)
			{
			  if(helpPassage->giveID() == ID)//success!
			    return helpPassage;
			  
			  if(!helpPassage -> isLast())
			    helpPassage = (lbpassage*)(helpPassage -> next);
			  else
			    break;
			}
		    }
		}//for cntP
	      
	      if(! helpField -> isLast())
		helpField = (LField*)(helpField -> next);
	      else
		break;//floor searched
	    }
	}
      if(! helpFloor -> isLast())
	helpFloor = (LBFloor*)(helpFloor -> next);
      else
	break;
    }
  return NULL;// error -> passage with that ID does not exist
}

/*
  After loading XML building, following operations should be done:
  - refresh IDPool
  - refresh connections between primitives
*/
void
globalContainer::refreshPrimitives()
{
  LBFloor *helpFloor;
  LField *helpField;
  LBWindow *helpWindow;
  lbpassage *helpPassage;


  if(floorsTree->hasChild())
    helpFloor = (LBFloor*)floorsTree -> child;
  else
    return;

  while(1)
    {
      reserveID(helpFloor -> giveID());

      //if helpFlor has any child, search children to find field's window with ID
      if(helpFloor->hasChild())
	{
	  helpField = (LField*)helpFloor->child;

	  while(1)
	    {
	      reserveID(helpField->giveID());

	      //check if any wall has window with ID
	      for(int cntW = 0; cntW < 4; cntW++)
		{
		  if(helpField->windowTree[cntW]->hasChild())
		    {
		      helpWindow = (LBWindow*)helpField->windowTree[cntW]->child;
		      
		      while(1)
			{
			  reserveID(helpWindow->giveID());
			  
			  if(!helpWindow -> isLast())
			    helpWindow = (LBWindow*)(helpWindow -> next);
			  else
			    break;
			}
		    }

		  if(helpField->passageTree[cntW]->hasChild())
		    {
		      helpPassage = (lbpassage*)helpField->passageTree[cntW]->child;

		      while(1)
			{
			  reserveID(helpPassage->giveID());
			  /*
			    check with what primitive passage has connecion and
			    set adequate *destObject
			  */
			  {
			    LBStairs *destStairs = 
			      findStairs(helpPassage->destObjectID);

			    LField *destField = 
			      findField(helpPassage->destObjectID);

			    if(destStairs != NULL)
			      helpPassage -> destObject = (LObject*)destStairs;
			    else
			      helpPassage -> destObject = (LObject*)destField;
			    }
			  
			  if(!helpPassage -> isLast())
			    helpPassage = (lbpassage*)(helpPassage -> next);
			  else
			    break;
			}
		    }
		}//for cntW
	      
	      if(! helpField -> isLast())
		helpField = (LField*)(helpField -> next);
	      else
		break;//floor searched
	    }
	}
      if(! helpFloor -> isLast())
	helpFloor = (LBFloor*)(helpFloor -> next);
      else
	break;
    }


  LBStairs *helpStairs;

  if(stairsTree->hasChild())
    {
      helpStairs = (LBStairs*)stairsTree->child;
      while(1)
	{
	  reserveID(helpStairs->giveID());      

	  {//connections
	    helpStairs->connBottom = findField(helpStairs->connBottomID);
	    helpStairs->connTop = findField(helpStairs->connTopID);
	  }

	  if(! helpStairs -> isLast())
	    helpStairs = (LBStairs*)(helpStairs -> next);
	  else
	    break;
	}
    }
}
