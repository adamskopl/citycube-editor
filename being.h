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
#ifndef __BEING_H
#define __BEING_H

#include <stdlib.h>
#include <time.h>

#include "md2.h"
#include "object.h"
#include "camera.h"
#include "field.h"
#include <SDL/SDL.h>

#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))
#define PI 3.14159265358979323846

class LBeing : public LMd2
{
protected:
 public:

  float oldZ;
  void selfAnimate(float deltaTime);

  void selfDraw(LCamera *camera);
  void selfPrepare();

public:

  LField *field;//on which field 
  //     float direction;                                       

     LBeing();
     ~LBeing();

     int stateStart, stateEnd;
     float deltaT; 
     float animSpeed; 

     void checkField(float DX, float DZ);//DX and DY were added now
                                    //substract them, if necessary
     
};

#endif
