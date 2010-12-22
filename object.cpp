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
#include <GL/gl.h>
#include <GL/glu.h>
#include "object.h"

LObject::LObject() { bDelete = false; ID = 0;}
LObject::~LObject() {}

void LObject::selfAnimate(scalar_t deltaTime) 
{
  position += velocity * deltaTime;
  velocity += acceleration * deltaTime;
}

void LObject::selfDraw(LCamera *camera) {}	

void LObject::processCollision(LObject *collisionObject) {}

void LObject::selfPrepare() 
{
  checkCollisions(findRoot());
}

void LObject::load() {}
void LObject::unload() {}


void LObject::othersDraw(LCamera *camera) 
{
  glPushMatrix();
  selfDraw(camera);
  if (hasChild())
    ((LObject*)child)->othersDraw(camera);
  glPopMatrix();
  
  if (hasParent() && !isLast())
    ((LObject*)next)->othersDraw(camera);
}

void LObject::othersAnimate(scalar_t deltaTime) 
{
  selfAnimate(deltaTime);	
  
  if (hasChild())
    ((LObject*)child)->othersAnimate(deltaTime);
  
  if (hasParent() && !isLast())
    ((LObject*)next)->othersAnimate(deltaTime);
  
  if (bDelete)
    delete this;
}


void LObject::checkCollisions(LObject *obj) 
{
  
  if (((obj->position - position).Length() <= (obj->size + size)) &&
      (obj != ((LObject*)this)))
    {
      processCollision(obj);
      
      
      if (hasChild())
	((LObject*)child)->checkCollisions(obj);
      
      
      if (hasParent() && !isLast())
	((LObject*)next)->checkCollisions(obj);
    }
  
  
  if (obj->hasChild())
    checkCollisions((LObject*)(obj->child));
  
  
  if (obj->hasParent() && !obj->isLast())
    checkCollisions((LObject*)(obj->next));
}


void LObject::othersPrepare()
{
  selfPrepare();
  
  if (hasChild())	
    ((LObject*)child)->othersPrepare();
  
  if (hasParent() && !isLast())
    ((LObject*)next)->othersPrepare();
}


LObject* LObject::findRoot()
{
  
  if (parent)
    return ((LObject*)parent)->findRoot();
  
  return this;
}

int
LObject::giveID()
{
  return ID;
}

void
LObject::setID(int newID)
{
  ID = newID;
}

void 
LObject::resetID()
{
  ID = 0;
}
