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
#ifndef __CLOCK_H
#define __CLOCK_H
/*
  Time measuring idea copied from:

  http://linuxdevcenter.com/pub/a/linux/2003/10/23/sdl_anim.html
  by Bob Pendleton

 */
#include <SDL/SDL.h>
class EClock
{
private:
  int startTime;              // Last time the clock was
                              // started.
  int baseTime;               // How much game time passed
                              // before the last time the
                              // clock was started.
  bool running;               // Is the clock running or
                              // not?

  int help;

public:

  // Initialize the class variables. At this point no game
  // time has elapsed and the clock is not running.
  EClock();
  // Start the clock.

  void start();
  // Stop the clock

  void stop();
  // True if the clock is paused.

  bool stopped();
  // Get this clocks current time in milliseconds.

  int time();

};

#endif
