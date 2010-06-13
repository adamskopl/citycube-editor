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
#include "being.h"

LBeing::LBeing()
{
	interpol = 3.0f;
	stateStart = 0;
	stateEnd = 39;
	animSpeed = 3.0f;
	direction = 0.0f;

	position = LVector(0,0,0);
	velocity = LVector(0,0,0.0);
	acceleration = LVector(0.0,0.0,0.0);
	size = 6.25f;

	field = NULL;
}

LBeing::~LBeing()
{

}

void LBeing::selfAnimate(float deltaTime)
{
	float cosYaw = (float)sin(DEG2RAD(direction));
	float sinYaw = (float)cos(DEG2RAD(direction)); 

	float speed = velocity.z * deltaTime;

	if ((direction >= 360.0f) || (direction <= -360.0f))
	  direction = 0.0f;

	float newx, newz;

	newx = float(cosYaw)*speed;
	position.x += newx;

	newz = float(sinYaw)*speed;
	
	position.z += newz;

	deltaT = deltaTime;	// used for interpolation
}


void LBeing::selfDraw(LCamera *camera)
{
  glPushMatrix();
  //  glTranslatef(position.x, position.y, position.z);
  glRotatef(-direction, 0.0, 1.0, 0.0);
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

  //	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
  glScalef(0.15, 0.15, 0.15);
	
  Animate(stateStart, stateEnd, deltaT*animSpeed);
  glPopMatrix();
}

void LBeing::selfPrepare()
{
	/*
	   Frame#  Action
	   ----------------
	   0-39    idle
	   40-46   running
	   47-60   getting shot but not falling (back bending)
	   61-66   getting shot in shoulder
	   67-73   jumping
	   74-95   idle
	   96-112  getting shot and falling down
	   113-122 idle
	   123-135 idle
	   136-154 crouch
	   155-161 crouch crawl
	   162-169 crouch adjust weapon (idle)
	   170-177 kneeling dying
	   178-185 falling back dying
	   186-190 falling forward dying
	   191-198 falling back slow dying
	*/
	srand((unsigned)time(NULL));

	switch (modelState)
	{
	case MODEL_IDLE:
		stateStart = 0;
		stateEnd = 39;
		break;
	case MODEL_CROUCH:
		break;
	case MODEL_RUN:
		stateStart = 40;
		stateEnd = 46;
		//		velocity = LVector(0.0, 0.0, 4.0);
		break;
	case MODEL_JUMP:
		stateStart = 67;
		stateEnd = 73;
		break;
	case MODEL_FIRE:
		stateStart = 0;
		stateEnd = 5;
		break;
	}

	// perform collision detection from this entity with all other objects in world
	checkCollisions(findRoot());
}

void LBeing::checkField(float DX, float DZ){

  float Hdistance = field -> GiveHorizontalDistance(position.x, position.z);
  float Vdistance = field -> GiveVerticalDistance(position.x, position.z);


  //  printf("H : %f     ", Hdistance);
  //  printf("V : %f   ",Vdistance);
  //  printf("%d\n",field->giveKind());
  /*
  if(field->giveUp())printf("UP ");
  if(field->giveRight())printf("RIGTH ");
  if(field->giveDown())printf("DOWN ");
  if(field->giveLeft())printf("LEFT ");
  printf("\n");*/

  
  
  if(Vdistance < 0.0){
    if(field->Passage(F_U)){
      field -> heroLeaves();
      field = field -> giveUp();
      field -> heroEnters();
    }
    else{
      position.z -= DZ;
      position.x -= DX;
    }
  }

  if(Vdistance > 1.0){
    if(field->Passage(F_D)){
      field -> heroLeaves();
      field = field -> giveDown();
      field -> heroEnters();
    }
    else{
      position.z -= DZ;
      position.x -= DX;
    }
  }

  if(Hdistance < 0.0){
    if(field->Passage(F_R)){
      field -> heroLeaves();
      field = field -> giveRight();
      field -> heroEnters();
    }
    else{
      position.x -= DX;
      position.z -= DZ;
    }
  }

  if(Hdistance > 1.0){
    if(field->Passage(F_L)){
      field -> heroLeaves();
      field = field -> giveLeft();
      field -> heroEnters();
    }
    else{
      position.x -= DX;
      position.z -= DZ;
    }
  }
  
  if(Hdistance > 0.88){
    if( ! (field->Passage(F_L)) ){
      position.x -= DX;
      position.z -= DZ;
    }
  }

  if(Hdistance < 0.12){
    if( ! (field->Passage(F_R)) ){
      position.x -= DX;
      position.z -= DZ;
    }
  }

  if(Vdistance > 0.88){
    if( ! (field->Passage(F_D)) ){
      position.x -= DX;
      position.z -= DZ;
    }
  }

  if(Vdistance < 0.12){
    if( ! (field->Passage(F_U)) ){
      position.x -= DX;
      position.z -= DZ;
    }
  }
}
