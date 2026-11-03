#ifndef ITEM
#define ITEM

// Represents an item that can be collected and used by the player.
class item {
 protected:
  char* name;  // Name of the item.
  char* text;  // Description of the item.
  int id;      // Room ID where the item can be used.

 public:
  // Constructor and destructor.
  item(const char* n, const char* t, int i);
  ~item();

  // Accessor functions.
  char* getName() const;
  char* getText() const;
  int getID() const;

  // Prints the item description.
  void print() const;
};

#endif
