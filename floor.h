#ifndef FLOOR_H
#define FLOOR_H
#include "object.h"
#include "counter.h"

enum statusFloorTypes
  {
    noneFloor,
    chosenFloor
  };

class LBFloor : public LObject, public Counter<LBFloor>
{
  //floor is a root of fields belonging to it
  
 private:
  statusFloorTypes statusFloor;
  static statusFloorTypes statusFloors;
  
  
 public:
  LBFloor(int, float);
  
  float height;
  bool isItDrawn;
  bool isItRendered;
  
  void drawFloor();
  //    void setFloorStatus(floorStatus);
  
  void setSFloor(statusFloorTypes S){statusFloor = S;}
  statusFloorTypes giveSFloor(void){return statusFloor;}
  
  static void setSFloors(statusFloorTypes S){statusFloors = S;}
  static statusFloorTypes giveSFloors(void){return statusFloors;}
  
};

#endif // FLOOR_H
