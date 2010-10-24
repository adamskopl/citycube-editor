#ifndef __EFIELD_H
#define __EFIELD_H

#include <stdio.h>
#include "camera.h"
#include "md2.h"
#include "node.h"
#include "vector.h"
#include "lbpassage.h"


/*
  [OLD VERSION]

  fields are defined in this way :  

  X X X X
  _______
  A B C D

  1 - wall
  0 - passage (clear)

                    A   
                 _______
 	        |       |
	    D   |       |   B
 	        |       |
 	        |_______|
 
	            C

  The system is simple : 
  [0x000D] in binary is 1101,
  so the defined field looks like that ...
                 _______
                |       |
                |       |
                |       |
                |       |


   ... and for 0x0006 (0110) ...

   
                        |
                        |
                        |
                 _______|

*/

#define CCCC 0x0000  
#define CCCW 0x0001  
#define CCWC 0x0002 
#define CCWW 0x0003 
#define CWCC 0x0004 
#define CWCW 0x0005 
#define CWWC 0x0006 
#define CWWW 0x0007 
#define WCCC 0x0008 
#define WCCW 0x0009 
#define WCWC 0x000A 
#define WCWW 0x000B 
#define WWCC 0x000C 
#define WWCW 0x000D 
#define WWWC 0x000E 
#define WWWW 0x000F 

#define F_U  0x0008
#define F_R  0x0004
#define F_D  0x0002
#define F_L  0x0001

class lbpassage;

typedef struct{
  float x, z;
}vector_xz;


//FINISH DISTANCE AND CLEAN UP
// real mess ... Corners, vector_xz, LVector ...

class LField : public LObject{
 public:
  char kind; //field's code (XXXX system)


  //CHANGE NAME, or code - conflict with cornersN
  vector_xz CornersN[4]; //UnitNormals (for DISTANCE)
  float distance; //heroe's distance 

  bool empty;

  //section with connections - pointers on other fields
  LField* conn_up;
  LField* conn_right;
  LField* conn_down;
  LField* conn_left;



//  bool walls; //walls or not ?
  
 public:
  //walls heights
  float walls[4];
  lbpassage *passageTree[4];

  LVector corners[4];

  //vector from cornerA to cornerB is vectorA
  //vector from cornerC to cornerD is vectorC ...
  LVector vectors[4];

  //normals for every corner
  LVector cornersN[4];

  //every vector has its own connection pointer (on other field's wall)
  LField* connections[4];

  LVector centerPoint;
  
  int up, right, down, left; //needed to loading levels

  LField(char KIND, LVector*);
  LField();
  ~LField();

  bool isPointIn(LVector point);
  bool isFieldTouching(LField*);
  bool isPassagePossible();

  void calculateVectorsAndNormals();

  float GiveHorizontalDistance(float X, float Z);
  float GiveVerticalDistance(float X, float Z);    

  char giveKind(); //returns field's code
  void setKind(char KIND); //sets field's code
  void heroEnters(void);
  void heroLeaves(void);
  
  void othersDraw();
  void selfDraw();

  void DrawMini();
  void OnDrawMini();
  
  char Passage(char);

  void ConnectUp(LField *connection, char);
  void ConnectRight(LField *connection, char);
  void ConnectDown(LField *connection, char);
  void ConnectLeft(LField *connection,char);  

  void ConnectUp(LField *connection);
  void ConnectRight(LField *connection);
  void ConnectDown(LField *connection);
  void ConnectLeft(LField *connection);  
  
  //return connected field
  LField* giveUp(void);
  LField* giveRight(void);
  LField* giveDown(void);
  LField* giveLeft(void);  

  //  bool connectionExists(LField *connection);
  bool connectTo(LField *connection);

  void remove ();
};

#endif
