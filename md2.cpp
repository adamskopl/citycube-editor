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
#include "md2.h"

void CalculateNormal( float *p1, float *p2, float *p3 )
{
  float a[3], b[3], result[3];
  float length;
  
  a[0] = p1[0] - p2[0];
  a[1] = p1[1] - p2[1];
  a[2] = p1[2] - p2[2];
  
  b[0] = p1[0] - p3[0];
  b[1] = p1[1] - p3[1];
  b[2] = p1[2] - p3[2];
  
  result[0] = a[1] * b[2] - b[1] * a[2];
  result[1] = b[0] * a[2] - a[0] * b[2];
  result[2] = a[0] * b[1] - b[0] * a[1];
  
  length = (float)sqrt(result[0]*result[0] + result[1]*result[1] + result[2]*result[2]);
  
  glNormal3f(result[0]/length, result[1]/length, result[2]/length);
}

triangle operator-(triangle a, triangle b)
{
  triangle c;
  
  c.point[0] = a.point[0] - b.point[0];
  c.point[1] = a.point[1] - b.point[1];
  c.point[2] = a.point[2] - b.point[2];
  
  return c;
}

triangle operator*(float f, triangle b)
{
  triangle c;
  
  c.point[0] = f * b.point[0];
  c.point[1] = f * b.point[1];
  c.point[2] = f * b.point[2];
  
  return c;
}

triangle operator/(triangle a, triangle b)
{
  triangle c;
  
  c.point[0] = a.point[0] / b.point[0];
  c.point[1] = a.point[1] / b.point[1];
  c.point[2] = a.point[2] / b.point[2];
  
  return c;
}

triangle operator+(triangle a, triangle b)
{
  triangle c;
  
  c.point[0] = a.point[0] + b.point[0];
  c.point[1] = a.point[1] + b.point[1];
  c.point[2] = a.point[2] + b.point[2];
  
  return c;
}

LMd2::LMd2()
{
  numVertices = 0;    // vertices
  numTriangles = 0;   // triangles
  numFrames = 0;      // frames
  numST = 0;          // texture coordinates
  frameSize = 0;      // needed?
  currentFrame = 0;   // current keyframe 
  nextFrame = 1;      // next keyframe
  interpol = 0.0;     // interpolation percent
  triIndex = NULL;    // triangle indices
  st = NULL;          // texture coordinate indices
  vertexList = NULL;  // vertices
  modelState = MODEL_IDLE;
}    

LMd2::~LMd2()
{
  Unload();
}

void LMd2::loadTexture(const char *texturePath)
{
  textureImage = IMG_Load(texturePath);
  if(!textureImage)
    {
      LError(SDL_GetError());
    }
}

void LMd2::setupSkin()
{
  // set the proper parameters for an MD2 texture
  //  glGenTextures(1, &thisTexture->texID);
  //  glBindTexture(GL_TEXTURE_2D, thisTexture->texID);
  glGenTextures( 1, &texture );

  glBindTexture( GL_TEXTURE_2D, texture );


  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


  glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage->w, textureImage->h, 0, 
      		GL_BGR, GL_UNSIGNED_BYTE, textureImage->pixels);


  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, textureImage -> w, 
  		    textureImage -> h,
    		    GL_RGBA, GL_UNSIGNED_BYTE, textureImage -> pixels);
}

int LMd2::Load(const char *modelFile,const char *texturePath)
{
  FILE *filePtr;                          // file pointer
  int fileLen;                            // length of model file
  char *buffer;                           // file buffer
  
  modelHeader_t *modelHeader;             // model header
  
  stIndex_t *stPtr;                       // texture data
  frame_t *frame;                              // frame data
  triangle *vertexListPtr;                // index variable
  mesh_t *bufIndexPtr;          // index variables
  int i, j;                               // index variables
  
  // open the model file
  filePtr = fopen(modelFile, "rb");
  if (filePtr == NULL)
    return false;
  
  // find length of file
  fseek(filePtr, 0, SEEK_END);
  fileLen = ftell(filePtr);
  fseek(filePtr, 0, SEEK_SET);
  
  // read entire file into buffer
  buffer = new char [fileLen+1];
  fread(buffer, sizeof(char), fileLen, filePtr);
  
  // extract model file header from buffer
  modelHeader = (modelHeader_t*)buffer;
  
  vertexList = new triangle [modelHeader->numXYZ * modelHeader->numFrames];
  
  numVertices = modelHeader->numXYZ;
  numFrames = modelHeader->numFrames;
  frameSize = modelHeader->framesize;
  
  for (j = 0; j < numFrames; j++)
    {
      frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];
      
      vertexListPtr = (triangle*)&vertexList[numVertices * j];
      for (i = 0; i < numVertices; i++)
	{
	  vertexListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
	  vertexListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
	  vertexListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
	}
    }

  loadTexture(texturePath);
  setupSkin();
  


  numST = modelHeader->numST;
  st = new texCoord_t [numST];
  
  stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];


  for (i = 0; i < numST; i++)
    {
      st[i].s = (float)stPtr[i].s / (float)textureImage -> w;
      st[i].t = (float)stPtr[i].t / (float)textureImage -> h;
    }

  numTriangles = modelHeader->numTris;
  triIndex = new mesh_t [numTriangles];
  
  // point to triangle indexes in buffer
  bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];
  
  // create a mesh (triangle) list
  for (j = 0; j < numFrames; j++)         
    {
      // for all triangles in each frame
      for(i = 0; i < numTriangles; i++)
	{
	  triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
	  triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
	  triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
	  triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
	  triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
	  triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
	}
    }
  
  // close file and free memory
  fclose(filePtr);
  delete buffer;
  
  currentFrame = 0;
  nextFrame = 1;
  interpol = 0.0;
  
  return true;
}
int LMd2::Animate(int startFrame, int endFrame, float percent)
{
  triangle *vList;              // current frame vertices
  triangle *nextVList;          // next frame vertices
  int i;                                  // index counter
  float x1, y1, z1;                  // current frame point values
  float x2, y2, z2;                  // next frame point values
  
  triangle vertex[3]; 
  
  if ((startFrame > currentFrame))
    currentFrame = startFrame;
  
  if ((startFrame < 0) || (endFrame < 0))
    return -1;
  
  if ((startFrame >= numFrames) || (endFrame >= numFrames))
    return -1;
  
  if (interpol >= 1.0)
    {
      interpol = 0.0f;
      currentFrame++;
      if (currentFrame >= endFrame)
	currentFrame = startFrame;
      
      nextFrame = currentFrame + 1;
      
      if (nextFrame >= endFrame)
	nextFrame = startFrame;
    }
  
  vList = &vertexList[numVertices*currentFrame];
  nextVList = &vertexList[numVertices*nextFrame];
  
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glBindTexture(GL_TEXTURE_2D, 1);
  

  glBegin(GL_TRIANGLES);
  for (i = 0; i < numTriangles; i++)
    {
      // get first points of each frame
      x1 = vList[triIndex[i].meshIndex[0]].point[0];
      y1 = vList[triIndex[i].meshIndex[0]].point[1];
      z1 = vList[triIndex[i].meshIndex[0]].point[2];
      x2 = nextVList[triIndex[i].meshIndex[0]].point[0];
      y2 = nextVList[triIndex[i].meshIndex[0]].point[1];
      z2 = nextVList[triIndex[i].meshIndex[0]].point[2];
      
      // store first interpolated vertex of triangle
      vertex[0].point[0] = x1 + interpol * (x2 - x1);
      vertex[0].point[1] = y1 + interpol * (y2 - y1);
      vertex[0].point[2] = z1 + interpol * (z2 - z1);
      
      // get second points of each frame
      x1 = vList[triIndex[i].meshIndex[2]].point[0];
      y1 = vList[triIndex[i].meshIndex[2]].point[1];
      z1 = vList[triIndex[i].meshIndex[2]].point[2];
      x2 = nextVList[triIndex[i].meshIndex[2]].point[0];
      y2 = nextVList[triIndex[i].meshIndex[2]].point[1];
      z2 = nextVList[triIndex[i].meshIndex[2]].point[2];
      
      // store second interpolated vertex of triangle
      vertex[2].point[0] = x1 + interpol * (x2 - x1);
      vertex[2].point[1] = y1 + interpol * (y2 - y1);
      vertex[2].point[2] = z1 + interpol * (z2 - z1);   
      
      // get third points of each frame
      x1 = vList[triIndex[i].meshIndex[1]].point[0];
      y1 = vList[triIndex[i].meshIndex[1]].point[1];
      z1 = vList[triIndex[i].meshIndex[1]].point[2];
      x2 = nextVList[triIndex[i].meshIndex[1]].point[0];
      y2 = nextVList[triIndex[i].meshIndex[1]].point[1];
      z2 = nextVList[triIndex[i].meshIndex[1]].point[2];
      
      // store third interpolated vertex of triangle
      vertex[1].point[0] = x1 + interpol * (x2 - x1);
      vertex[1].point[1] = y1 + interpol * (y2 - y1);
      vertex[1].point[2] = z1 + interpol * (z2 - z1);
      
      // calculate the normal of the triangle
      CalculateNormal(vertex[0].point, vertex[2].point, vertex[1].point);

      glTexCoord2f(st[triIndex[i].stIndex[0]].s,
		   st[triIndex[i].stIndex[0]].t);
      glVertex3fv(vertex[0].point);

          
      glTexCoord2f(st[triIndex[i].stIndex[2]].s ,
		   st[triIndex[i].stIndex[2]].t);
      glVertex3fv(vertex[2].point);
          
      glTexCoord2f(st[triIndex[i].stIndex[1]].s,
		   st[triIndex[i].stIndex[1]].t);
      glVertex3fv(vertex[1].point);
    }
    glEnd();
  interpol += percent;  // increase percentage of interpolation between frames
  
  return 0;
}

void LMd2::Unload()
{
  if (triIndex != NULL)
    delete [] triIndex;//free(triIndex);
  if (vertexList != NULL)
    delete [] vertexList;//free(vertexList);
  if (st != NULL)
    delete [] st; //free(st);
  
}

void LMd2::SetState(modelState_t state)
{
  modelState = state;
}

modelState_t LMd2::GetState()
{
  return modelState;
}

