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
#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#include "error.h"

class LTexture
{
 private:
  long int scaledWidth;
  long int scaledHeight;
  
 public:
  GLuint textures;
  int width;
  int height;
  SDL_Surface *textureImage;
  LTexture();
  ~LTexture() { Unload(); }
  
  void loadTexture(char *);
  
  void Unload();

};

#endif
