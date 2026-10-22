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
  char* getName() const;
  char* getText() const;
  int getID() const;
  void print() const;
}
