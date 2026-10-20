#include <iostream>
#include <cstring>
#include "item.h"
#include "room.h"
#include <vector>
using namespace std;

room::room(char* t, char* n, vector<item*> rI){
  name = new char[strlen(n)+1];
  strcpy(name, n);
  roomText = new char[strlen(t)+1];
  strcpy(roomText, t);

  roomItems = rI;
}

room::~room(){
  Delete name[];
  Delete roomText[];
  Delete roomItems[];
}
vector<item*> room::getItems()
{
  return roomItems;
}
void room::print() const
{
    cout << "You are in the: " << name << "\n"
	 << roomText << "\n\n" 
	 << "There are the below items in this room: ";
  for (item* i : roomItems)
    {
      i->print();
    }
}
