#ifndef __EFIELD_H
#define __EFIELD_H

#include "camera.h"

#include "md2.h"

#include <GL/gl.h>
#include <GL/glu.h>

/*
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


typedef struct{
  float x, z;
}vector_xz;




typedef struct{
  CVector a, b, c, d;
}CORNERS;

//FINISH DISTANCE AND CLEAN UP
// real mess ... Corners, vector_xz, CVector ...

class EField : public CNode{
 public:
  char kind; //field's code (XXXX system)
  //  char x, y; //coordinations
 private:

  vector_xz Corners[4];
  vector_xz CornersN[4]; //UnitNormals
  float distance; //heroe's distance 
  
  bool empty;

  //section with connections - pointers on other fields
  EField* conn_up;
  EField* conn_right;
  EField* conn_down;
  EField* conn_left;
  bool walls; //walls or not ?
  
 public:
  CORNERS corners;


  int index; //index of the field, to save
  int up, right, down, left; //to save in file (we can't save pointers)

  
  EField(char KIND, CORNERS*);
  EField();

  float GiveHorizontalDistance(float X, float Z);
  float GiveVerticalDistance(float X, float Z);    

  char giveKind(); //returns field's code
  void setKind(char KIND); //sets field's code
  void heroEnters(void);
  void heroLeaves(void);
  
  void Draw();
  void OnDraw();

  void DrawMini();
  void OnDrawMini();
  
  char Passage(char);

  void ConnectUp(EField *connection, char);
  void ConnectRight(EField *connection, char);
  void ConnectDown(EField *connection, char);
  void ConnectLeft(EField *connection,char);  

  void Disconnect(char);//destroy connection
  
  //return connected field
  EField* giveUp(void);
  EField* giveRight(void);
  EField* giveDown(void);
  EField* giveLeft(void);  
  
};








#endif
