#include "lbxmlmanager.h"

lbXMLmanager::lbXMLmanager(globalContainer *GC): GC(GC)
{
}

void
lbXMLmanager::saveXML()
{
  mxml_node_t *xml;    /* <?xml ... ?> */
  mxml_node_t *data;   /* <data> */
  mxml_node_t *node;   /* <node> */
  mxml_node_t *group;  /* <group> */
  
  xml = mxmlNewXML("1.0");
  
  data = mxmlNewElement(xml, "budynekARektorat");
  
  node = mxmlNewElement(data, "node");
  mxmlNewText(node, 0, "val1");
  node = mxmlNewElement(data, "node");
  mxmlNewReal(node, 0.34f);
  node = mxmlNewElement(data, "node");
  mxmlNewText(node, 0, "val3");
  
  group = mxmlNewElement(data, "group");
  
  node = mxmlNewElement(group, "height");
  mxmlNewText(node, 0, "0.45f");

  node = mxmlNewElement(group, "node");
  mxmlNewText(node, 0, "val5");

  node = mxmlNewElement(group, "node");
  mxmlNewText(node, 0, "val6");
  
  node = mxmlNewElement(data, "node");
  mxmlNewText(node, 0, "val7");
  node = mxmlNewElement(data, "node");
  mxmlNewText(node, 0, "val8");

  FILE *fp;

  fp = fopen("budynekA.xml","w");
  mxmlSaveFile(xml, fp, NULL);
  fclose(fp);
}

void
lbXMLmanager::loadXML()
{

}
