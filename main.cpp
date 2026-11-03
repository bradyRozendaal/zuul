#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>

#include "room.h"
#include "item.h"

using namespace std;

/*
  Project: Zuul
  Made by: Brady Rozendaal
  Theme: Abandoned Research Facility

  The player must explore 15 rooms, collect five items,
  restore power, activate the facility's systems, and escape.
*/

// Initializes all 15 rooms and places the five items.
void initRooms(vector<room*>& rooms)
{
  // Names of all rooms.
  const char* roomNames[15] = {
    "Entrance Lobby",
    "Reception",
    "Security Office",
    "Medical Bay",
    "Storage Room",
    "Cafeteria",
    "Server Room",
    "Research Laboratory",
    "Containment Room",
    "Offices",
    "Maintenance Room",
    "Generator Room",
    "Reactor Control",
    "Elevator",
    "Emergency Exit"
  };

  // Descriptions of all rooms.
  const char* roomText[15] = {
    "The main entrance is sealed behind you.",
    "An abandoned reception desk sits beneath flickering lights.",
    "Security monitors line the walls. A terminal requires a keycard.",
    "Dusty hospital beds and medical equipment fill the room.",
    "Shelves of tools and spare parts surround you.",
    "Cold trays remain on forgotten cafeteria tables.",
    "Rows of silent servers wait for a backup battery.",
    "Research notes cover the desks. The experiments have been abandoned.",
    "A reinforced observation window looks into an empty chamber.",
    "Scattered paperwork covers the abandoned offices.",
    "Tool cabinets and workbenches fill the room.",
    "The generator is offline and its access panel is closed.",
    "A dark control console overlooks the reactor.",
    "The elevator is waiting, but its control panel requires authorization.",
    "A heavy emergency door leads outside."
  };

  // Each vector stores the items initially found in one room.
  vector<item*> roomItems[15];

  // Create the five items and assign their usable room IDs.

  // Keycard: found in Reception, used in Security Office (room 2).
  roomItems[1].push_back(new item("Keycard","A staff keycard.",2));

  // Screwdriver: found in Storage, used in Generator Room (room 11).
  roomItems[4].push_back(new item("Screwdriver","A screwdriver for opening maintenance panels.",11));

  // Fuse: found in Maintenance, used in Generator Room (room 11).
  roomItems[10].push_back(new item("Fuse","A replacement fuse for the generator.",11));

  // Battery: found in Research Laboratory, used in Server Room (room 6).
  roomItems[7].push_back(new item("Battery","A backup battery for the server terminal.",6));

  // Access Code: found in Offices, used in Elevator (room 13).
  roomItems[9].push_back(new item("Access Code","A handwritten elevator authorization code.",13));

  // Create all 15 rooms.
  for (int i = 0; i < 15; i++)
  {
    rooms.push_back(new room(roomText[i], roomNames[i], roomItems[i]));
  }
}

// Displays the valid directions from the current position.
void getValidMoves(int** layout, int pos[2])
{
  cout << "\n";

  // East.
  if (pos[0] < 4)
    cout << "east ";

  // West.
  if (pos[0] > 0)
    cout << "west ";

  // North.
  if (pos[1] < 2)
    cout << "north ";

  // South.
  if (pos[1] > 0)
    cout << "south ";

  cout << "\n";
}

// Checks whether the target position is inside the map.
bool moveIsValid(int** layout, int targetPos[2])
{
  if (targetPos[0] < 0 || targetPos[0] >= 5 ||
      targetPos[1] < 0 || targetPos[1] >= 3)
  {
    return false;
  }

  return true;
}

// Prints the current game state.
void printState(vector<room*>& rooms, int** layout, int pos[2])
{
  // Find the current room using the map coordinates.
  cout << "\n----------------------------------------------";
  int roomID = layout[pos[0]][pos[1]];

  rooms[roomID]->print();

  cout << "\nYou can travel in the following directions:";
  getValidMoves(layout, pos);
}

// Prints all items in a vector.
void printItems(vector<item*> items)
{
  if (items.empty())
  {
    cout << "None\n";
  }
  else
  {
    for (item* i : items)
      i->print();
  }
}

// Finds an item in a vector using its name.
item* findItem(vector<item*> items, char in[])
{
  for (item* i : items)
  {
    if (strcmp(i->getName(), in) == 0)
      return i;
  }

  return NULL;
}

// Moves the player in the chosen direction.
void move(int (&pos)[2], int** layout)
{
  int targetPos[2] = {pos[0], pos[1]};
  char in[20];

  cout << "What direction would you like to move? ";
  cin.getline(in, 20);

  // Convert input to lowercase.
  for (int i = 0; in[i] != '\0'; i++)
    in[i] = tolower(in[i]);

  // Determine the target position.
  if (strcmp(in, "north") == 0)
    targetPos[1]++;

  else if (strcmp(in, "south") == 0)
    targetPos[1]--;

  else if (strcmp(in, "east") == 0)
    targetPos[0]++;

  else if (strcmp(in, "west") == 0)
    targetPos[0]--;

  else
  {
    cout << "Invalid direction.\n";
    return;
  }

  // Move if the target position is valid.
  if (moveIsValid(layout, targetPos))
  {
    pos[0] = targetPos[0];
    pos[1] = targetPos[1];
  }
  else
  {
    cout << "You cannot move in that direction.\n";
  }
}

// Allows the player to pick up an item.
void pickupItem(room* currentRoom, vector<item*>& inventory)
{
  vector<item*> roomItems = currentRoom->getItems();
  char in[50];

  cout << "Which item would you like to pick up?\n";
  printItems(roomItems);

  cin.getline(in, 50);

  item* chosen = findItem(roomItems, in);

  if (chosen != NULL)
  {
    inventory.push_back(chosen);
    currentRoom->removeItem(chosen);

    cout << "You picked up " << chosen->getName() << ".\n";
  }
  else
  {
    cout << "That item is not in this room.\n";
  }
}

// Allows the player to drop an item.
void dropItem(room* currentRoom, vector<item*>& inventory)
{
  char in[50];

  cout << "Which item would you like to drop?\n";
  printItems(inventory);

  cin.getline(in, 50);

  item* chosen = findItem(inventory, in);

  if (chosen != NULL)
  {
    currentRoom->addItem(chosen);

    // Remove the item from inventory without deleting it.
    for (int j = 0; j < inventory.size(); j++)
    {
      if (inventory[j] == chosen)
      {
        inventory.erase(inventory.begin() + j);
        break;
      }
    }

    cout << "You dropped " << chosen->getName() << ".\n";
  }
  else
  {
    cout << "You are not carrying that item.\n";
  }
}

// Allows the player to use items in their intended rooms.
void useItem(vector<item*>& inventory, int currentRoomNum, bool& panelOpened, bool& powerRestored, bool& serverOnline, bool& securityAccess, bool& elevatorUnlocked)
{
  char in[50];

  cout << "Which item would you like to use?\n";
  printItems(inventory);

  cin.getline(in, 50);

  item* chosen = findItem(inventory, in);

  if (chosen == NULL)
  {
    cout << "You are not carrying that item.\n";
    return;
  }

  // Check whether the item can be used in this room.
  if (chosen->getID() != currentRoomNum)
  {
    cout << "There is nowhere to use that item here.\n";
    return;
  }

  bool used = false;

  // Screwdriver opens the generator access panel.
  if (strcmp(chosen->getName(), "Screwdriver") == 0)
  {
    if (!panelOpened)
    {
      panelOpened = true;
      used = true;

      cout << "You open the generator access panel.\n";
    }
    else
      cout << "The panel is already open.\n";
  }

  // Fuse restores power after the panel has been opened.
  else if (strcmp(chosen->getName(), "Fuse") == 0)
  {
    if (panelOpened)
    {
      powerRestored = true;
      used = true;

      cout << "You install the fuse. Power is restored!\n";
    }
    else
      cout << "You need to open the generator panel first.\n";
  }

  // Battery activates the server terminal.
  else if (strcmp(chosen->getName(), "Battery") == 0)
  {
    if (!serverOnline)
    {
      serverOnline = true;
      used = true;

      cout << "The server terminal powers on.\n";
    }
    else
      cout << "The server is already running.\n";
  }

  // Keycard activates security access.
  else if (strcmp(chosen->getName(), "Keycard") == 0)
  {
    if (!securityAccess)
    {
      securityAccess = true;
      used = true;

      cout << "The security terminal accepts your keycard.\n";
    }
    else
      cout << "Security access is already active.\n";
  }

  // Access code unlocks the elevator.
  else if (strcmp(chosen->getName(), "Access Code") == 0)
  {
    if (powerRestored && serverOnline && securityAccess)
    {
      elevatorUnlocked = true;
      used = true;

      cout << "The access code is accepted. The elevator unlocks!\n";
    }
    else
    {
      cout << "The elevator requires power, an active server, "
           << "and security access.\n";
    }
  }

  // Remove and delete an item after successful use.
  if (used)
  {
    for (int j = 0; j < inventory.size(); j++)
    {
      if (inventory[j] == chosen)
      {
        inventory.erase(inventory.begin() + j);
        break;
      }
    }

    delete chosen;
  }
}

// Frees all dynamically allocated memory.
void cleanup(vector<room*>& rooms, vector<item*>& inventory,
             int** layout)
{
  // Each room deletes the items still inside it.
  for (room* r : rooms)
    delete r;

  // Delete items still carried by the player.
  for (item* i : inventory)
    delete i;

  // Delete the map.
  for (int i = 0; i < 5; i++)
    delete[] layout[i];

  delete[] layout;
}

// Main game function.
int main()
{
  vector<item*> items;  // Player inventory.
  vector<room*> rooms;  // All rooms.

  // Initialize all rooms and items.
  initRooms(rooms);

  // Create a 5 by 3 map.
  int** layout = new int*[5];

  for (int i = 0; i < 5; i++)
    layout[i] = new int[3];

  // Assign room IDs to map coordinates.
  for (int x = 0; x < 5; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      layout[x][y] = x * 3 + y;
    }
  }

  // Player starts in the entrance lobby.
  int pos[2] = {0, 0};

  // Track puzzle progress.
  bool play = true;
  bool panelOpened = false;
  bool powerRestored = false;
  bool serverOnline = false;
  bool securityAccess = false;
  bool elevatorUnlocked = false;

  cout << "====================================\n";
  cout << "   ABANDONED RESEARCH FACILITY\n";
  cout << "====================================\n";
  cout << "You wake up inside an abandoned research facility.\n";
  cout << "Explore the facility and find a way to escape.\n";

  // Main game loop.
  while (play)
  {
    // Display the current room.
    printState(rooms, layout, pos);

    // Display inventory.
    cout << "\nYou have:\n";
    printItems(items);

    int currentRoomNum = layout[pos[0]][pos[1]];
    room* currentRoom = rooms[currentRoomNum];

    // Check whether the player has reached the exit.
    if (currentRoomNum == 14)
    {
      if (elevatorUnlocked)
      {
        cout << "\nYou make it outside!\n";
        cout << "You escaped the research facility!\n";
        break;
      }
      else
      {
        cout << "\nThe emergency exit is sealed.\n";
        cout << "You must unlock the elevator first.\n";
      }
    }

    char in[20];

    cout << "\nWhat would you like to do?\n";
    cout << "Commands: move, pickup, use, drop, quit\n";

    cin.getline(in, 20);

    // Convert command to lowercase.
    for (int i = 0; in[i] != '\0'; i++)
      in[i] = tolower(in[i]);

    // Execute the chosen command.
    if (strcmp(in, "move") == 0)
    {
      move(pos, layout);
    }
    else if (strcmp(in, "pickup") == 0)
    {
      pickupItem(currentRoom, items);
    }
    else if (strcmp(in, "use") == 0)
    {
      useItem(items, currentRoomNum, panelOpened, powerRestored, serverOnline, securityAccess, elevatorUnlocked);
    }
    else if (strcmp(in, "drop") == 0)
    {
      dropItem(currentRoom, items);
    }
    else if (strcmp(in, "quit") == 0)
    {
      cout << "Quitting program...\n";
      play = false;
    }
    else
    {
      cout << "Invalid command.\n";
    }
  }

  // Free allocated memory before ending the program.
  cleanup(rooms, items, layout);

  return 0;
}
