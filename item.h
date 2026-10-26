#ifndef ITEM
#define ITEM
#include <iostream>

using namespace std;

class item {
 protected:
  char* name;
  char* text;
  int id;
 public:
  item(char* n, char* t, int i);
  ~item();
  char* getName();
  char* getText();
  int getID();
  void print();
};
  
#endif
