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
#ifndef __CAMERA_H
#define __CAMERA_H

#include "vector.h"
#include "error.h"

//#include "object.h"
class LObject;



  /*
    CAMERA IS OPERATING FOR NOW ONLY IN MIME MODE
    its parameters are:

    - pos (position in the world)
    - rotAct (roatation around the actor)
    - rotX (rotation around camera's local X)
    - dist (distance from an actor)
    - height (how high we are upon an actor?)

    Camera is observing actor.

    Every parameter is changed gradually, so for now, following convenience is taken:
    
    name             - how parameter is named, but it's not used alone (nameA and 
                       nameB are used)
    nameA, nameB     - actual and final name's values (camera is gradually 
                       equalizing 
                       these values: from A to B)
    name_S           - speed of changes (sounds stupid, I know ...)
    name_A	     - accelaration of changes

    name_ParameterM   - parameter's changes modificator (by manipulating it, changes
                       are acting in different ways)

    nameD             - difference between nameA and nameB
  */
typedef struct 
{
  //TODO:
  /*
    create enum PARAMETERS {pos, height, rotAct ...}
    and array which elements are chosen with enum PARAMETERS
    
    because every parameter act the same:

    parameters[height].modB(); -> change heightB
    parameters[rotAct].update(); -> update rotActA

    every parameter have equal value named the same:
    'rotActA' and 'heigthA' are just 'parA'.

    for(int a = 0; a < PAR_NUMBER; a++)
      {
        parameters[a].par_SM = 3.0f;
      }
   */

  //pos 
  LVector posA, posB;
  LVector pos_S, pos_A;
  float pos_SM, pos_AM;
  LVector pos_D;
  
  //rotAct
  float rotActA, rotActB;
  float rotAct_S, rotAct_A;
  float rotAct_SM, rotAct_AM;
  float rotAct_D;

  //rotX - later
  float rotXA, rotXB;
  float rotX_S, rotX_A;
  float rotX_SM, rotX_AM;
  float rotX_D;

  //dist
  float distA, distB;
  float dist_S, dist_A;
  float dist_SM, dist_AM;
  float dist_D;

  //height
  float heightA, heightB;
  float height_S, height_A;
  float height_SM, height_AM;
  float height_D;

}camParam;

class LCamera
{
private:
  camParam CP;


public:
  float rotateX, rotateY, rotateZ;


  /*
  //actual, final position
  LVector posA, posB;
  LVector speed, accel;		
  //parameters for manipulating speed and acceleration
  float speedPar, accelPar;
  //difference between positions
  LVector posDiff;

  //actual and final rotation around actor
  float rotActA, rotActB;
  float rotActSpeed, rotActAccel;
  //parameters for modyfing rotation's speed and acceleration
  float rotActSpeedPar, rotActAccelPar;
  //difference between rotatations
  float rotDiff;

  //how far from actor?
  float distance;
  float camHeight;

  */


  //calculate new values:
  void updatePos(scalar_t);
  void updateRotAct(scalar_t);
  void updateRotX(scalar_t);
  void updateDist(scalar_t);
  void updateHeight(scalar_t);



  LCamera();
  ~LCamera();

  //1)mimeMode - follows object without delay
  void mimeMode(LObject*);

  //2)spyMode - follows object with delay
  void spyMode(LObject*);

  //target of actual camera's mode
  LObject *actor;
  //which mode is on ?
  int modeId;

  void animate(scalar_t deltaTime);

  float finalRotY;
  float finalRotX;
  float finalDist;

  void modRotActB(float dRotY);
  void modRotXB(float dRotX);
  void modDistB(float dDistance);
  void modHeightB(float dHeight);

  void reset();
  //  void negFinalRotY();

};

#endif
