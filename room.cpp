#include <iostream>
#include <cstring>
#include "item.h"
#include "room.h"

using namespace std;

// Constructor: initializes the room and copies its text and name.
room::room(const char* t, const char* n, vector<item*> rI)
{
  roomText = new char[strlen(t) + 1];
  strcpy(roomText, t);

  name = new char[strlen(n) + 1];
  strcpy(name, n);

  roomItems = rI;
}

// Destructor: frees the room's memory and remaining items.
room::~room()
{
  delete[] roomText;
  delete[] name;

  // Delete items that are still inside this room.
  for (item* i : roomItems)
    delete i;
}

// Removes an item from the room without deleting it.
// This allows the item to be transferred into the inventory.
void room::removeItem(item* i)
{
  for (int j = 0; j < roomItems.size(); j++)
  {
    if (roomItems[j] == i)
    {
      roomItems.erase(roomItems.begin() + j);
      return;
    }
  }
}

// Adds an item to the room.
void room::addItem(item* i)
{
  roomItems.push_back(i);
}

// Returns the room's item vector.
vector<item*> room::getItems()
{
  return roomItems;
}

// Prints the room's name, description, and items.
void room::print()
{
  cout << "\nYou are in: " << name << "\n";
  cout << roomText << "\n";

  cout << "\nItems in this room:\n";

  if (roomItems.empty())
    cout << "None\n";
  else
  {
    for (item* i : roomItems)
      i->print();
  }
}
