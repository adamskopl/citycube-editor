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
#ifndef __MD2_H
#define __MD2_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>

#include "object.h"
#include "texture.h"
#include "vector.h"

#define MAX_FRAMES 512

enum modelState_t
{
	MODEL_IDLE,		// bezczynnoœæ
	MODEL_CROUCH,		// kucanie
	MODEL_RUN,		// bieg
	MODEL_JUMP,		// skok
	MODEL_FIRE		// strza³
};

typedef struct
{
   float point[3];
} triangle;

triangle operator-(triangle a, triangle b);
triangle operator*(float f, triangle b);
triangle operator/(triangle a, triangle b);
triangle operator+(triangle a, triangle b);

void CalculateNormal( float *p1, float *p2, float *p3 );

typedef struct
{
   float s;
   float t;
} texCoord_t;

typedef struct
{
   short s;
   short t;
} stIndex_t;

typedef struct
{
   unsigned char v[3];
   unsigned char normalIndex;	// nie u¿ywane
} framePoint_t;

typedef struct
{
   float scale[3];
   float translate[3];
   char name[16];
   framePoint_t fp[1];
} frame_t;

typedef struct
{
   unsigned short meshIndex[3];		// indeksy wierzcho³ków
   unsigned short stIndex[3];		// indeksy wspo³rzêdnych tekstury
} mesh_t;

typedef struct
{
   int ident;		
   int version;		
   int skinwidth;    
   int skinheight;   
   int framesize;    
   int numSkins;     
   int numXYZ;       
   int numST;        
   int numTris;      
   int numGLcmds;
   int numFrames;    
   int offsetSkins;  
   int offsetST;     
   int offsetTris;   
   int offsetFrames; 
   int offsetGLcmds; 
   int offsetEnd;    
} modelHeader_t;


class LMd2 : public LObject
{
private:

     int numFrames;	
     int numVertices;         
     int numTriangles;        
     int numST;               
     int frameSize;           
     mesh_t *triIndex;        
     texCoord_t *st;          
     triangle *vertexList;    

     void loadTexture(const char *filePath);

     GLuint texture;
     void setupSkin();
     //     SDL_Surface *textureImage;

protected:
     modelState_t modelState;	
     int currentFrame;       
     int nextFrame;          

public:
     SDL_Surface *textureImage;
     float interpol;         

     LMd2();       
     ~LMd2();     

     int Load(const char *modelFile, const char *texturePath);
     int LoadModel(char *modelFile);
     int LoadSkin(char *skinFile);
     int Animate(int startFrame, int endFrame, float percent);

     void Unload();

     void SetState(modelState_t state);	
     modelState_t GetState();
};

#endif
