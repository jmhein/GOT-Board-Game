#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Warrior_v3.h"
#include "Hero_v3.h"
using namespace std;

/**
   A tile class that tracks tile type, letter on game board, name, money, army size, point value, if it has dragon glass, and owner
 */

class Tile
{
public:
   Tile(); // default constructor
   Tile(char l, string tileName, int m, int a, int p); // parameterized constructor
   string getName(); // returns tile name
   char getLetter(); // returns letter on game board
   int getMoney();
   int getArmySize();
   int getPoints();
   bool getDragonglass(); // returns true if tile has dragonglass
   string getOwner();
   void setLetter(string l); // likely to be used to change from land to dragonglass and vice versa
   void setName(string tileName);
   void setMoney(int m);
   void setArmySize(int a);
   void setPoints(int p);
   void setDragonglass(string glass);
   int setOwner(Hero h1, int index);
   
   //////// MAY NEED TO ADD ADDITIONAL FUNCTIONS WHILE WORKING THROUGH GAME MECHANICS ///////////////////////
   
private:
   char letter;
   string name;
   int money;
   int army_size;
   int points;
   bool dragonglass;
   Hero owner;
   int hero0;
   int hero1;
   int hero2;
   int hero3;
   int hero4;
   int hero5;
   int hero6;
};

#endif
