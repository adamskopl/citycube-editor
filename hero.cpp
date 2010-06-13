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
#include "hero.h"

LHero::LHero(){
  
}


void LHero::selfPrepare()
{
  /*  crosshair_angle[1] = (float)((float)mouseX/(float)screenWidth)*30.0 - 15.0
  +direction;
  
  crosshair_angle[0] = (float)((float)mouseY/(float)screenHeight)*40.0 - 20.0;

  crosshair_position = position;

  crosshair_position.z += (float)sin(DEG2RAD(crosshair_angle[1]))*20.0;
  crosshair_position.x += (float)cos(DEG2RAD(crosshair_angle[1]))*20.0;

  crosshair_position.y += (float)sin(DEG2RAD(-crosshair_angle[0]))*20.0;
  */

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

	checkCollisions(findRoot());
}
/*
  NOTES
  # Kim's eyes could be some kind of geometric figure
    (to show her eyes blink)

 */
void LHero::selfDraw(LCamera* camera)
{
  glPushMatrix();
  {
    glTranslatef(position.x, position.y, position.z);
    //    printf("hero:   %f, %f, %f\n", position.x, position.y, position.z);
    //    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(direction, 0.0, 1.0, 0.0);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.15, 0.15, 0.15);
    Animate(stateStart, stateEnd, deltaT*animSpeed);
  }
  glPopMatrix();
}
