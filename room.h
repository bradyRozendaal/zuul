#ifndef ROOM
#define ROOM

#include <vector>
#include "item.h"

using namespace std;

// Represents a room in the research facility.
class room {
 protected:
  char* roomText;             // Description of the room.
  char* name;                 // Name of the room.
  vector<item*> roomItems;    // Items currently in the room.

 public:
  // Constructor and destructor.
  room(const char* t, const char* n, vector<item*> rI);
  ~room();

  // Room item management.
  void removeItem(item* i);
  void addItem(item* i);
  vector<item*> getItems();

  // Prints the room's information.
  void print();
};

#endif
