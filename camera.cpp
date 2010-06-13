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
#include "camera.h"
#include <GL/gl.h>
#include "object.h"
#include <math.h>


#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))
#define PI 3.14159265358979323846

LCamera::LCamera()
{
  //  position = LVector(400.5f, 2.0f, 19.0f)*10.0;
  //  lookAt = LVector(0.0, 0.0, 0.0);

}

LCamera::~LCamera()
{
}

void 
LCamera::mimeMode(LObject *actor)
{
  modeId = 1;
  this -> actor = actor;
}

void 
LCamera::spyMode(LObject* actor)
{
  this -> actor = actor;

  //data, that can be played with
  //such values should be loaded from .txt file - it will provide
  //easy data manipulating without compiling the code.
  //maybe variable editor in future ?
  distance = 100.0f;
  rotateX = 25.0f;
  camHeight = 50.0f;

  posA = LVector(actor -> position.x, actor -> position.y,
		     actor -> position.z);
  posB = posA;
  posDiff = 0.0f;

  speedInter = 3.0f;
  accelInter = 2.0f;

  rotActA = actor -> direction;
  rotActB = rotActA;

  rotSpeed = 0.0f;
  rotAccel = 0.0f;
  rotDiff = 0.0f;
  rotSpeedInter = 3.0f;
  rotAccelInter = 2.0f;

  modeId = 2;
}

void 
LCamera::updateRotation(scalar_t deltaTime)
{
  //final rotation is equal to actor's rotation
  rotActB = actor -> direction;

  //if new difference occur, new speed values must be calculated
  if(rotDiff !=rotActB - rotActA)
    {
      rotDiff = rotActB - rotActA;

      //the bigger difference is, the higher speed and acceleration are
      rotSpeed = rotDiff*rotSpeedInter;
      rotAccel = -rotDiff*rotAccelInter;
    }

  rotSpeed += rotAccel*deltaTime;
  rotActA += rotSpeed*deltaTime;
}

void
LCamera::updatePosition(scalar_t deltaTime)
{
  //final position is equal to actor's position
  posB = actor -> position;

  if(posDiff != posB - posA)
    {
      posDiff = posB - posA;
      
      //the bigger diference is, the higher speed and acceleration are
      speed = posDiff*speedInter;
      accel = -posDiff*accelInter;
    }

  speed += accel*deltaTime;
  posA += speed*deltaTime;
}

void 
LCamera::animate(scalar_t deltaTime)
{
  //reset ModelView matrix
  glLoadIdentity();

  switch(modeId)
    {
      //mimeMode
    case(1):
      {
	break;
      }
      //spyMode
    case(2): 
      {         
	float camX = -(posA.x);
	float camY = -(posA.y + camHeight);
	float camZ = -(posA.z);

	glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(-rotActA, 0.0f, 1.0f, 0.0f);

	float dx = (float)cos(DEG2RAD( -(rotActA) ))*distance;
	float dz = (float)sin(DEG2RAD( -(rotActA) ))*distance;

	//some miscalculations done... and dz is dx
	//	glTranslatef(dz, 0.0f, -dx);
	camX += dz;
	camZ -= dx;
	glTranslatef(camX, camY, camZ);

	updateRotation(deltaTime);
	updatePosition(deltaTime);
	break;
      }
    default:
      {
	LError("unknown camera mode!");
      }
    }
} 
