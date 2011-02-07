#include "lbxmlmanager.h"
#include "lbstairs.h"
#include<iostream>

enum XMLBuildingNodes
  {
    xml_floorsTree, xml_floor, xml_ID, xml_fieldsTree, xml_field, xml_corners,
    xml_vector, xml_v3x, xml_v3y, xml_v3z, xml_walls, xml_wall, xml_windowsTree, 
    xml_window, xml_position, xml_dimensions, xml_width, xml_height, xml_doorsTree, 
    xml_doors, xml_dist1, xml_dist2, xml_destination, xml_stairsTree, xml_stairs, 
    xml_bottomDoors, xml_topDoors, xml_bottomDest, xml_topDest, xml_bottom, xml_top,
    xml_horizontalVector, xml_unknown
  };


XMLBuildingNodes compareNodeString(const char* nodeS)
{
  if (!strcmp(nodeS, "floorsTree")){return xml_floorsTree;}
  if (!strcmp(nodeS, "floor")){return xml_floor;}  
  if (!strcmp(nodeS, "ID")){return xml_ID;}  
  if (!strcmp(nodeS, "fieldsTree")){return xml_fieldsTree;}  
  if (!strcmp(nodeS, "field")){return xml_field;}  
  if (!strcmp(nodeS, "corners")){return xml_corners;}  
  if (!strcmp(nodeS, "vector")){return xml_vector;}  
  if (!strcmp(nodeS, "v3x")){return xml_v3x;}
  if (!strcmp(nodeS, "v3y")){return xml_v3y;}
  if (!strcmp(nodeS, "v3z")){return xml_v3z;}
  if (!strcmp(nodeS, "walls")){return xml_walls;}  
  if (!strcmp(nodeS, "wall")){return xml_wall;}  
  if (!strcmp(nodeS, "windowsTree")){return xml_windowsTree;}  
  if (!strcmp(nodeS, "window")){return xml_window;}  
  if (!strcmp(nodeS, "position")){return xml_position;}  
  if (!strcmp(nodeS, "dimensions")){return xml_dimensions;}  
  if (!strcmp(nodeS, "width")){return xml_width;}  
  if (!strcmp(nodeS, "height")){return xml_height;}  
  if (!strcmp(nodeS, "doorsTree")){return xml_doorsTree;}  
  if (!strcmp(nodeS, "doors")){return xml_doors;}  
  if (!strcmp(nodeS, "dist1")){return xml_dist1;}  
  if (!strcmp(nodeS, "dist2")){return xml_dist2;}  
  if (!strcmp(nodeS, "destination")){return xml_destination;}  
  if (!strcmp(nodeS, "stairsTree")){return xml_stairsTree;}  
  if (!strcmp(nodeS, "stairs")){return xml_stairs;}  
  if (!strcmp(nodeS, "bottomDoors")){return xml_bottomDoors;}  
  if (!strcmp(nodeS, "topDoors")){return xml_topDoors;}  
  if (!strcmp(nodeS, "bottomDest")){return xml_bottomDest;}  
  if (!strcmp(nodeS, "topDest")){return xml_topDest;}  
  if (!strcmp(nodeS, "bottom")){return xml_bottom;}  
  if (!strcmp(nodeS, "top")){return xml_top;}  
  if (!strcmp(nodeS, "horizontalVector")){return xml_horizontalVector;}  

  return xml_unknown;
}

/*
  Judges node's type.
 */
mxml_type_t
type_cb(mxml_node_t *node)
{
  const char *type;
  
  type = mxmlElementGetAttr(node, "type");
  
  if (type == NULL)
    {
      type = node->value.element.name;
    }
  
  //change this not-so-nice code later ...
  if (!strcmp(type, "height") || 
      !strcmp(type, "v3x") ||
      !strcmp(type, "v3y") ||
      !strcmp(type, "v3z") ||
      !strcmp(type, "dist1") ||
      !strcmp(type, "dist2") ||
      !strcmp(type, "height") ||
      !strcmp(type, "width") ||
      !strcmp(type, "horizontalVector")
      )
    {
      return (MXML_REAL);
    }
  else if 
    (!strcmp(type, "ID") ||
     !strcmp(type, "topDoors") ||
     !strcmp(type, "bottomDoors") ||
     !strcmp(type, "destination") ||
     !strcmp(type, "bottomDest") ||
     !strcmp(type, "topDest")
     )
    {
      return (MXML_INTEGER);
    }
  else
    {
      return (MXML_TEXT);
    }
  
}

lbXMLmanager::lbXMLmanager(globalContainer *GC): GC(GC)
{
}

bool
lbXMLmanager::saveXML(const char *fileName)
{
  //pointers on structures from globalcontainer
  LObject *FTree = GC -> floorsTree;
  LBStairs *STree = GC -> stairsTree;
  
  
  mxml_node_t *xml;    /* <?xml ... ?> */
  mxml_node_t *data;   /* <data> */
  
  xml = mxmlNewXML("1.0");
  
  data = mxmlNewElement(xml, "budynekA");
  
  {//XML FLOORSTREE
    mxml_node_t *floorsTree = mxmlNewElement(data, "floorsTree");
    
    LBFloor *helpFloor;
    if(FTree->hasChild())
      {
	helpFloor = (LBFloor*) FTree -> child;
      }
    else
      return false; //no floors - no building
    
    while(1)
      {
	XMLFloor(floorsTree, helpFloor);
	
	if( !helpFloor -> isLast())
	  {
	    helpFloor = (LBFloor*)(helpFloor -> next);
	  }
	else
	  {
	    break;
	  }
      }
  }
  
  {//XML STAIRSTREE
    mxml_node_t *stairsTree = mxmlNewElement(data, "stairsTree");
    
    LBStairs *helpStairs = NULL;
    if(STree->hasChild())
      {
	helpStairs = (LBStairs*) STree -> child;
      }
    
    if(helpStairs != NULL)
      while(1)
	{
	  XMLStairs(stairsTree, helpStairs);
	  
	  if( !helpStairs -> isLast())
	    {
	      helpStairs = (LBStairs*)(helpStairs -> next);
	    }
	  else
	    {
	      break;
	    }
	}
  }
  
  FILE *fp;
  
  fp = fopen(fileName,"w");
  mxmlSaveFile(xml, fp, NULL);
  fclose(fp);
  
  return true;
}

void
lbXMLmanager::XMLFloor(mxml_node_t *floorsTree, LBFloor *floor)
{
  mxml_node_t *floorNode = mxmlNewElement(floorsTree, "floor");
  
  mxml_node_t *idNode = mxmlNewElement(floorNode, "ID");
  mxmlNewInteger(idNode, floor->giveID());
  
  mxml_node_t *heightNode = mxmlNewElement(floorNode, "height");
  mxmlNewReal(heightNode, floor->height);
  
  {//FIELDS TREE
    mxml_node_t *fieldsTree = mxmlNewElement(floorNode, "fieldsTree");    
    
    LField *helpField;
    if(floor->hasChild())
      {
	helpField = (LField*)floor -> child;
      }
    else
      return;//no fields
    
    while(1)
      {
	XMLField(fieldsTree, helpField);
	if( !helpField -> isLast())
	  {
	    helpField = (LField*)(helpField -> next);
	  }
	else
	  {
	    break;
	  }
      }
  }
}

void 
lbXMLmanager::XMLField(mxml_node_t *fieldsTree, LField *field)
{
  mxml_node_t *fieldNode = mxmlNewElement(fieldsTree, "field");
  
  mxml_node_t *idNode = mxmlNewElement(fieldNode, "ID");
  mxmlNewInteger(idNode, field->giveID());
  
  //corners of field
  XMLFieldCorners(fieldNode, field);
  
  //walls of field - with windows and doors (passages)
  XMLWalls(fieldNode, field);
}

void 
lbXMLmanager::XMLFieldCorners(mxml_node_t *fieldNode, LField *field)
{
  mxml_node_t *cornersNode = mxmlNewElement(fieldNode, "corners");
  
  for(int a = 0; a < 4; a++)
    {
      XMLVector(cornersNode, field->corners[a]);
    }
}

void 
lbXMLmanager::XMLVector(mxml_node_t *node, LVector vector)
{
  mxml_node_t *vectorNode = mxmlNewElement(node, "vector");
  
  mxml_node_t *coordNodes[3];
  
  coordNodes[0] = mxmlNewElement(vectorNode, "v3x");
  coordNodes[1] = mxmlNewElement(vectorNode, "v3y");
  coordNodes[2] = mxmlNewElement(vectorNode, "v3z");
  
  mxmlNewReal(coordNodes[0], vector.x);
  mxmlNewReal(coordNodes[1], vector.y);
  mxmlNewReal(coordNodes[2], vector.z);
  
  //  std::cout << "float"  << coordNodes[2]->child->value.real << "\n";
}

void lbXMLmanager::XMLWalls(mxml_node_t *fieldNode, LField *field)
{
  mxml_node_t *wallsNode = mxmlNewElement(fieldNode, "walls");
  mxml_node_t *walls[4];
  
  for(int cnt = 0; cnt < 4; cnt++)
    {
      walls[cnt] = mxmlNewElement(wallsNode, "wall");
      
      //      mxml_node_t *idNode = mxmlNewElement(walls[cnt], "ID");
      //      mxmlNewInteger(idNode, 0);
      mxml_node_t *heightNode = mxmlNewElement(walls[cnt], "height");
      mxmlNewReal(heightNode, field->walls[cnt]);
      
      mxml_node_t *windowsTree = mxmlNewElement(walls[cnt], "windowsTree");
      XMLWindows(windowsTree, field, cnt);
      
      mxml_node_t *doorsTree = mxmlNewElement(walls[cnt], "doorsTree");
      XMLDoors(doorsTree, field, cnt);
    }
}

void
lbXMLmanager::XMLWindows(mxml_node_t *windowsNode, LField *field, int wallNo)
{
  LBWindow *helpWindow;
  if(field->windowTree[wallNo] -> hasChild())
    {
      helpWindow = (LBWindow*)field->windowTree[wallNo]->child;
    }
  else
    return;//no windows
  
  while(1)
    {
      mxml_node_t *WNode = mxmlNewElement(windowsNode, "window");
      
      mxml_node_t *WID = mxmlNewElement(WNode, "ID");
      mxmlNewInteger(WID, helpWindow->giveID());
      
      mxml_node_t *WPos = mxmlNewElement(WNode, "position");
      XMLVector(WPos, helpWindow->pos);
      
      mxml_node_t *WDimensions = mxmlNewElement(WNode, "dimensions");
      mxml_node_t *WWidth = mxmlNewElement(WDimensions, "width");
      mxmlNewReal(WWidth, helpWindow->width);
      mxml_node_t *WHeight = mxmlNewElement(WDimensions, "height");
      mxmlNewReal(WHeight, helpWindow->height);
      
      
      if( !helpWindow -> isLast())
	{
	  helpWindow = (LBWindow*)(helpWindow -> next);
	}
      else
	{
	  break;
	}
    }
}

void
lbXMLmanager::XMLDoors(mxml_node_t *doorsNode, LField *field, int wallNo)
{
  lbpassage *helpPassage;
  if(field->passageTree[wallNo] -> hasChild())
    {
      helpPassage = (lbpassage*)field->passageTree[wallNo]->child;
    }
  else
    return;//no passages
  
  while(1)
    {
      mxml_node_t *DNode = mxmlNewElement(doorsNode, "doors");
      
      mxml_node_t *DID = mxmlNewElement(DNode, "ID");
      mxmlNewInteger(DID, helpPassage -> giveID());
      
      mxml_node_t *d1Node = mxmlNewElement(DNode, "dist1");
      mxmlNewReal(d1Node, helpPassage->d1);
      
      mxml_node_t *d2Node = mxmlNewElement(DNode, "dist2");
      mxmlNewReal(d2Node, helpPassage->d2);
      
      mxml_node_t *DHeight = mxmlNewElement(DNode, "height");
      mxmlNewReal(DHeight, helpPassage->doorsHeight);
      
      mxml_node_t *DDest = mxmlNewElement(DNode, "destination");
      mxmlNewInteger(DDest, helpPassage->destObjectID);
      
      if( !helpPassage -> isLast())
	{
	  helpPassage = (lbpassage*)(helpPassage -> next);
	}
      else
	{
	  break;
	}
    }
}

void
lbXMLmanager::XMLStairs(mxml_node_t *stairsTree, LBStairs *stairs)
{
  mxml_node_t *stairsNode = mxmlNewElement(stairsTree, "stairs");
  
  /*first nodes, that are needed to create LBStairs object, when doing XML loading*/
  mxml_node_t *idNode = mxmlNewElement(stairsNode, "ID");
  mxmlNewInteger(idNode, stairs->giveID());
  mxml_node_t *bottomDoorsNode = mxmlNewElement(stairsNode, "bottomDoors");
  mxmlNewInteger(bottomDoorsNode, stairs->bottomDoorsID);
  mxml_node_t *topDoorsNode = mxmlNewElement(stairsNode, "topDoors");
  mxmlNewInteger(topDoorsNode, stairs->topDoorsID);
  
  mxml_node_t *bottomDNode = mxmlNewElement(stairsNode, "bottomDest");
  mxmlNewInteger(bottomDNode, stairs->connBottomID);
  
  mxml_node_t *topDNode = mxmlNewElement(stairsNode, "topDest");
  mxmlNewInteger(topDNode, stairs->connTopID);
  
  mxml_node_t *cornersNode = mxmlNewElement(stairsNode, "corners");
  mxml_node_t *bottom = mxmlNewElement(cornersNode, "bottom");
  XMLVector(bottom, stairs->cornersBottom[0]);
  XMLVector(bottom, stairs->cornersBottom[1]);
  mxml_node_t *top = mxmlNewElement(cornersNode, "top");
  XMLVector(top, stairs->cornersTop[0]);
  XMLVector(top, stairs->cornersTop[1]);
  
  mxml_node_t *horVecNode = mxmlNewElement(stairsNode, "horizontalVector");
  XMLVector(horVecNode, stairs->horizontalVector);



}

XMLResult
lbXMLmanager::loadXML(const char* filename)
{
  FILE *fp;

  fp = fopen(filename, "r");
  xmlTopNode = mxmlLoadFile(NULL, fp, type_cb);


  //pointers on structures from globalcontainer
  //delete default floor
  GC->freeID(((LBFloor*)GC->floorsTree->child)->giveID());
  GC->floorsTree->child->disconnect();
  GC->floorsAmount=0;

  FTree = GC -> floorsTree;
  STree = GC -> stairsTree;
  XMLResult result;
  //walker has building's name
  walker = mxmlWalkNext(xmlTopNode, xmlTopNode, MXML_DESCEND);

  //should be floorsTree
  walkerGo();

  if(compareNodeString(walker->value.opaque) != xml_floorsTree)
    return EFLOORSTREE;//floorsTree not found

  //floors tree found, load floors:
  result = loadFloors();
  if(result != SLOADING) return result;


  //floors loaded, check if there are any stairs
  if(compareNodeString(walker->value.opaque) != xml_stairsTree)
    return ESTAIRSTREE;//stairsTree not found

  result = loadStairs();
  if(result != SLOADING) 
    if(result != SNOSTAIRS) 
      return result;

  /*
    Everything loaded - now it's time to assign primitives to pointers:

    1. passages:
       - destField

    2. stairs:
       - connBottom
       - connTop
   */


  fclose(fp);
  return SLOADING;
}

XMLResult
lbXMLmanager::loadFloors()
{
  //load all floors - return true when no errors occure
  walkerGo();
  XMLResult result;
  //there should be at least one floor - check it
  if(compareNodeString(walker->value.opaque) != xml_floor)  
    return EFLOOR;

  /*
    from now on, do the work untill we meet first node after last node of the last
    floor
  */
  while(compareNodeString(walker->value.opaque) == xml_floor)
    {
      LBFloor *floor;
      int floorID = 10;
      float floorHeight = 10;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_ID)
	return EFLOORID;
      walkerGo();
      floorID = walker->value.integer;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_height)
	return EFLOORHEIGHT;
      walkerGo();
      floorHeight = walker->value.real;
      
      //add new floor
      floor = GC->addFloor(floorID, GC->worldSize - floorHeight);

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_fieldsTree)      
	return EFIELDSTREE;

      result = loadFields(floor);
      if(result!=SLOADING)
	return result;
    }

  return SLOADING;
}

void
lbXMLmanager::walkerGo(int nodesNo)
{
  for(int cnt = 0; cnt < nodesNo; cnt++)
    {
      walker = mxmlWalkNext(walker, xmlTopNode, MXML_DESCEND);  
    }
}

XMLResult
lbXMLmanager::loadFields(LBFloor *floor)
{
  XMLResult result;

  walkerGo();

  if(compareNodeString(walker->value.opaque) != xml_field)  
    return EFIELD;

  while(compareNodeString(walker->value.opaque) == xml_field)
    {
      LField *field;
      int fieldID;
      LVector fieldCorners[4];

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_ID)
	return EFIELDID;  
      
      walkerGo();
      fieldID = walker->value.integer;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_corners)
	return EFIELDCORNERS;  

      //load corners
      for(int cnt = 0; cnt < 4; cnt++)
	{
	  fieldCorners[cnt] = loadVector();
	}
      
      //new field, fill it and then add to *floor
      field = new LField(fieldID, fieldCorners);

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_walls)
	return EWALLS;  

      walkerGo();

      //load walls
      {
	for(int cnt = 0; cnt < 4; cnt++)
	  {
	    if(compareNodeString(walker->value.opaque) != xml_wall)
	      return EWALL;      
	    
	    //	    int wallID;
	    float wallHeight;

	    /*	    walkerGo();
	    if(compareNodeString(walker->value.opaque) != xml_ID)
	      return EWALLID;      
	    walkerGo();
	    wallID = walker->value.integer;*/

	    walkerGo();
	    if(compareNodeString(walker->value.opaque) != xml_height)
	      return EWALLHEIGHT;      
	    walkerGo();
	    wallHeight = walker->value.real;
	    field->walls[cnt] = wallHeight;

	    walkerGo();
	    if(compareNodeString(walker->value.opaque) != xml_windowsTree)
	      return EWINDOWSTREE;      
	    result = loadWindows(field->windowTree[cnt]);
	    if(result != SLOADING)
	      if(result != SNOWINDOW)
		return result;

	    if(compareNodeString(walker->value.opaque) != xml_doorsTree)
	      return EDOORSTREE;      
	    loadDoors(field->passageTree[cnt]);
	  }
      }
      floor -> connect(field);      
    }
  return SLOADING;
}

LVector
lbXMLmanager::loadVector()
{
  float x,y,z;

  //for now, we are assuming that xml file is valid
  walkerGo(3);//-> vector -> x -> real
  x = walker->value.real;
  walkerGo(2);//-> y -> real
  y = walker->value.real;  
  walkerGo(2);//-> z -> real
  z = walker->value.real;
  
  return LVector(x, y, z);
}

XMLResult
lbXMLmanager::loadWindows(LBWindow *windowsRoot)
{
  walkerGo();
  if(compareNodeString(walker->value.opaque) != xml_window)
    return SNOWINDOW;

  while(compareNodeString(walker->value.opaque) == xml_window)  
    {
      int winID;
      LVector winPos;
      float winWidth;
      float winHeight;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_ID)
	return EWINDOWID;      
      walkerGo();
      winID = walker->value.integer;
      
      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_position)
	return EWINDOWPOSITION;      
      winPos = loadVector();

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_dimensions)
	return EWINDOWDIMENSIONS;      
      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_width)
	return EWINDOWWIDTH;      
      walkerGo();
      winWidth = walker->value.real;
      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_height)
	return EWINDOWHEIGHT;      
      walkerGo();
      winHeight = walker->value.real;
      
      LBWindow *newWindow = new LBWindow(winID, winPos, winWidth, winHeight);
      newWindow -> connectTo(windowsRoot);
      walkerGo();
    }

  return SLOADING;
}

XMLResult
lbXMLmanager::loadDoors(lbpassage *passageRoot)
{
  walkerGo();

  if(compareNodeString(walker->value.opaque) != xml_doors)
    return EDOORS;      

  while(compareNodeString(walker->value.opaque) == xml_doors)  
    {
      int doorsID;
      float dist1;
      float dist2;
      float height;
      int destID;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_ID)
	return EDOORSID;      
      walkerGo();
      doorsID = walker->value.integer;      

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_dist1)
	return EDOORSDIST1;      
      walkerGo();
      dist1 = walker->value.real;      

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_dist2)
	return EDOORSDIST2;      
      walkerGo();
      dist2 = walker->value.real;      

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_height)
	return EDOORSHEIGHT;      
      walkerGo();
      height = walker->value.real;      

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_destination)
	return EDOORSDESTINATION;      
      walkerGo();
      destID = walker->value.integer;      

      lbpassage *newPassage = new lbpassage(doorsID, dist1, dist2, destID, height);
      newPassage -> connectTo(passageRoot);

      walkerGo();
    }
  return SLOADING;
}

XMLResult
lbXMLmanager::loadStairs()
{
  walkerGo();

  if(walker == NULL)
    return SNOSTAIRS;

  if(compareNodeString(walker->value.opaque) != xml_stairs)
    return SLOADING; //no stairs or error

  while(compareNodeString(walker->value.opaque) == xml_stairs)  
    {  
      int stairsID;
      int bottomDoorsID, topDoorsID;
      int bottomDest;
      int topDest;
      LVector horizontalVector;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_ID)
	return ESTAIRSID;      
      walkerGo();
      stairsID = walker->value.integer;            

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_bottomDoors)
	return ESTAIRSBOTTOMDOORS;      
      walkerGo();
      bottomDoorsID = walker->value.integer;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_topDoors)
	return ESTAIRSTOPDOORS;      
      walkerGo();
      topDoorsID = walker->value.integer;

      std::cout << "DOOOOORS: " << bottomDoorsID << "  " << topDoorsID<<std::endl;

      LBStairs *loadedStairs = new LBStairs(stairsID, bottomDoorsID, topDoorsID);

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_bottomDest)
	return ESTAIRSBOTTOMDEST;      
      walkerGo();
      bottomDest = walker->value.integer;            

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_topDest)
	return ESTAIRSTOPDEST;      
      walkerGo();
      topDest = walker->value.integer;            

      std::cout << "DEEEST: " << topDest << "  " << bottomDest<<std::endl;

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_corners)
	return ESTAIRSCORNERS;      
      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_bottom)
	return ESTAIRSBOTTOM;      
      for(int cnt = 0; cnt < 2; cnt++){loadedStairs->cornersBottom[cnt] = 
	  loadVector();}

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_top)
	return ESTAIRSTOP;      
      for(int cnt = 0; cnt < 2; cnt++){loadedStairs->cornersTop[cnt] = 
	  loadVector();}

      walkerGo();
      if(compareNodeString(walker->value.opaque) != xml_horizontalVector)
	return ESTAIRSHORIZONTALVECTOR;
      horizontalVector = loadVector();

      loadedStairs->setID(stairsID);
      loadedStairs-> bottomDoorsID = bottomDoorsID;
      loadedStairs-> topDoorsID = topDoorsID;
      loadedStairs->connBottomID = bottomDest;
      loadedStairs->connTopID = topDest;
      loadedStairs->horizontalVector = horizontalVector;
      
      loadedStairs->connectTo(STree);
      
      walkerGo();
      if(walker == NULL)
	return SLOADING;//end of building tree
    }
  return SLOADING;
}
