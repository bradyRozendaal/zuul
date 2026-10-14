#include <iostream>
#include <cstring>
#include "items.h"
#include <vector>
using namespace std;

class Room {
 protected:
  char* roomText;
  vector<item*> roomItems;
 public:
  Room(char* t, item* rI);
  ~Room();
  item* getItems() const;
};
