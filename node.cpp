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
#include "node.h"


bool 
LNode::hasParent()
{ 
  if(parent)
    return true;
  else
    return false;
}

bool
LNode::hasChild()
{ 
  if(child)
    return true;
  else
    return false;
}

bool 
LNode::isFirst()
{
  if (parent)
    return (parent->child == this);
  else
    return false;
}
  
  
bool 
LNode::isLast()
{
  if (parent)
    return (parent->child->prev == this);
  else
    return false;
}


void LNode::connectTo(LNode* newParent)
{
  if (parent)
    disconnect();
  
  parent = newParent;
  
  if (parent->child)
    {
      prev = parent->child->prev;
      next = parent->child;
      parent->child->prev->next = this;
      parent->child->prev = this;
    }
  else
    {
      parent->child = this;	
    }
}

void LNode::connect(LNode* newChild)
{
  if (newChild->hasParent())
    newChild->disconnect();
  
  newChild->parent = this;
  
  if (child)
    {
      newChild->prev = child->prev;
      newChild->next = child;
      child->prev->next = newChild;
      child->prev = newChild;
    }
  else
    child = newChild;
}

void LNode::disconnect()
{
  if (parent && parent->child == this)
    {
      if (next != this)
	parent->child = next;
      else
	parent->child = NULL;	
    }
  
  prev->next = next;
  next->prev = prev;
  
  prev = this;
  next = this;
}

LNode::LNode()
{
  parent = NULL;
  child = NULL;
  prev = this;  
  next = this;
}

LNode::LNode(LNode* LNode)
{

  parent = NULL;
  child = NULL;
  prev = this;
  next = this;
  connectTo(LNode);
}

