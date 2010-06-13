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
#include <SDL/SDL.h>
#include "clock.h"


EClock::EClock()
{
  startTime = 0;
  baseTime = 0;
  running = false;
}

// Start the clock.
void EClock::start()
{
  if (!running){
    startTime = SDL_GetTicks();
    running = true;
    baseTime = SDL_GetTicks();
  }
}

// Stop the clock
void EClock::stop()
{
  if (running){
    baseTime = baseTime + (SDL_GetTicks() - startTime);
    running = false;
  }
}

// True if the clock is paused.
bool EClock::stopped()
{
  return !running;
}

// Get this clocks current time in milliseconds.
// modified : get time in milliseconds, which have passed since
//            last exec. of time()
int EClock::time()
{
  if (running){
    help = baseTime;
    baseTime = SDL_GetTicks();
    return baseTime - help;
  }
  else{
    return baseTime;
  }
}
