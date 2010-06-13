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
#ifndef __ENGINE_H
#define __ENGINE_H


//#include "input.h"
#include "clock.h"
#include "camera.h"
//#include "window.h"
#include "world.h"
#include <SDL/SDL.h>

class LEngine {

  EClock *clock;
  SDL_Event event;
  Uint32 start;
  
  bool loopDone;
  
  LCamera *gameCamera;
  LWorld *gameWorld;
  
 public:
  LEngine();

  int fieldsCount;
  void launch();

};

#endif
