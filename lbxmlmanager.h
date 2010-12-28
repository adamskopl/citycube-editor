#ifndef LBXMLMANAGER_H
#define LBXMLMANAGER_H

#include <mxml.h>
#include "globalcontainer.h"

/*
  E(...) means error in (...)
  S(...) means succes in (...)

  such error handling is useful when using gdb
 */
enum XMLResult
  {
    SLOADING,
    EFLOORSTREE, //no floorsTree node
    ESTAIRSTREE, //no stairsTree node
    EFLOOR,      //no floor node
    EFLOORID,    //no floor's ID node
    EFLOORHEIGHT, //no floor's height
    EFIELDSTREE, //no fieldstree's node
    EFIELD,      //no field's node
    EFIELDID,    //no field id's node
    EFIELDCORNERS, //no field corners node
    EWALLS,   //no walls node
    EWALL,    //no wall's node
    //    EWALLID,      
    EWALLHEIGHT,
    EWINDOWSTREE,
    EDOORSTREE,
    EWINDOW,
    SNOWINDOW,
    EWINDOWID,
    EWINDOWPOSITION,
    EWINDOWDIMENSIONS,
    EWINDOWWIDTH,
    EWINDOWHEIGHT,
    EDOORS,
    EDOORSID,
    EDOORSDIST1,
    EDOORSDIST2,
    EDOORSHEIGHT,
    EDOORSDESTINATION,
    ESTAIRS,
    ESTAIRSID,
    ESTAIRSBOTTOMDEST,
    ESTAIRSTOPDEST,
    ESTAIRSCORNERS,
    ESTAIRSBOTTOM,
    ESTAIRSTOP,
    ESTAIRSHORIZONTALVECTOR,
    SNOSTAIRS

  };

class lbXMLmanager
{
public:
    lbXMLmanager(globalContainer *GC);
    

    bool saveXML(const char *);
    XMLResult loadXML(const char *);

private:
    globalContainer *GC;

    void XMLFloor(mxml_node_t *floorsTree, LBFloor *floor);
    void XMLField(mxml_node_t *fieldsTree, LField *field);
    void XMLFieldCorners(mxml_node_t *fieldNode, LField *field);
    void XMLVector(mxml_node_t *node, LVector vector);
    void XMLWalls(mxml_node_t *fieldNode, LField *field);
    void XMLWindows(mxml_node_t *windowsNode, LField *field, int wallNo);
    void XMLDoors(mxml_node_t *doorsNode, LField *field, int wallNo);

    void XMLStairs(mxml_node_t *stairsTree, LBStairs *stairs);

    // loading part:

    //top node - need to be set at beginning of loading!
    mxml_node_t *xmlTopNode;
    //node walking through the building's tree
    mxml_node_t *walker;
    //take next node
    void walkerGo(int nodesNo = 1);

    /*
      Loading functions  first node, that does node belong to the loaded part.
      E.g floor is loaded, walker is set to first node after last floor's node, so 
      loading can continue.

      Return success or failure.
    */
    LObject *FTree;
    LBStairs *STree;

    XMLResult loadFloors();
    //load fields and add them to the floor
    XMLResult loadFields(LBFloor *floor);
    LVector loadVector();
    XMLResult loadWindows(LBWindow *windowsRoot);
    XMLResult loadDoors(lbpassage *passageRoot);
    
    XMLResult loadStairs();
};

#endif // LBXMLMANAGER_H
