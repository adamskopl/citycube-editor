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
#ifndef __WORLD_H
#define __WORLD_H


#include "camera.h"
#include "object.h"
#include "being.h"

#include "vector.h"
#include "field.h"
#include "hero.h"
#include <vector>

#include <stdlib.h>
using namespace std;

class LWorld{


 protected:
  void OnPrepare();
  
 public:
  LCamera *camera;

  int screenWidth;
  int screenHeight;
  
  LWorld(LObject *);
  ~LWorld();
  void buildWorld();
  void destroyWorld();
  void prepare(){ OnPrepare(); }
  void draw(LCamera *);
  void animate(int Deltatime);
  void drawMap();
  void drawText();

  LHero *hero;
  LBeing *root;

  LObject *floorsTree;


  int loadLevel(const char *);
  void drawFloors();
};
#endif
