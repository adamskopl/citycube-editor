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
#ifndef __OBJECT_H
#define __OBJECT_H

#include "camera.h"
#include "vector.h"
#include "node.h"


class LObject : public LNode
{
 private:
  int ID;

 protected:
  bool bDelete;

  virtual void selfAnimate(scalar_t);
  virtual void selfDraw(LCamera *);
  virtual void processCollision(LObject *);
  virtual void selfPrepare();

 public:
  LVector position;	
  LVector velocity;	
  LVector acceleration;	
  scalar_t size;	
  float direction;
  
  LObject();
  ~LObject();

  virtual void load();
  virtual void unload();
    
  void othersDraw(LCamera *);
  void othersAnimate(scalar_t );
  void checkCollisions(LObject *);
  void othersPrepare();

  LObject *findRoot();

  int giveID();
  void setID(int);
  void resetID();
};

#endif
