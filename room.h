#include <iostream>
#include <cstring>
#include "item.h"
#include <vector>
using namespace std;

class room {
 protected:
  char* roomText;
  vector<item*> roomItems;
 public:
  room(char* t, vector<item*> rI);
  ~room();
  vector<item*> getItems();
  void print() const;
};
