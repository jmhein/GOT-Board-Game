#ifndef HERO_H
#define HERO_H

#include <iostream>
#include "Warrior_v3.h"
using namespace std;

/**
   A hero class that tracks hero name, stats (money, influence, army, warriors, ships), and start position
 */

class Hero
{
public:
   Hero(); // default constructor
   Hero(string heroName, int m, int i, int a, Warrior w1, Warrior w2, Warrior w3, Warrior w4, int r, int c, string sail, bool user, bool d); // parameterized constructor
   string getName(); // returns hero name
   int getMoney(); // returns hero money
   int getInfluence(); // returns hero influence
   int getArmySize(); // returns hero army size
   int getRow();
   int getColumn();
   int getWarriorMorale(int z);
   int getWarriorLoyalty(int x);
   int getWarriorStrength(int w);
   bool getWarriorDragonglass(int p);
   string getWarriorName(int y);
   bool getShip();
   bool getUser();
   bool isAlive();
   int getMyWarriors();
   Warrior getWarrior(int i); // returns Warrior at index i
   void setName(string heroName);
   void setMoney(int m);
   void setInfluence(int i);
   void setArmySize(int a);
   void setShip(string sail);
   void setRow(int r);
   void setColumn(int c);
   void setUser(bool u);
   void setAlive(bool d);
   void setMyWarriors(int w);
   void setWarriorDragonglass(int g);
   void setWarriorStrength(int v, int s);
   void setWarriorMorale(int u, int m);
   void setWarriorLoyalty(int t, int l);
   void addWarrior(Warrior w, int i); // adds a warrior "w" at index i
   void removeWarrior(string warriorName);
   
   
private:
   string name;
   int money;
   int influence;
   int army;
   Warrior warriors[4];
   int row;
   int column;
   bool ship;
   bool user;
   bool alive;
   const static int maxRow = 25;
   const static int maxColumn = 16;
   int myWarriors;
};

#endif
