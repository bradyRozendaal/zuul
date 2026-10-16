#include <iostream>
#include <cstring>
#include "item.h"
#include "room.h"
#include <vector>
using namespace std;

room::room(char* t, vector<item*> rI){
  roomText = new char[strlen(t)+1];
  strcpy(roomText, t);

  roomItems = rI;
}

room::~room(){
  Delete roomText[];
  Delete roomItems[];
}
vector<item*> room::getItems()
{
  return roomItems;
}
void room::print() const
{
  cout << roomText << "\n\nThere are the below items in this room: ";
  for (item* i : roomItems)
    {
      i->print();
    }
}
