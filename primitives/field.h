#ifndef __EFIELD_H
#define __EFIELD_H

#include <stdio.h>
#include "camera.h"
#include "md2.h"
#include "node.h"
#include "vector.h"
#include "lbpassage.h"
#include "lbwindow.h"
#include "counter.h"
#include "lbmathhelper.h"

class lbpassage;

typedef struct{
  float x, z;
}vector_xz;


/*
  used to set status of field or all fields - for example "actual" means to draw 
  fields other way than usual (to point which of them are actual)
*/
enum statusFieldTypes
  {
    noneField,
    chosenField,
    pointedField
  };



/*typedef struct{
  //pos on Wall, not in global space
  LVector pos;
  float width, height;
  }LBWindow;*/

//FINISH DISTANCE AND CLEAN UP
// real mess ... Corners, vector_xz, LVector ...


class LField : public LObject, public Counter<LField>{
 public:

  //CHANGE NAME, or code - conflict with cornersN
  vector_xz CornersN[4]; //UnitNormals (for DISTANCE)
  float distance; //heroe's distance 

  bool empty;

 public:
  //walls heights
  float walls[4];
  
  //every edge has its own passage tree
  lbpassage *passageTree[4];
  //every wall has its own window tree
  LBWindow *windowTree[4];

  LVector corners[4];

  //vector from cornerA to cornerB is vectorA
  //vector from cornerC to cornerD is vectorC ...
  LVector vectors[4];

  //normals for every corner
  LVector cornersN[4];

  //every vector has its own connection pointer (on other field's wall)
  //  LField* connections[4];

  LVector centerPoint;
  
  LField(int ID, LVector*);
  LField();
  ~LField();

  bool isPointIn(LVector point);
  bool isFieldTouching(LField*);
  bool isPassagePossible();

  void calculateVectorsAndNormals();

  float GiveHorizontalDistance(float X, float Z);
  float GiveVerticalDistance(float X, float Z);    

  void heroEnters(void);
  void heroLeaves(void);
  
  void othersDraw();
  void selfDraw();

  void DrawMini();
  void OnDrawMini();
  
  char Passage(char);

  float howFarPointIs(int wallIndex, LVector point);

  void remove ();

  void setSField(statusFieldTypes S){statusField = S;}
  static void setSFields(statusFieldTypes S){statusFields = S;}
  
  //delete all passages leading to destField
  void deletePassagesTo(LObject *destField);

 private:
  static int fieldsCnt;

  //status of this one particular field
  statusFieldTypes statusField;
  //status of all fields
  static statusFieldTypes statusFields;
};




#endif
