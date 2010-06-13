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
}

LWorld::~LWorld()
{
  delete camera;
  delete hero;
}

void LWorld::OnPrepare(){

  glClearColor(0.5f,0.5f,0.5f,0.0f);
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
    LObject *actualFloor;

    //for every floor draw its fields
    if(floorsTree -> hasChild())
        actualFloor = ((LField*)(floorsTree -> child));

    //break this while(), when last floor is drawn
    while(1)
    {
        LField * drawnField;
        //draw floor's fields

        if(actualFloor -> hasChild())
        {
            drawnField = ((LField*)(actualFloor -> child));

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
        actualFloor = (LField*)actualFloor -> next;
    }
}

void LWorld::draw(LCamera *camera)
{
  //GL_TEXTURE_2D INVOKED ONLY HERE
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);				
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

  drawFloors();
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

/*int LWorld::loadLevel(const char * filename){
  FILE *filePtr;

  filePtr = fopen(filename,"rb");

  int size;
  
  fread(&size, 1, sizeof(int), filePtr);
  size --;

  for(int a = 0; a < size; a++){
    char kind;
    CORNERS c;
    c.a.y = 0.0;
    c.b.y = 0.0;
    c.c.y = 0.0;
    c.d.y = 0.0;
    
    fread(&kind, 1, sizeof(char), filePtr);

    fread(&c.a.x, 1,sizeof(float), filePtr);
    fread(&c.a.z, 1,sizeof(float), filePtr);
    fread(&c.b.x, 1,sizeof(float), filePtr);
    fread(&c.b.z, 1,sizeof(float), filePtr);
    fread(&c.c.x, 1,sizeof(float), filePtr);
    fread(&c.c.z, 1,sizeof(float), filePtr);
    fread(&c.d.x, 1,sizeof(float), filePtr);
    fread(&c.d.z, 1,sizeof(float), filePtr);

    c.a *= 10;
    c.b *= 10;
    c.c *= 10;    
    c.d *= 10;

    int up, right, down, left;
    
    fread(&up, 1,sizeof(int), filePtr);
    fread(&right, 1,sizeof(int), filePtr);    
    fread(&down, 1,sizeof(int), filePtr);
    fread(&left, 1,sizeof(int), filePtr);


    LField *temp = new LField(kind, &c);
    temp->up = up;
    temp->right = right;
    temp->down = down;
    temp->left = left;
    
    fields.push_back(*temp);//add readed field
  }

  
  fclose(filePtr);

  for(int a = 0; a < size; a++){
    if(fields[a].up){fields[a].ConnectUp(&(fields[fields[a].up-1]));}
    if(fields[a].right){fields[a].ConnectRight(&(fields[fields[a].right-1]));}
    if(fields[a].down){fields[a].ConnectDown(&(fields[fields[a].down-1]));}
    if(fields[a].left){fields[a].ConnectLeft(&(fields[fields[a].left-1]));}    
  }
  
  hero -> field = &(fields[0]);
  fields[0].heroEnters();

  float dx = fields[0].corners.b.x - fields[0].corners.a.x;
  float dz = fields[0].corners.a.z - fields[0].corners.d.z;

  float x = fields[0].corners.b.x - (dx/2);
  float z = fields[0].corners.b.z - (dz/2);  

  hero -> position = LVector(x,2.5,z);

  return size;
}

*/
