#include <iostream>
#include <cstring>
#include "items.h"
#include <vector>
using namespace std;

Room::Room(char* t, item* rI){
  roomText = new char[strlen(t)+1];
  strcpy(roomText, t);

  roomItems = rI;
}

Room:~Room(){
  
}

