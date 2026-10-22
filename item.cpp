#include <iostream>
#include "item.h"
using namespace std;

item::item(char* n, char* t, int id);
{
  name = n;
  text = t;
  id = i;
}
item::~item()
{
  Delete name[];
  Delete text[];
}
char* getName() const
{
  return name;
}
char* getText() const
{
  return text;
}
int getID() const
{
  return id;
}
void item::print const
{
  cout << text;
}
