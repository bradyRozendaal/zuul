#include <iostream>
#include <cstring>
#include "item.h"
#include "room.h"
#include <vector>
using namespace std;

room::room(char* t, char* n, vector<item*> rI){
  char* name = new char[strlen(n)+1];
  strcpy(name, n);
  char* roomText = new char[strlen(t)+1];
  strcpy(roomText, t);

  vector<item*> roomItems = rI;
}

room::~room(){
  delete[] name;
  delete[] roomText;
  for (item* i : roomItems)
    {
      delete i;
    }
}
void room::removeItem(item* i)
{
  char* itemName = i->getName();
  for (item* it : roomItems)
    {
      if (it->getName() == itemName)
	{
	  roomItems.erase(it);
	}
    }
}
void room::addItem(item* i)
{
  roomItems.push_back(i);
}
vector<item*> room::getItems()
{
  return roomItems;
}
void room::print()
{
    cout << "You are in the: " << name << "\n"
	 << roomText << "\n\n" 
	 << "There are the below items in this room: ";
  for (item* i : roomItems)
    {
      i->print();
    }
}
