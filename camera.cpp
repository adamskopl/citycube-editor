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
  modeId = 2;

  this -> actor = actor;

  //data, that can be played with
  //such values should be loaded from .txt file - it will provide
  //easy data manipulating without compiling the code.
  //maybe variable editor in future ?
  CP.posA = LVector(actor -> position.x, actor -> position.y, actor -> position.z);
  CP.posB = CP.posA;
  CP.pos_S = 0.0f;
  CP.pos_A = 0.0f;
  CP.pos_SM = 3.0f;
  CP.pos_AM = 2.0f;
  CP.pos_D = 0.0f;

  CP.distB = 300.0f;
  CP.distA = 300.0f;
  CP.dist_S = 0.0f;
  CP.dist_A = 0.0f;
  CP.dist_SM = 1.5f;
  CP.dist_AM = 1.2f;
  CP.dist_D = 0.0f;

  CP.rotActA = 0.0f;
  CP.rotActB = 0.0f;
  CP.rotAct_S = 0.0f;
  CP.rotAct_A = 0.0f;
  CP.rotAct_SM = 3.0f;
  CP.rotAct_AM = 2.0f;
  CP.rotAct_D = 0.0f;

  CP.heightB = 200.0f;
  CP.heightA = 200.0f;
  CP.height_S = 0.0f;
  CP.height_A = 0.0f;
  CP.height_SM = 3.0f;
  CP.height_AM = 2.0f;
  CP.height_D = 0.0f;

  CP.rotXB = 25.0f;
  CP.rotXA = 25.0f;
  CP.rotX_S = 0.0f;
  CP.rotX_A = 0.0f;
  CP.rotX_SM = 3.0f;
  CP.rotX_AM = 2.0f;
  CP.rotX_D = 0.0f;
}

/*

  __Updating every of parameter looks like this:__

void
LCamera::updateName(scalar_t deltaTime)
{
  nameB = //(final name Value, if it is defined by other object);

  //if new difference occur, new speed values must be calculated
  if(CP.name_D != CP.nameB - CP.nameA)
    {
      //update difference
      CP.name_D = CP.nameB - CP.nameA;

      //the bigger difference is, the higher speed and acceleration are
      CP.name_S = CP.name_D * CP.name_SM;
      CP.name_A = -CP.name_D * CP.name_AM;      
    }

  //new speed's value: increase it by acceleration
  CP.name_S += CP.name_A*deltaTime;

  //change nameA's value, to be closer to nameB vaule's
  CP.nameA += CP.name_S*deltaTime;
}

*/

void 
LCamera::updateRotAct(scalar_t deltaTime)
{
  //final rotation
  //  rotActB = finalRotY;

  //if new difference occur, new speed values must be calculated
  if(CP.rotAct_D !=CP.rotActB - CP.rotActA)
    {
      CP.rotAct_D = CP.rotActB - CP.rotActA;

      //the bigger difference is, the higher speed and acceleration are
      CP.rotAct_S = CP.rotAct_D*CP.rotAct_SM;
      CP.rotAct_A = -CP.rotAct_D*CP.rotAct_AM;
    }

  CP.rotAct_S += CP.rotAct_A*deltaTime;
  CP.rotActA += CP.rotAct_S*deltaTime;
}

/*void
LCamera::updateRotX(scalar_t deltaTime)
{

}*/

void
LCamera::updateDist(scalar_t deltaTime)
{
  //  distB = 

  //if new difference occur, new speed values must be calculated
  if(CP.dist_D != CP.distB - CP.distA)
    {
      //update difference
      CP.dist_D = CP.distB - CP.distA;
      
      //the bigger difference is, the higher speed and acceleration are
      CP.dist_S = CP.dist_D * CP.dist_SM;
      CP.dist_A = -CP.dist_D * CP.dist_AM;      
    }

  //new speed's value: increase it by acceleration
  CP.dist_S += CP.dist_A*deltaTime;

  //change distA's value, to be closer to distB vaule's
  CP.distA += CP.dist_S*deltaTime;
}

void
LCamera::updatePos(scalar_t deltaTime)
{
  //final position is equal to actor's position
  CP.posB = actor -> position;

  if(CP.pos_D != CP.posB - CP.posA)
    {
      CP.pos_D = CP.posB - CP.posA;
      
      //the bigger diference is, the higher speed and acceleration are
      CP.pos_S = CP.pos_D*CP.pos_SM;
      CP.pos_A = -CP.pos_D*CP.pos_AM;
    }

  CP.pos_S += CP.pos_A*deltaTime;
  CP.posA += CP.pos_S*deltaTime;
}

void
LCamera::updateRotX(scalar_t deltaTime)
{
  //rotXB = //(final rotX Value, if it is defined by other object);

  //if new difference occur, new speed values must be calculated
  if(CP.rotX_D != CP.rotXB - CP.rotXA)
    {
      //update difference
      CP.rotX_D = CP.rotXB - CP.rotXA;

      //the bigger difference is, the higher speed and acceleration are
      CP.rotX_S = CP.rotX_D * CP.rotX_SM;
      CP.rotX_A = -CP.rotX_D * CP.rotX_AM;      
    }

  //new speed's value: increase it by acceleration
  CP.rotX_S += CP.rotX_A*deltaTime;

  //change rotXA's value, to be closer to rotXB vaule's
  CP.rotXA += CP.rotX_S*deltaTime;
}

void
LCamera::updateHeight(scalar_t deltaTime)
{
  //  heightB = //(final height Value, if it is defined by other object);

  //if new difference occur, new speed values must be calculated
  if(CP.height_D != CP.heightB - CP.heightA)
    {
      //update difference
      CP.height_D = CP.heightB - CP.heightA;

      //the bigger difference is, the higher speed and acceleration are
      CP.height_S = CP.height_D * CP.height_SM;
      CP.height_A = -CP.height_D * CP.height_AM;      
    }

  //new speed's value: increase it by acceleration
  CP.height_S += CP.height_A*deltaTime;

  //change heightA's value, to be closer to heightB vaule's
  CP.heightA += CP.height_S*deltaTime;
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
	float camX = -(CP.posA.x);
	float camY = -(CP.posA.y + CP.heightA);
	float camZ = -(CP.posA.z);

	glRotatef(CP.rotXA, 1.0f, 0.0f, 0.0f);
	glRotatef(-CP.rotActA, 0.0f, 1.0f, 0.0f);

	float dx = (float)cos(DEG2RAD( -(CP.rotActA) ))*CP.distA;
	float dz = (float)sin(DEG2RAD( -(CP.rotActA) ))*CP.distA;

	//some miscalculations done... and dz is dx
	//	glTranslatef(dz, 0.0f, -dx);
	camX += dz;
	camZ -= dx;
	glTranslatef(camX, camY, camZ);

	updateRotAct(deltaTime);
	updateRotX(deltaTime);
	updateDist(deltaTime);
	updatePos(deltaTime);
	updateHeight(deltaTime);

	break;
      }
    default:
      {
	LError("unknown camera mode!");
      }
    }
} 

void
LCamera::modRotActB(float dRotAct)
{
  if(CP.rotActB != CP.rotActB+dRotAct)
    {
      CP.rotActB += dRotAct;
    }
}

void 
LCamera::modRotXB(float dRotX)
{
  if(CP.rotXB != CP.rotXB + dRotX)
    {
      CP.rotXB += dRotX;
    }
}

void 
LCamera::modDistB(float dDist)
{
  if(CP.distB != CP.distB + dDist)
    {
      CP.distB += dDist;
    }
}

void 
LCamera::modHeightB(float dHeight)
{
  if(CP.heightB != CP.heightB + dHeight)
    {
      CP.heightB += dHeight;
    }
}
/*
void
LCamera::negFinalRotY()
{
  finalRotY = -finalRotY;
  }*/

void
LCamera::reset()
{
  CP.rotActB = 0.0f;
  CP.rotXB = 20.0f;
  CP.heightB = 200.0f;
  CP.distB = 300.0f;
}
