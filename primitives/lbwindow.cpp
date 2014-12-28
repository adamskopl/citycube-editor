#include "lbwindow.h"

LBWindow::LBWindow(int ID, LVector pos, float w, float h): pos(pos), width(w), height(h)
{
  setID(ID);
}
