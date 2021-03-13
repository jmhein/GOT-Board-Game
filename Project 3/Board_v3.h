#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Warrior_v3.h"
#include "Hero_v3.h"
#include "Tile_v3.h"
using namespace std;

/**
   A board class that sets up the game board via 2D array of tiles, tracks position of heros and warriors, and owners of each tile
 */

class Board
{
public:
   Board(); // default constructor - create blank 2D array of tiles, blank array of Warrior, blank array of heroes
   int readWarriors(string filename); // populate warriors array
   int readHeroes(string filename); // populate heroes array
   int readCities(string filename); // populate cities array
   int initilizeBoard(string filename); // populates the gameBoard array with tiles
   int initilizeDragonglass();
   int initilizeWarriors();
   int initilizeHeroes();
   void printGameBoard();
   void chooseHero();
   void userTurn();
   void computerTurn();
   void moveWarriors();
   void userHeroEncounters();
   void warriorEncounters();
   void computerEncounters();
   void updateResources();
   void winterIsComing();
   void printTotalPoints();
   void stannisSpecialEvent();
   void cersiSpecialEvent();
   void sansaSpecialEvent();
   void danySpecialEvent();
   string getUserName();
   bool isLastHero();
   int getUserPoints();
   int getUserArmySize();
   bool isUserAlive();
   int getUserTiles();
   bool whiteWalkers();
   void printHeroes();
   int createHero(string heroName);
   int getHeroPoints(string heroName); // may need more input paramters - will parce out as writing the code
   

//////// MAY NEED TO ADD OR MOVE ADDITIONAL FUNCTIONS WHILE WORKING THROUGH GAME MECHANICS ///////////////////////
   
private:
   const static int maxRows = 25;
   const static int maxColumns = 16;
   const static int maxWarriors = 14;
   const static int maxCities = 26;
   Tile gameBoard[maxRows][maxColumns];
   Warrior warriors[maxWarriors];
   Hero heroes[7];
   Tile cities[maxCities];
   int numWarriors;
   int numHeroes;
   int numCities;
   int whiteWalkerCount;
};

#endif
