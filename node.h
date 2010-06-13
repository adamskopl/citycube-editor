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

#ifndef __NODE_H
#define __NODE_H

#include <stdio.h>

class LNode{
 public:

  LNode *parent;
  LNode *child;
  LNode *prev;
  LNode *next;

  bool hasParent();
  bool hasChild();

  bool isFirst();
  bool isLast();

  void connect(LNode*);
  void connectTo(LNode*);

  void disconnect();

  LNode();
  LNode(LNode*);
};

#endif
