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
  char roomText[][] = {"", ""};
  vector<vector<item*>> roomItems;
  for (int i = 0, i < size(roomText); i++)
    {
      rooms.push_back(new room(roomText[i], roomItems[i]));
    }
}

void printState(vector<room*> rooms, int** layout, int pos[2])
{
  cout << rooms[layout[pos[0]][pos[1]]]->print();
  cout << "\nYou can travel in the following directions: ";
  if (layout[pos[0]+1][pos[1]] != 0){
    cout << "East\n"
  }
  if (layout[pos[0]-1][pos[1]] != 0){
    cout << "West\n"
  }
  if (layout[pos[0]][pos[1]+1] != 0){
    cout << "North\n"
  }
  if (layout[pos[0]][pos[1]-1] != 0){
    cout << "South\n"
  }
}

int Main()
{
  vector<item*> items;//items in your inventory
  vector<room*> rooms;//the vector of rooms
  initRooms();
  int size = 10;//total size of the map
  int** layout = new int*[size]{};
  for (int i = 0; i < size; i++){
    layout[i] = new int[size]{};
  }
  int pos[2] = {0,0};
  //player should be able to view invetory, move, pickup, and quit
  
}
