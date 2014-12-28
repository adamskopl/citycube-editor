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
//#include "window.h"
#include "engine.h"

LEngine::LEngine(){
  clock = new EClock;

  //gameWorld = new LWorld();

  gameCamera = gameWorld -> camera;
  
  loopDone = false;
}

void LEngine::launch(){

  clock -> start();

  //glViewport(0,0,screenWidth, screenHeight);

  glMatrixMode(GL_PROJECTION);		       
  glLoadIdentity();

  //REPLACE gluPerspective WITH SOMETHING ELSE 
  //no GLU at all
  //gluPerspective(54.0f,(GLfloat)screenWidth/(GLfloat)screenHeight,0.1,200.0f);

  glLineWidth(0.2f);

  //fieldsCount = gameWorld -> loadLevel("levels/levelOne.lvl");
  glMatrixMode(GL_MODELVIEW);		  

  while (!loopDone){
      float timePassed = clock -> time();

      //prepare camera
      gameCamera -> animate((float)timePassed/1000.0f);
      gameWorld -> prepare();
      gameWorld -> draw(gameCamera);
      gameWorld -> animate(timePassed);
      //      gameWorld -> drawText();

      SDL_GL_SwapBuffers();     
  }
}
