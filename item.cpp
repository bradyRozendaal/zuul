#include <iostream>
#include <cstring>
#include "item.h"

using namespace std;

// Constructor: creates copies of the item's name and description.
item::item(const char* n, const char* t, int i)
{
  name = new char[strlen(n) + 1];
  strcpy(name, n);

  text = new char[strlen(t) + 1];
  strcpy(text, t);

  id = i;
}

// Destructor: frees dynamically allocated memory.
item::~item()
{
  delete[] name;
  delete[] text;
}

// Returns the item's name.
char* item::getName() const
{
  return name;
}

// Returns the item's description.
char* item::getText() const
{
  return text;
}

// Returns the room ID where the item can be used.
int item::getID() const
{
  return id;
}

// Prints the item's name and description.
void item::print() const
{
  cout << name << ": " << text << "\n";
}
