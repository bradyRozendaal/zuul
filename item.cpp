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
  delete name[];
  delete text[];
}
char* item::getName()
{
  return name;
}
char* item::getText()
{
  return text;
}
int item::getID()
{
  return id;
}
void item::print
{
  cout << text;
}
