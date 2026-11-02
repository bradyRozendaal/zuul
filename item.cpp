#include <iostream>
#include "item.h"
using namespace std;

item::item(char* n, char* t, int i)
{
  name = n;
  text = t;
  id = i;
}
item::~item()
{
  delete[] name;
  delete[] text;
}
char* item::getName() const
{
  return name;
}
char* item::getText() const
{
  return text;
}
int item::getID() const
{
  return id;
}
void item::print() const
{
  cout << text;
}
