#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
using namespace std;

/**
   A warrior class that tracks warrior name and stats (strength, loyalty, morale, allegience, ships, dragonglass)
 */

class Warrior
{
public:
   Warrior(); // default constructor
   Warrior(string warriorName, int s, int l, int m, string f, string sail, string glass, bool alive); // paramterized constructor
   string getName();
   int getStrength();
   int getLoyalty();
   int getMorale();
   int getRow();
   int getColumn();
   bool getFree();
   bool getShip();
   bool getDragonglass();
   bool isAlive();
   void setName(string warriorName);
   void setStrength(int s);
   void setLoyalty(int l);
   void setMorale(int m);
   void setFree(string f);
   void setShip(string sail);
   void setDragonglass(string glass);
   void setRow(int r);
   void setColumn(int c);
   void setAlive(bool d);

private:
   string name;
   int strength;
   int loyalty;
   int morale;
   bool freedom;
   bool ship;
   bool dragonglass;
   bool alive;
   int row;
   int column;
   const static int maxStrength = 200;
   const static int maxLoyaltyMorale = 100;
   const static int maxRow = 25;
   const static int maxColumn = 16;
};

#endif