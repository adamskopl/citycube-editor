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
#ifndef __HERO_H
#define __HERO_H

#include "being.h"
#include "camera.h"

class LHero : public LBeing{

  void selfPrepare();
  void selfDraw(LCamera*);
 
 public:

  LHero();

  //crosshair ... needed for old game conception
  /*
  LVector crosshair_position;
  float crosshair_angle[2];
  float crosshair_max[2];
  float crosshair_min[0];
  */

  float mouseX, mouseY;
  
};

#endif
