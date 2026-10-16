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
  void print() const;
}
