/* 
   This file is part of Lucidia.

   Lucidia is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Lucidia is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Lucidia.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "world.h"
//#include "text.h"

/*
  NOTES:

  # such things as texture files and so on - should
    be loaded from text file (easily edited by player)

 */
LWorld::LWorld(LObject *globalFloors)
{
  
  hero = new LHero();
  camera = new LCamera();

  root = new LBeing;

  hero -> connectTo(root);
  
  hero -> Load("models/kimNew.md2", "kim2.tga");

  hero -> SetState(MODEL_IDLE);
  hero -> direction = 0.0f;

  floorsTree = globalFloors;
  //  LField::setFieldsGS(FieldsGSNormal);
}

LWorld::~LWorld()
{
  delete camera;
  delete hero;
}

void LWorld::OnPrepare(){

  //glClearColor(0.22f,0.22f,0.22f,0.0f);
  glClearColor(0.22f, 0.22f, 0.22f, 0.0f);
  root -> othersPrepare();
}

void LWorld::animate(int deltaTime)
{
  root -> LObject::othersAnimate
    ((float)deltaTime/1000); //once again - modify class clock
}

void LWorld::drawText()
{
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glDisable(GL_DEPTH_TEST);
  ////////////////////////////////////  

  glColor3f(1.0f, 0.0f, 0.0f);
  //LText text;

  //text.drawChar(10, 10);

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void LWorld::drawFloors()
{
    LBFloor *actualFloor;

    //for every floor draw its fields
    if(floorsTree -> hasChild())
      actualFloor = ((LBFloor*)(floorsTree -> child));
    else
      {
	//printError("drawFloors: actualFloor==NULL!");
	return;
      }

    //break this while(), when last floor is drawn
    while(1)
    {
        LField * drawnField;
        //draw floor's fields
        if(actualFloor -> isItRendered)
            if(actualFloor -> hasChild())
            {
	      drawnField = ((LField*)(actualFloor -> child));


	      /*
		If floor is chosen one, draw all its Fields in specific way.
		set FieldsS back to normal, when floor other than chosen one
		will be met.
	      */
	      if(actualFloor->giveSFloor() == chosenFloor)
		{
		  LField::setSFields(chosenField);
		}
	      else
		{
		  LField::setSFields(noneField);
		}

            //break this while(), when last field is drawn
            while(1)
            {
                drawnField -> selfDraw();
                if(drawnField -> isLast())
                    break;
                drawnField = (LField*)drawnField -> next;
            }
        }
        if(actualFloor -> isLast())
            break;
        actualFloor = (LBFloor*)actualFloor -> next;
    }
}

void LWorld::drawStairs()
{

    LBStairs *drawnStairs;
    if(stairsTree -> hasChild())
        drawnStairs = (LBStairs*)(stairsTree -> child);
    else
        return;

    //break this while, when last stairs are drawn
    while(1)
    {
        drawnStairs -> selfDraw();
        if(drawnStairs -> isLast())
            break;
        drawnStairs = (LBStairs*)(drawnStairs -> next);
    }

}

void LWorld::draw(LCamera *camera)
{
  //GL_TEXTURE_2D INVOKED ONLY HERE
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);				
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

  drawFloors();
  drawStairs();
  //TODO : write function for drawing.
/*
  glPushMatrix();
  LField * drawnField;
  if(worldList -> child)
  {
      drawnField = ((LField*)(worldList -> child));

      while(1)
      {
          drawnField -> selfDraw();
          if(drawnField -> isLast())
              break;
          drawnField = (LField*)drawnField->next;
      }
  }
  glPopMatrix();
*/
  //root -> othersDraw(camera);
}


