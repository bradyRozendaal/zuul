#include <iostream>
#include <cstring>
#include "item.h"
#include <vector>
using namespace std;

class room {
 protected:
  char* roomText;
  char* name;
  vector<item*> roomItems;
 public:
  room(char* t, char* n, vector<item*> rI);
  ~room();
  void removeItem(item* i);
  void addItem(item* i);
  vector<item*> getItems();
  void print();
};
