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
#ifndef __CAMERA_H
#define __CAMERA_H

#include "vector.h"
#include "error.h"

//#include "object.h"
class LObject;

class LCamera
{
private:


public:
  LVector speed;		
  LVector accel;		

  float rotateX, rotateY, rotateZ;

  //actual, final position and difference between them
  LVector posA, posB;
  //values for manipulating speed and acceleration
  float speedInter, accelInter;
  //difference between positions
  LVector posDiff;

  //actual and final rotation around actor
  float rotActA, rotActB;
  float rotSpeed, rotAccel;
  //values for manipulating rotation's speed and acceleration
  float rotSpeedInter, rotAccelInter;
  //difference between rotatations
  float rotDiff;

  //how far from actor?
  float distance;
  float camHeight;
  //calculate new values
  void updateRotation(scalar_t);
  void updatePosition(scalar_t);
  LCamera();
  ~LCamera();

  //1)mimeMode - follows object without delay
  void mimeMode(LObject*);

  //2)spyMode - follows object with delay
  void spyMode(LObject*);

  //target of actual camera's mode
  LObject *actor;
  //which mode is on ?
  int modeId;

  void animate(scalar_t deltaTime);
};

#endif
