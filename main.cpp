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
  Date:
*/

void initRooms(vector<room*>& rooms)//initializes all rooms
{
  char roomText[][15] = {"", ""};
  vector<vector<item*>> roomItems(5);
  for (int i = 0; i < size(roomText); i++)
    {
      rooms.push_back(new room(roomText[i], roomItems[i]));
    }
}
void getValidMoves(int** layout, int pos[2])
{
  if (layout[pos[0]+1][pos[1]] != 0){
    cout << "east\n";
  }
  if (layout[pos[0]-1][pos[1]] != 0){
    cout << "west\n";
  }
  if (layout[pos[0]][pos[1]+1] != 0){
    cout << "north\n";
  }
  if (layout[pos[0]][pos[1]-1] != 0){
    cout << "south\n";
  }
}

bool moveIsValid(int** layout, int targetPos[2])
{
  if (targetPos[0] < 0 ||targetPos[1] < 0)
    {
      return false;
    } 
  if (layout[targetPos[0]][targetPos[1] != 0])
    {
      return true;
    }
    return false;
}
  
void printState(vector<room*> rooms, int** layout, int pos[2])
{
  rooms[layout[pos[0]][pos[1]]]->print();//prints the text for the current room you are in
  cout << "\nYou can travel in the following directions: ";
  getValidMoves(layout, pos);
}
void printItems(vector<item*> items)
  {
    for (item* i : items)
      {
	i->print();
      }
  }

void move(int (&pos)[2], int** layout)
{
  int targetPos[2];
  cout << "What direction would you like to move?";
  getValidMoves(layout, pos);
  char in[5];
  cin.getline(in, 5);
  if (in[0] == 'n')
    {
      targetPos[0] = pos[0];
      targetPos[1] = pos[1] + 1;
    }
  else if (in[0] == 'e')
    {
      targetPos[0] = pos[0] + 1;
      targetPos[1] = pos[1];
    }
  else if (in[0] == 's')
    {
      targetPos[0] = pos[0];
      targetPos[1] = pos[1] - 1;
    }
  else if (in[0] == 'w')
    {
      targetPos[0] = pos[0] - 1;
      targetPos[1] = pos[1];
    }
  if (moveIsValid(layout, targetPos))
    {
      pos[0] = targetPos[0];
      pos[1] = targetPos[1];
    }
}

int Main()
{
  vector<item*> items;//items in your inventory
  vector<room*> rooms;//the vector of rooms
  //initRooms();
  int size = 10;//total size of the map
  int** layout = new int*[size]{};//double pointer of layout
  for (int i = 0; i < size; i++){//iterates through layout to initialize the memory with 0s
    layout[i] = new int[size]{};
  }
  int pos[2] = {0,0};
  //player should be able to view invetory, move, pickup, and quit
  bool play = true;
  while (play)
    {
      printState(rooms, layout, pos);//prints the current game state
      cout << "You have: ";
      printItems(items);//prints your inventory
      room* currentRoom = rooms[layout[pos[0]][pos[1]]];//room you are in
      int currentRoomNum = layout[pos[0]][pos[1]];//int ID for the room you are in
      vector<item*> rI = currentRoom->getItems();//items in the room you are in
      char in[5];
      cout << "What would you like to do? (move, pickup, use, drop, quit)\n";
      cin.getline(in, 5);
      if (in[0] == 'm')
	{
	  move(pos, layout);
	}
      else if (in[0] == 'p')
	{
	  cout << "What item would you like to pickup?: \n";
	  printItems(rI);
	  char* in;
	  cin.getline(in, 5);
	  for (item* i : rI)
	    {
	      if (i->getName() == in)
		{
		  items.push_back(i);
		  currentRoom->removeItem(i);
		}
	    }
	}
      else if (in[0] == 'd')
	{
	  cout << "What item would you like to drop?: \n";
	  printItems(items);
	  char* in;
	  cin.getline(in, 20);
	  for (item* i : items)
	    {
	      if (i->getName() == in)
		{
		  currentRoom->addItem(i);
		  items.erase(remove(items.begin(),items.end(), i), items.end());
		}
	    }
	}
      else if (in[0] == 'u')//use an item
	{
	  cout << "Which item would you like to use?";
	  printItems(items);
	  char* in;
	  cin.getline(in, 20);
	  for (item* i : items)
	    {
	      if (i->getName() == in)
		{
		  if (i->getID() == currentRoomNum)
		    {
		      //repeated if list for what its going to do
		    }
		}
	    }
	  }
      else if (in[0] == 'q')
	{
	  cout << "quiting program...";
	  return 0;
	}
    }
}
