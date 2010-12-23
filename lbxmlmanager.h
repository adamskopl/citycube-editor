#ifndef LBXMLMANAGER_H
#define LBXMLMANAGER_H

#include <mxml.h>
#include "globalcontainer.h"

class lbXMLmanager
{
public:
    lbXMLmanager(globalContainer *GC);
    

    void saveXML();
    void loadXML();

private:
    globalContainer *GC;
};

#endif // LBXMLMANAGER_H
