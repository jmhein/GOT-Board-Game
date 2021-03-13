// CS1300 Spring 2019
// Author: Jeremy Hein
// Recitation: 204 – Telly Umada
// Cloud9 Workspace Editor Link: https://ide.c9.io/jmhein/csci1300_jmhein
// Project 3

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Tile_v3.h" // include header file
#include "Warrior_v3.h" // include header file
#include "Hero_v3.h" // include header file
#include "Board_v3.h" // include header file

using namespace std;

//////////////////////////////////// SPLIT FUNCTION ///////////////////////////////////////////////////////////

int split(string sentence, char delim, string mySplits[], int length) // Write function below
{ 
    int count = 0; // initilize count variable
    string word = ""; // temp string to hold word
    sentence = sentence + delim; // adds delim to end of string in order to pick up last word in sentence
    for (int i = 0; i < sentence.length(); i++)
    {
        if (count < length)
        {
            if (sentence[i] == delim) // if character at index i = delim
            {
                if (word.length() > 0) // check if word length is greater than 0
                {
                    mySplits[count] = word; // if true, print word
                    count ++; // count plus 1
                }
                word = "";
            }
            else
            {
            word = word + sentence[i]; // if character is not = to delim, word = previous characters + character at index #
            }
        }
        else
        {
            return -1;
        }
    }
}

/////////////////////////////////////////// Implementation file ///////////////////////////////////////////////////

Board::Board()
{
    gameBoard[maxRows][maxColumns];
    warriors[maxWarriors];
    heroes[7];
    cities[26];
    numWarriors = 0;
    numHeroes = 0;
    numCities = 0;
    whiteWalkerCount = 0;
}

/////////////////////////////////////////// READ WARRIORS FUNCTION ///////////////////////////////////////////////////

int Board::readWarriors(string filename)
{
    string line = ""; // temp string for reading file
    string temp_array[7]; // temp array to store / pass warriors into warriors array
    Warrior temp_warrior; // temp warrior variable
    ifstream myfile; // initialize variable of stream type
    myfile.open(filename); // open file specified in function parameter
    if (myfile.is_open()) // if file is opened successfully - do stuff
    {
        while (getline(myfile, line)) // while there are lines to read, do stuff below
        {
            if (line != "") // if line is not empty
            {
                split (line, ',', temp_array, 7); // split the string with ',' as deliminator
                temp_warrior.setName(temp_array[0]); // name is first element in array
                temp_warrior.setStrength(stoi(temp_array[1])); // strength is second element in array
                temp_warrior.setLoyalty(stoi(temp_array[2])); // loyalty is third element in array
                temp_warrior.setMorale(stoi(temp_array[3])); // morale is fourth element in array
                temp_warrior.setFree(temp_array[4]); // free is fifth element in array
                temp_warrior.setShip(temp_array[5]); // ship is sixth element in array
                temp_warrior.setDragonglass(temp_array[6]); // dragonglass is seventh element in array
                temp_warrior.setAlive(true);
                warriors[numWarriors] = temp_warrior; // pass temp book variable to bookArray at index i
                numWarriors++; // incriment numWarriors
            }
        }
        return numWarriors; // return numWarriors
    }
    else // if file opens unsuccessfully, return -1
    {
        return -1;
    }
}

/////////////////////////////////////////// READ HEROES FUNCTION ///////////////////////////////////////////////////

int Board::readHeroes(string filename)
{
    string line = ""; // temp string for reading file
    string temp_array[12]; // temp array to store / pass heroes into heroes array
    Hero temp_hero; // temp hero variable
    string temp_warrior;
    ifstream myfile; // initialize variable of stream type
    myfile.open(filename); // open file specified in function parameter
    if (myfile.is_open()) // if file is opened successfully - do stuff
    {
        while (getline(myfile, line)) // while there are lines to read, do stuff below
        {
            if (line != "") // if line is not empty
            {
                split (line, ',', temp_array, 12); // split the string with ',' as deliminator
                temp_hero.setName(temp_array[0]); // name is first element in array
                temp_hero.setMoney(stoi(temp_array[1])); // money is second element in array
                temp_hero.setInfluence(stoi(temp_array[2])); // influence is third element in array
                temp_hero.setArmySize(stoi(temp_array[3])); // army size is fourth element in array
                temp_hero.setRow(stoi(temp_array[8])); // row is 9th element in array
                temp_hero.setColumn(stoi(temp_array[9])); // column is 10th element in array
                //if (temp_array[10] == "yes")
                //{
                //    temp_hero.setShip("yes");
                //}
                temp_hero.setShip(temp_array[10]); // ship is 11th element in array
                temp_hero.setUser(false);
                temp_hero.setAlive(true);
                for (int i = 4; i < 8; i++)
                {
                    if (temp_array[i] != "NULL") // if temp array at index i does not equal NULL
                    {
                       temp_warrior = temp_array[i];
                       for (int j = 0; j < maxWarriors; j++)
                       {
                           if (temp_warrior == warriors[j].getName()) // check if names equal
                           {
                               temp_hero.addWarrior(warriors[j], temp_hero.getMyWarriors()); // if equal, add warrior at index j to temp hero at index i
                               warriors[j].setFree("no"); // warrior is not free
                               warriors[j].setRow(temp_hero.getRow()); // warriors row position equals heros row position
                               warriors[j].setColumn(temp_hero.getColumn()); // warriors column position equals hero position
                               if (warriors[j].getShip() == true)
                               {
                                   temp_hero.setShip("yes");
                               }
                           }
                       }
                    }
                }
                heroes[numHeroes] = temp_hero; // pass temp hero variable to heroes array at index numHeroes
                numHeroes++; // incriment numHeroes
                temp_hero.setMyWarriors(0);
            }
        }
        return numHeroes; // return numHeroes
    }
    else // if file opens unsuccessfully, return -1
    {
        return -1;
    }
}

/////////////////////////////////////////// READ CITIES FUNCTION ///////////////////////////////////////////////////

/**
   - takes file name as input
   - reads the file using getline and split functions 
   - populates Tiles from the file, and passes into "cities" array
 */

int Board::readCities(string filename)
{
    string line = ""; // temp string for reading file
    string temp_array[5]; // temp array to store / pass tiles into cities array
    Tile temp_tile; // temp tile variable
    ifstream myfile; // initialize variable of stream type
    myfile.open(filename); // open file specified in function parameter
    if (myfile.is_open()) // if file is opened successfully - do stuff
    {
        while (getline(myfile, line)) // while there are lines to read, do stuff below
        {
            if (line != "") // if line is not empty
            {
                split (line, ',', temp_array, 5); // split the string with ',' as deliminator
                temp_tile.setLetter(temp_array[0]); // letter is the first element in array
                temp_tile.setName(temp_array[1]); // name is the second element in array
                temp_tile.setMoney(stoi(temp_array[2])); // money is the third element in array
                temp_tile.setArmySize(stoi(temp_array[3])); // army size if the fourth element in array
                temp_tile.setPoints(stoi(temp_array[4])); // points is the last element in array
                cities[numCities] = temp_tile; // pass temp tile into cities array at index numCities
                numCities++; // incriment numCities
            }
        }
        return numCities; // return numCities
    }
    else // if file opens unsuccessfully, return -1
    {
        return -1;
    }
}

/////////////////////////////////////////// INITIALIZE BOARD FUNCTION ///////////////////////////////////////////////////

/**
   - takes file name as input
   - reads the file using getline and split functions 
   - checks letter for each split
   - if letter is w - this is a water tile - populate Tile variable with water stats and pass into 2D gameboard array
   - it letter is p - this is a land tile - populate Tile variable with land stats and pass into 2D gameboard array
   - if letter a city letter - find the appropriate cite tile (stored in cities array) and pass into 2D gameboard array
   - will have return values to be utilized in game driver function
 */

int Board::initilizeBoard(string filename)
{
    string line = ""; // temp string for reading file
    string temp_array[maxColumns]; // temp array to store / pass tiles into cities array
    Tile temp_tile; // temp tile variable
    ifstream myfile; // initialize variable of stream type
    myfile.open(filename); // open file specified in function parameter
    int rowCount = 0;
    if (myfile.is_open()) // if file is opened successfully - do stuff
    {
        while(getline(myfile, line)) // while there are lines to read, do stuff below
        {
            if (line != "") // if line is not empty
            {
               split (line, ',', temp_array, maxColumns);
               for (int i = 0; i < maxColumns; i++)
               {
                   if (temp_array[i] == "p")
                   {
                       temp_tile.setLetter("p");
                       temp_tile.setName("");
                       temp_tile.setMoney(20);
                       temp_tile.setArmySize(10);
                       temp_tile.setPoints(2);
                       temp_tile.setDragonglass("no");
                       gameBoard[rowCount][i] = temp_tile;
                   }
                   else if (temp_array[i] == "w")
                   {
                       temp_tile.setLetter("w");
                       temp_tile.setName("");
                       temp_tile.setMoney(10);
                       temp_tile.setArmySize(0);
                       temp_tile.setPoints(1);
                       temp_tile.setDragonglass("no");
                       gameBoard[rowCount][i] = temp_tile;
                   }
                   else
                   {
                       temp_tile.setLetter(temp_array[i]);
                       for (int k = 0; k < maxCities; k++)
                       {
                           if (temp_tile.getLetter() == cities[k].getLetter())
                           {
                               gameBoard[rowCount][i] = cities[k];
                           }
                       }
                   }
               }
               rowCount++;
            }
        }
        return 1; // return numCities
    }
    else // if file opens unsuccessfully, return -1
    {
        return -1;
    }
}

/////////////////////////////////////////// PRINT GAMEBOARD FUNCTION ///////////////////////////////////////////////////

/**
   - prints the full game board
 */
 
void Board::printGameBoard()
{
    for (int i = 0; i < maxRows; i++)
    {
        for (int j = 0; j < maxColumns; j++)
        {
            cout << setw(2);
            cout << gameBoard[i][j].getLetter();
        }
        cout << endl;
    }
}

/////////////////////////////////////////// INITIALIZE DRAGONGLASS FUNCTION ///////////////////////////////////////////////////

/**
   - randomizes land tiled in 2D tiles array that have dragonglass
 */

int Board::initilizeDragonglass()
{
    int count = 0; // variable to count number of land tiles with dragonglass
    int r; // store random value for row
    int c; // store random value for column
    while (count < 5) // while the count is less than 5
    {
        c = rand() % maxColumns + 1; // generates random number between 0 and 25
        r = rand() % maxRows + 1; // generates random number between 0 and 15
        if (gameBoard[r][c].getLetter() == 'p') // if letter at gameBoard index is land
        {
            gameBoard[r][c].setDragonglass("yes"); // set dragonglass to true
            count++; // increment count
        }
    }
    return count;
}

/////////////////////////////////////////// INITIALIZE WARRIORS FUNCTION ///////////////////////////////////////////////////

/**
   - randomizes land tiled in 2D tiles array that have dragonglass
 */

int Board::initilizeWarriors()
{
    int r; // hold value of row
    int c; // hold value of column
    for (int i = 0; i < numWarriors; i++) // for loop less than num warriors
    {
        c = rand() % maxColumns + 1; // generates random column number
        r = rand() % maxRows + 1; // generates random row number
        for (int j = 0; j < numWarriors; j++) // nested for loop
        {
            if (j != i) // check if warriors at index i are equal to warriors at index j
            {
                while (r == warriors[j].getRow() && c == warriors[j].getColumn() || gameBoard[r - 1][c - 1].getLetter() == 'w' && warriors[i].getShip() == false) // check that warriors are not in same spot as other characters, and if the tile is water they must have a ship
                {
                    c = rand() % maxColumns + 1; // if the above condition is true, generate new numbers
                    r = rand() % maxRows + 1;
                } 
            }
        }
        if (warriors[i].getFree() == true) // if the warrior is free, set row and column
        {
            warriors[i].setRow(r); 
            warriors[i].setColumn(c);
        }
    }
}

/////////////////////////////////////////// INITIALIZE HEROES FUNCTION ///////////////////////////////////////////////////

/**
   - assigns heroes ownership of their starting tiles
 */

int Board::initilizeHeroes()
{
    int r;
    int c;
    for (int i = 0; i < numHeroes; i++)
    {
        r = heroes[i].getRow() - 1;
        c = heroes[i].getColumn() - 1;
        gameBoard[r][c].setOwner(heroes[i], i); // set ownership for hero at starting location
        
    }
}

void Board::printHeroes()
{
    int index;
    for (int i = 0; i < numHeroes; i++)
    {
        cout << heroes[i].getName() << endl;
        cout << heroes[i].getMyWarriors() << endl;
        for (int j = 0; j < heroes[i].getMyWarriors(); j++)
        {
            cout << heroes[i].getWarriorName(j) << endl;
        }
    }
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getName() == "Cersei Lannister")
        {
            index = i;
        }
    }
    heroes[index].removeWarrior("Jaime Lannister");
    cout << endl;
    cout << heroes[index].getName() << endl;
    cout << heroes[index].getMyWarriors() << endl;
    for (int j = 0; j < heroes[index].getMyWarriors(); j++)
    {
       cout << heroes[index].getWarriorName(j) << endl;
    }
}

/////////////////////////////////////////// CHOOSE HERO FUNCTION ///////////////////////////////////////////////////

/**
   - presents player with a list of heroes to choose from
 */
 
void Board::chooseHero()
{
    string menuChoice;
    cout << "Please choose from the following heroes:" << endl;
    cout << endl;
    for (int i = 1; i < 7; i++)
    {
        cout << i << ". " << heroes[i - 1].getName() << endl;
    }
    getline(cin, menuChoice);
    while (menuChoice != "1" && menuChoice != "2" && menuChoice != "3" && menuChoice != "4" && menuChoice != "5" && menuChoice != "6")
    {
        cout << "Invalid intput. Please make another selection: ";
        getline(cin, menuChoice);
        cout << endl;
    }
    switch(stoi(menuChoice))
    {
 		case 1: heroes[0].setUser(true); 
 		        cout << "When you play the game of thrones, you win or you die, " << heroes[0].getName() << endl;
            break;
        case 2: heroes[1].setUser(true);
                cout << "When you play the game of thrones, you win or you die, " << heroes[1].getName() << endl;
            break;
        case 3: heroes[2].setUser(true);
                cout << "When you play the game of thrones, you win or you die, " << heroes[2].getName() << endl;
            break; 
        case 4: heroes[3].setUser(true); 
                cout << "When you play the game of thrones, you win or you die, " << heroes[3].getName() << endl;
            break;
        case 5: heroes[4].setUser(true);
                cout << "When you play the game of thrones, you win or you die, " << heroes[4].getName() << endl;
            break; 
        case 6: heroes[5].setUser(true); 
                cout << "When you play the game of thrones, you win or you die, " << heroes[5].getName() << endl;
            break;
    }
}

/////////////////////////////////////////// CREATE HERO FUNCTION ///////////////////////////////////////////////////

/**
   - promt user for inputs as outline in the writeup
   - pass intpus into a hero variable, and pass hero into the heroes array
 */

int Board::createHero(string heroName)
{
     Hero newHero;
     string m = "";
     string i = "";
     string a = "";
     string r = "";
     string c = "";
     cout << "Your Grace " << heroName << ", you have chosen to go on this journey alone.  Please provide starting values for your adventure." << endl;
     cout << endl;
     cout << "How much gold will you start with? ";
     getline(cin, m);
     while (stoi(m) < 0 || stoi(m) > 10000)
     {
        cout << "Please enter a number between 0 and 10,000: ";  
        getline(cin, m);
     }
     cout << "How much influence will you have? ";
     getline(cin, i);
     while (stoi(i) < 0 || stoi(i) > 10000)
     {
        cout << "Please enter a number between 0 and 10,000: ";   
        getline(cin, i);
     }
     cout << "How many knights are in your army? ";
     getline (cin, a);
     while (stoi(a) < 0 || stoi(a) > 10000)
     {
        cout << "Please enter a number between 0 and 10,000: "; 
        getline(cin, a);
     }
     cout << "Where will you begin your adventure? " << endl;
     cout << "Enter a number between 1 and 26" << endl;
     cout << "Row: ";
     getline(cin, r);
     while (stoi(r) < 1 || stoi(r) > maxRows)
     {
         cout << "Enter a number between 1 and 26" << endl;
         cout << "Row: ";
         getline(cin, r);
     }
     cout << "Enter a number between 1 and 16" << endl;
     cout << "Column: ";
     getline(cin, c);
     while (stoi(c) < 1 || stoi(c) > maxColumns)
     {
         cout << "Enter a number between 1 and 16" << endl;
         cout << "Column: ";
         getline(cin, c);
     }
     for (int i = 0; i < numWarriors; i++)
     {
         while (stoi(r) == warriors[i].getRow() && stoi(c) == warriors[i].getColumn() || stoi(r) < 1 || stoi(r) > maxRows || stoi(c) < 1 || stoi(c) > maxColumns)
         {
             cout << "You may not start in the same position as another character" << endl;
             cout << "Enter a number between 1 and 26" << endl;
             cout << "Row: ";
             getline(cin, r);
             cout << "Enter a number between 1 and 16" << endl;
             cout << "Column: ";
             getline(cin, c);
         }
     }
     for (int i = 0; i < numHeroes; i++)
     {
         while (stoi(r) == heroes[i].getRow() && stoi(c) == heroes[i].getColumn() || stoi(r) < 1 || stoi(r) > maxRows || stoi(c) < 1 || stoi(c) > maxColumns)
         {
             cout << "You may not start in the same position as another character" << endl;
             cout << "Enter a number between 1 and 26" << endl;
             cout << "Row: ";
             getline(cin, r);
             cout << "Enter a number between 1 and 16" << endl;
             cout << "Column: ";
             getline(cin, c);
         }
     }
     newHero.setName(heroName);
     newHero.setMoney(stoi(m));
     newHero.setInfluence(stoi(i));
     newHero.setArmySize(stoi(a));
     newHero.setRow(stoi(r));
     newHero.setColumn(stoi(c));
     newHero.setUser(true);
     newHero.setAlive(true);
     if (gameBoard[stoi(r) - 1][stoi(c) - 1].getLetter() == 'w')
     {
         newHero.setShip("yes");
     }
     else
     {
         newHero.setShip("no");
     }
     heroes[numHeroes] = newHero;
     numHeroes++;
     for (int i = 0; i < numHeroes; i++)
     {
         if (heroes[i].getUser() == true)
         {
             gameBoard[stoi(r) - 1][stoi(c) - 1].setOwner(heroes[i], i);
         }
     }
}

/////////////////////////////////////////// USER TURN FUNCTION ///////////////////////////////////////////////////

/**
   - mechanics for the users turn
 */

void Board::userTurn()
{
    int userIndex;
    string menuChoice;
    string travelDirection;
    bool validMove = false;
    for (int i = 0; i < numHeroes; i++) // find user index
    {
        if (heroes[i].getUser() == true)
        {
            userIndex = i;
        }
    }
    int userR = heroes[userIndex].getRow() - 1; // get the user row
    int userC = heroes[userIndex].getColumn() - 1; // get the user column
    int userMoney = heroes[userIndex].getMoney();
    int userArmy = heroes[userIndex].getArmySize();
    cout << "It is your turn, Your Grace " << heroes[userIndex].getName() << ". Here is your map:" << endl;
    cout << endl;
    for (int i = (userR - 3); i < (userR + 4); i++) // print 7x7 map as outlined in write up
    {
        for (int k = (userC - 3); k < (userC + 4); k++)
        {
            if (i < 0 || i > maxRows - 1)
            {
                cout << setw(2);
                cout << "X";
            }
            else if (k < 0 || k > maxColumns - 1)
            {
                cout << setw(2);
                cout << "X";
            }
            else if (gameBoard[i][k].getLetter() == 'p')
            {
                cout << setw(2);
                cout << "*";
            }
            else if (gameBoard[i][k].getLetter() == 'w')
            {
                cout << setw(2);
                cout << "~";
            }
            else
            {
                cout << setw(2);
                cout << gameBoard[i][k].getLetter();
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << endl;
    cout << "1. Travel" << endl;
    cout << "2. Rest" << endl;
    cout << "3. Consult with the gods" << endl;
    getline(cin, menuChoice);
    while (stoi(menuChoice) != 1 && stoi(menuChoice) != 2 && stoi(menuChoice) != 3)
    {
        cout << "Invalid input" << endl;
        getline(cin, menuChoice);
    }
    switch(stoi(menuChoice)) // get user choice for their menu options
    {
 		case 1: cout << "Will you travel North (N), South (S), East (E), or West (W)? ";
 		        while (validMove == false) // first check if move is valid
 		        {
 		            getline(cin, travelDirection);
 		            if (travelDirection != "N" && travelDirection != "E" && travelDirection != "S" && travelDirection != "W")
 		            {
 		                cout << "Please enter N, S, E, or W: ";
 		            }
 		            else if (travelDirection == "N" && heroes[userIndex].getRow() - 1 < 1) // checks if the edge of the map is one tile to the North
 		            {
 		                cout << "You have reached the edge of the map, Your Grace." << endl;
 		                cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "S" && heroes[userIndex].getRow() + 1 > maxRows)  // checks if the edge of the map is one tile to the South
 		            {
 		                cout << "You have reached the edge of the map, Your Grace." << endl;
 		                cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "E" && heroes[userIndex].getColumn() + 1 > maxColumns) // checks if the edge of the map is one tile to the East
 		            {
 		                cout << "You have reached the edge of the map, Your Grace." << endl;
 		                cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "W" && heroes[userIndex].getColumn() - 1 < 1) // checks if the edge of the map is one tile to the West
 		            {
 		                cout << "You have reached the edge of the map, Your Grace." << endl;
 		                cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "N" && gameBoard[userR - 1][userC].getLetter() == 'w' && heroes[userIndex].getShip() == false) // checks for water tile to the North and if user has ship
 		            {
 		                cout << "You must have a ship in order to move to a water tile, Your Grace." << endl;
     		            cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "S" && gameBoard[userR + 1][userC].getLetter() == 'w' && heroes[userIndex].getShip() == false) // checks for water tile to the South and if user has ship
 		            {
 		                cout << "You must have a ship in order to move to a water tile, Your Grace." << endl;
     		            cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "E" && gameBoard[userR][userC + 1].getLetter() == 'w' && heroes[userIndex].getShip() == false) // checks for water tile to the East and if user has ship
 		            {
 		                cout << "You must have a ship in order to move to a water tile, Your Grace." << endl;
     		            cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else if (travelDirection == "W" && gameBoard[userR][userC - 1].getLetter() == 'w' && heroes[userIndex].getShip() == false) // checks for water tile to the West and if user has ship
 		            {
 		                cout << "You must have a ship in order to move to a water tile, Your Grace." << endl;
     		            cout << "Please choose a different direction (N, S, E, or W): ";
 		            }
 		            else // if above conditions are not true, move is valid
 		            {
 		                validMove = true;
 		            }
 		        }
 		        if (travelDirection == "N") // update postion for move to the North
 		        {
 		            heroes[userIndex].setRow(heroes[userIndex].getRow() - 1);
 		        }
 		        else if (travelDirection == "S") // update postion for move to the South
 		        {
 		            heroes[userIndex].setRow(heroes[userIndex].getRow() + 1);
 		        }
 		        else if (travelDirection == "E") // update postion for move to the East
 		        {
 		            heroes[userIndex].setColumn(heroes[userIndex].getColumn() + 1);
 		        }
 		        else // update postion for move to the West
 		        {
 		            heroes[userIndex].setColumn(heroes[userIndex].getColumn() - 1);
 		        }
            break;
        case 2: if (heroes[userIndex].getMyWarriors() != 0) // check that user has warriors and update strength accordingly
                {
                    for (int i = 0; i < heroes[userIndex].getMyWarriors(); i++)
                    {
                        heroes[userIndex].setWarriorStrength(i, heroes[userIndex].getWarriorStrength(i) + 1);
                    }
                }
            break;
        case 3: if (heroes[userIndex].getMyWarriors() != 0) // check that user has warriors and update morale accordingly
                {
                    for (int i = 0; i < heroes[userIndex].getMyWarriors(); i++)
                    {
                        heroes[userIndex].setWarriorMorale(i, heroes[userIndex].getWarriorMorale(i) + 1);
                    }
                }
            break; 
    }
    cout << "Your turn is over, Your Grace " << heroes[userIndex].getName() << endl;
    cout << "You have:" << endl;
    cout << heroes[userIndex].getMoney() << " gold" << endl;
    cout << heroes[userIndex].getInfluence() << " influence" << endl;
    cout << heroes[userIndex].getArmySize() << " soldiers" << endl;
    cout << endl;
}

/////////////////////////////////////////// COMPUTER TURN FUNCTION ///////////////////////////////////////////////////

/**
   - promt user for inputs as outline in the writeup
   - pass intpus into a hero variable, and pass hero into the heroes array
 */

void Board::computerTurn()
{
    char travelDirection[4] = {'N', 'S', 'E', 'W'};
    bool validMove = false;
    int randomNumber;
    int heroR;
    int heroC;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == false && heroes[i].isAlive() == true) // check that hero is alive and it is not the main user
        {
            heroR = heroes[i].getRow() - 1;
            heroC = heroes[i].getColumn() - 1;
            validMove = false;
            while (validMove == false) // ensures computer move is valid
            {
                randomNumber = rand() % 4;
                if (travelDirection[randomNumber] == 'N' && (heroes[i].getRow() - 1) < 1)
 	            {
 	                validMove = false;
 	            }
 	            else if (travelDirection[randomNumber] == 'S' && (heroes[i].getRow() + 1) > maxRows)
 	            {
 	                validMove = false;
 	            }
 	            else if (travelDirection[randomNumber] == 'W' && (heroes[i].getColumn() - 1) < 1)
 	            {
 	                validMove = false;
 	            }
 	            else if (travelDirection[randomNumber] == 'E' && (heroes[i].getColumn() + 1) > maxColumns)
 	            {
 	                validMove = false;
 	            }
                else if (travelDirection[randomNumber] == 'N' && gameBoard[heroR - 1][heroC].getLetter() == 'w' && heroes[i].getShip() == false)
                {
                    validMove = false;
                }
                else if (travelDirection[randomNumber] == 'S' && gameBoard[heroR + 1][heroC].getLetter() == 'w' && heroes[i].getShip() == false)
                {
                    validMove = false;
                }
                else if (travelDirection[randomNumber] == 'E' && gameBoard[heroR][heroC + 1].getLetter() == 'w' && heroes[i].getShip() == false)
                {
                    validMove = false;
                }
                else if (travelDirection[randomNumber] == 'W' && gameBoard[heroR][heroC - 1].getLetter() == 'w' && heroes[i].getShip() == false)
                {
                    validMove = false;
                }
                else
                {
                    validMove = true;
                }
            }
            if (travelDirection[randomNumber] == 'N') 
            {
                heroes[i].setRow(heroes[i].getRow() - 1);
            }
            else if (travelDirection[randomNumber] == 'S') 
            {
                heroes[i].setRow(heroes[i].getRow() + 1);
            }
            else if (travelDirection[randomNumber] == 'E') 
            {
                heroes[i].setColumn(heroes[i].getColumn() + 1);
            }
            else if (travelDirection[randomNumber] == 'W') 
            {
                heroes[i].setColumn(heroes[i].getColumn() - 1);
            }
        }
    }
}

/////////////////////////////////////////// MOVE WARRIORS FUNCTION ///////////////////////////////////////////////////

/**
   - randomly moves warriors
 */

void Board::moveWarriors()
{
    char travelDirection[4] = {'N', 'S', 'E', 'W'};
    bool validMove = false;
    int randomNumber;
    int warriorR;
    int warriorC;
    for (int i = 0; i < numWarriors; i++)
    {
        if (warriors[i].getFree() == true) // same as move heroes
        {
            warriorR = warriors[i].getRow() - 1;
            warriorC = warriors[i].getColumn() - 1;
            validMove = false;
            while (validMove == false)
            {
                randomNumber = rand() % 4;
                if (travelDirection[randomNumber] == 'N' && (warriors[i].getRow() - 1) < 1)
 	            {
 	                validMove = false;
 	            }
 	            else if (travelDirection[randomNumber] == 'S' && (warriors[i].getRow() + 1) > maxRows)
 	            {
 	                validMove = false;
 	            }
 	            else if (travelDirection[randomNumber] == 'W' && (warriors[i].getColumn() - 1) < 1)
 	            {
 	                validMove = false;
 	            }
 	            else if (travelDirection[randomNumber] == 'E' && (warriors[i].getColumn() + 1) > maxColumns)
 	            {
 	                validMove = false;
 	            }
                else if (travelDirection[randomNumber] == 'N' && gameBoard[warriorR - 1][warriorC].getLetter() == 'w' && warriors[i].getShip() == false)
                {
                    validMove = false;
                }
                else if (travelDirection[randomNumber] == 'S' && gameBoard[warriorR + 1][warriorC].getLetter() == 'w' && warriors[i].getShip() == false)
                {
                    validMove = false;
                }
                else if (travelDirection[randomNumber] == 'E' && gameBoard[warriorR][warriorC + 1].getLetter() == 'w' && warriors[i].getShip() == false)
                {
                    validMove = false;
                }
                else if (travelDirection[randomNumber] == 'W' && gameBoard[warriorR][warriorC - 1].getLetter() == 'w' && warriors[i].getShip() == false)
                {
                    validMove = false;
                }
                else
                {
                    validMove = true;
                }
            }
            if (travelDirection[randomNumber] == 'N')
            {
                warriors[i].setRow(warriors[i].getRow() - 1);
            }
            else if (travelDirection[randomNumber] == 'S')
            {
                warriors[i].setRow(warriors[i].getRow() + 1);
            }
            else if (travelDirection[randomNumber] == 'E')
            {
                warriors[i].setColumn(warriors[i].getColumn() + 1);
            }
            else if (travelDirection[randomNumber] == 'W')
            {
                warriors[i].setColumn(warriors[i].getColumn() - 1);
            }
        }
    }
}

/////////////////////////////////////////// USER ENCOUNTER FUNCTION ///////////////////////////////////////////////////

/**
   - Checks for any user encounters
   - Prompts user for their choices and resolves encounter based on user inputs
 */

void Board::userHeroEncounters()
{
    int userIndex;
    int compIndex;
    int compR;
    int compC;
    int picks = 0;
    int x = 0;
    Warrior temp_warriors[8];
    Warrior w1;
    string menuChoice;
    string choice;
    string warriorChoice;
    double randomNumber;
    double probability = 0.0;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == true)
        {
            userIndex = i;
        }
    }
    int userR = heroes[userIndex].getRow() - 1;
    int userC = heroes[userIndex].getColumn() - 1;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == false && heroes[i].isAlive() == true) // check that hero is not user and is alive
        {
            compR = heroes[i].getRow() - 1;
            compC = heroes[i].getColumn() - 1;
            if (abs(userR - compR) <= 2 && abs(userC - compC) <= 2) // if within two tiles, prompt user for inputs
            {
                cout << "You have encountered " << heroes[i].getName() << endl;
                cout << "What would you like to do, Your Grace?" << endl;
                cout << endl;
                cout << "1. Give a speech" << endl;
                cout << "2. Buy them outright" << endl;
                cout << "3. Battle" << endl;
                getline(cin, menuChoice);
                while (stoi(menuChoice) != 1 && stoi(menuChoice) != 2 && stoi(menuChoice) != 3)
                {
                    cout << "Invalid input" << endl;
                    getline(cin, menuChoice);
                }
                switch(stoi(menuChoice))
                {
             		case 1: probability = (1 - (heroes[i].getWarriorMorale(0) / 100)) * (heroes[userIndex].getInfluence() / 1600); // case 1 speech
             		        randomNumber = (double)rand()/(RAND_MAX) + rand() % 1;
             		        if (randomNumber <= probability) // if won
             		        {
             		            cout << "You won the encounter with " << heroes[i].getName() << ", Your Grace." << endl;
             		            cout << heroes[i].getName() << " has retired" << endl;
             		            heroes[i].setAlive(false);
             		            heroes[userIndex].setMoney(heroes[userIndex].getMoney() + heroes[i].getMoney()); // user gets heroes money
             		            heroes[userIndex].setInfluence(heroes[userIndex].getInfluence() + heroes[i].getInfluence()); // user gets heroes influence
             		            heroes[userIndex].setArmySize(heroes[userIndex].getArmySize() + heroes[i].getArmySize()); // user gets heroes army
             		            for (int j = 0; j < maxRows; j++)
             		            {
             		                for (int k = 0; k < maxColumns; k++)
             		                {
             		                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
             		                    {
             		                        gameBoard[j][k].setOwner(heroes[userIndex], userIndex); // swith game borad tiles to user control
             		                    }
             		                }
             		            }
         		                if (heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors() > 4)
         		                {
         		                    cout << "Which warriors would you like to keep, You Grace?" << endl;
         		                    for (int j = 0; j < heroes[userIndex].getMyWarriors(); j++) // move all warriors to a temp array
         		                    {
         		                        temp_warriors[j] = heroes[userIndex].getWarrior(j);
         		                    }
         		                    for (int j = heroes[userIndex].getMyWarriors(); j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j ++)
         		                    {
         		                        temp_warriors[j] = heroes[i].getWarrior(x);
         		                        x++;
         		                    }
         		                    for (int j = 0; j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j++) // print all warriors to the screen
         		                    {
         		                        cout << j + 1 << ". " << temp_warriors[j].getName() << endl;
         		                    }
         		                    while (picks < 4) // user has four picks
         		                    {
             		                    getline(cin, warriorChoice);
             		                    while (stoi(warriorChoice) < 1 && stoi(warriorChoice) > heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors())
             		                    {
             		                        cout << "Invalid input" << endl;
             		                        getline(cin, warriorChoice);
             		                    }
         		                        for (int j = 0; j < numWarriors; j++)
         		                        {
         		                            if (temp_warriors[stoi(warriorChoice) - 1].getName() == warriors[j].getName())
         		                            {
         		                                heroes[userIndex].setMyWarriors(0);
         		                                heroes[userIndex].addWarrior(warriors[j], picks); // add approprite warrior to heroes party
         		                                cout << warriors[j].getName() << " has been added to your party!" << endl; // notify users
         		                            }
         		                        }
         		                        picks++; // increment picks
         		                    }
         		                    heroes[userIndex].setMyWarriors(4); // resent myWarriors to 4
         		                }
         		                else
         		                {
             		                for (int j = 0; j < heroes[i].getMyWarriors(); j++)
             		                {
             		                    heroes[userIndex].addWarrior(heroes[i].getWarrior(j), heroes[userIndex].getMyWarriors());
             		                }
         		                }
             		        }
             		        else
             		        {
             		            cout << "You lost the encounter with " << heroes[i].getName() << ", Your Grace." << endl;
             		            heroes[userIndex].setInfluence(heroes[userIndex].getInfluence() * 0.5);
             		        }
             		        picks = 0;
             		        x = 0;
             		        for (int j = 0; j < 8; j++)
             		        {
             		            temp_warriors[j] = w1;
             		        }
                        break;
                    case 2: probability = (1 - (heroes[i].getWarriorLoyalty(0) / 100)) * (heroes[userIndex].getMoney() / 17800); // buy outright
             		        randomNumber = (double)rand()/(RAND_MAX) + rand() % 1;
             		        if (randomNumber <= probability)
             		        {
             		            cout << "You won the encounter with " << heroes[i].getName() << ", Your Grace." << endl; // same mechanics as case 1
             		            cout << heroes[i].getName() << " has retired" << endl;
             		            heroes[i].setAlive(false);
             		            heroes[userIndex].setMoney(heroes[userIndex].getMoney() + heroes[i].getMoney());
             		            heroes[userIndex].setInfluence(heroes[userIndex].getInfluence() + heroes[i].getInfluence());
             		            heroes[userIndex].setArmySize(heroes[userIndex].getArmySize() + heroes[i].getArmySize());
             		            for (int j = 0; j < maxRows; j++)
             		            {
             		                for (int k = 0; k < maxColumns; k++)
             		                {
             		                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
             		                    {
             		                        gameBoard[j][k].setOwner(heroes[userIndex], userIndex);
             		                    }
             		                }
             		            }
         		                if (heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors() > 4)
         		                {
         		                    cout << "Which warriors would you like to keep, You Grace?" << endl;
         		                    for (int j = 0; j < heroes[userIndex].getMyWarriors(); j++)
         		                    {
         		                        temp_warriors[j] = heroes[userIndex].getWarrior(j);
         		                    }
         		                    for (int j = heroes[userIndex].getMyWarriors(); j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j ++)
         		                    {
         		                        temp_warriors[j] = heroes[i].getWarrior(x);
         		                        x++;
         		                    }
         		                    for (int j = 0; j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j++)
         		                    {
         		                        cout << j + 1 << ". " << temp_warriors[j].getName() << endl;
         		                    }
         		                    while (picks < 4)
         		                    {
             		                    getline(cin, warriorChoice);
             		                    while (stoi(warriorChoice) < 1 && stoi(warriorChoice) > heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors())
             		                    {
             		                        cout << "Invalid input" << endl;
             		                        getline(cin, warriorChoice);
             		                    }
         		                        for (int j = 0; j < numWarriors; j++)
         		                        {
         		                            if (temp_warriors[stoi(warriorChoice) - 1].getName() == warriors[j].getName())
         		                            {
         		                                heroes[userIndex].setMyWarriors(0);
         		                                heroes[userIndex].addWarrior(warriors[j], picks);
         		                                cout << warriors[j].getName() << " has been added to your party!" << endl;
         		                            }
         		                        }
         		                        picks++;
         		                    }
         		                    heroes[userIndex].setMyWarriors(4);
         		                }
         		                else
         		                {
             		                for (int j = 0; j < heroes[i].getMyWarriors(); j++)
             		                {
             		                    heroes[userIndex].addWarrior(heroes[i].getWarrior(j), heroes[userIndex].getMyWarriors());
             		                }
         		                }
             		        }
             		        else
             		        {
             		            cout << "You lost the encounter with " << heroes[i].getName() << ", Your Grace." << endl;
             		            heroes[userIndex].setMoney(heroes[userIndex].getMoney() * 0.5);
             		        }
             		        picks = 0;
             		        x = 0;
             		        for (int j = 0; j < 8; j++)
             		        {
             		            temp_warriors[j] = w1;
             		        }
                        break;
                    case 3: if (heroes[userIndex].getMyWarriors() == 0 && heroes[i].getMyWarriors() > 0) // battle mechanics
                            {
                                cout << "You have been defeated in battle, Your Grace!" << endl;
                                heroes[userIndex].setAlive(false);
                            }
                            else if (heroes[userIndex].getMyWarriors() > 0 && heroes[i].getMyWarriors() == 0) // same mechanics as before
             		        {
             		            cout << "You won the battle with " << heroes[i].getName() << ", Your Grace." << endl;
             		            cout << heroes[i].getName() << " has retired" << endl;
             		            heroes[i].setAlive(false);
             		            heroes[userIndex].setMoney(heroes[userIndex].getMoney() + heroes[i].getMoney());
             		            heroes[userIndex].setInfluence(heroes[userIndex].getInfluence() + heroes[i].getInfluence());
             		            heroes[userIndex].setArmySize(heroes[userIndex].getArmySize() + heroes[i].getArmySize());
             		            for (int j = 0; j < maxRows; j++)
             		            {
             		                for (int k = 0; k < maxColumns; k++)
             		                {
             		                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
             		                    {
             		                        gameBoard[j][k].setOwner(heroes[userIndex], userIndex);
             		                    }
             		                }
             		            }
         		                if (heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors() > 4)
         		                {
         		                    cout << "Which warriors would you like to keep, You Grace?" << endl;
         		                    for (int j = 0; j < heroes[userIndex].getMyWarriors(); j++)
         		                    {
         		                        temp_warriors[j] = heroes[userIndex].getWarrior(j);
         		                    }
         		                    for (int j = heroes[userIndex].getMyWarriors(); j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j ++)
         		                    {
         		                        temp_warriors[j] = heroes[i].getWarrior(x);
         		                        x++;
         		                    }
         		                    for (int j = 0; j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j++)
         		                    {
         		                        cout << j + 1 << ". " << temp_warriors[j].getName() << endl;
         		                    }
         		                    while (picks < 4)
         		                    {
             		                    getline(cin, warriorChoice);
             		                    while (stoi(warriorChoice) < 1 && stoi(warriorChoice) > heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors())
             		                    {
             		                        cout << "Invalid input" << endl;
             		                        getline(cin, warriorChoice);
             		                    }
         		                        for (int j = 0; j < numWarriors; j++)
         		                        {
         		                            if (temp_warriors[stoi(warriorChoice) - 1].getName() == warriors[j].getName())
         		                            {
         		                                heroes[userIndex].setMyWarriors(0);
         		                                heroes[userIndex].addWarrior(warriors[j], picks);
         		                                cout << warriors[j].getName() << " has been added to your party!" << endl;
         		                            }
         		                        }
         		                        picks++;
         		                    }
         		                    heroes[userIndex].setMyWarriors(4);
         		                }
         		                else
         		                {
             		                for (int j = 0; j < heroes[i].getMyWarriors(); j++)
             		                {
             		                    heroes[userIndex].addWarrior(heroes[i].getWarrior(j), heroes[userIndex].getMyWarriors());
             		                }
         		                }
             		        }
             		        else
             		        {
             		            cout << "Which warrior will represent you in battle, Your Grace?" << endl;
             		            for (int j = 0; j < heroes[userIndex].getMyWarriors(); j++)
             		            {
             		                cout << j + 1 << ". " << heroes[userIndex].getWarriorName(j) << endl;
             		            }
             		            getline(cin, choice);
             		            while (stoi(choice) > heroes[userIndex].getMyWarriors())
             		            {
             		                cout << "Invalid input" << endl;
             		                getline(cin, choice);
             		            }
             		            if (heroes[userIndex].getArmySize() * heroes[userIndex].getWarriorStrength(stoi(choice) - 1) > heroes[i].getArmySize() * heroes[i].getWarriorStrength(rand() % heroes[i].getMyWarriors()))
             		            {
             		                cout << "You won the battle with " << heroes[i].getName() << ", Your Grace." << endl;
                 		            cout << heroes[i].getName() << " has retired" << endl;
                 		            heroes[i].setAlive(false);
                 		            heroes[userIndex].setMoney(heroes[userIndex].getMoney() + heroes[i].getMoney());
                 		            heroes[userIndex].setInfluence(heroes[userIndex].getInfluence() + heroes[i].getInfluence());
                 		            heroes[userIndex].setArmySize(heroes[userIndex].getArmySize() + heroes[i].getArmySize());
                 		            for (int j = 0; j < maxRows; j++)
                 		            {
                 		                for (int k = 0; k < maxColumns; k++)
                 		                {
                 		                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
                 		                    {
                 		                        gameBoard[j][k].setOwner(heroes[userIndex], userIndex);
                 		                    }
                 		                }
                 		            }
             		                if (heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors() > 4)
             		                {
             		                    cout << "Which warriors would you like to keep, You Grace?" << endl;
             		                    for (int j = 0; j < heroes[userIndex].getMyWarriors(); j++)
             		                    {
             		                        temp_warriors[j] = heroes[userIndex].getWarrior(j);
             		                    }
             		                    for (int j = heroes[userIndex].getMyWarriors(); j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j ++)
             		                    {
             		                        temp_warriors[j] = heroes[i].getWarrior(x);
             		                        x++;
             		                    }
             		                    for (int j = 0; j < heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors(); j++)
             		                    {
             		                        cout << j + 1 << ". " << temp_warriors[j].getName() << endl;
             		                    }
             		                    while (picks < 4)
             		                    {
                 		                    getline(cin, warriorChoice);
                 		                    while (stoi(warriorChoice) < 1 && stoi(warriorChoice) > heroes[userIndex].getMyWarriors() + heroes[i].getMyWarriors())
                 		                    {
                 		                        cout << "Invalid input" << endl;
                 		                        getline(cin, warriorChoice);
                 		                    }
             		                        for (int j = 0; j < numWarriors; j++)
             		                        {
             		                            if (temp_warriors[stoi(warriorChoice) - 1].getName() == warriors[j].getName())
             		                            {
             		                                heroes[userIndex].setMyWarriors(0);
             		                                heroes[userIndex].addWarrior(warriors[j], picks);
             		                                cout << warriors[j].getName() << " has been added to your party!" << endl;
             		                            }
             		                        }
             		                        picks++;
             		                    }
             		                    heroes[userIndex].setMyWarriors(4);
             		                }
             		                else
             		                {
                 		                for (int j = 0; j < heroes[i].getMyWarriors(); j++)
                 		                {
                 		                    heroes[userIndex].addWarrior(heroes[i].getWarrior(j), heroes[userIndex].getMyWarriors());
                 		                }
         		                    }
             		            }
             		            else
             		            {
             		                cout << "You have been defeated in battle, Your Grace!" << endl;
                                    heroes[userIndex].setAlive(false);
             		            }
             		            picks = 0;
                 		        x = 0;
                 		        for (int j = 0; j < 8; j++)
                 		        {
                 		            temp_warriors[j] = w1;
                 		        }
             		        }
                        break;
                        cout << endl;
                }
            }
        }
    }
}

/////////////////////////////////////////// WARRIOR ENCOUNTERS FUNCTION ///////////////////////////////////////////////////

/**
   - checks to see if any heroes that are alive are in proximity of any free warriors
   - if more than one hero is in proximity - nothing happens
   - if one hero is in proximity and they have room in their party, the warrior is added to the party
   - warrior is no longer free, and increases morale and loyalty by 10
 */

void Board::warriorEncounters()
{
    int heroR;
    int heroC;
    int warriorR;
    int warriorC;
    int proximity;
    int heroIndex;
    for (int i = 0; i < numWarriors; i++)
    {
        if (warriors[i].isAlive() == true  && warriors[i].getFree() == true)
        {
            warriorR = warriors[i].getRow() - 1;
            warriorC = warriors[i].getColumn() - 1; 
            for (int j = 0; j < numHeroes; j++)
            {
               if (heroes[j].isAlive() == true)
               {
                    heroR = heroes[j].getRow() - 1;
                    heroC = heroes[j].getColumn() - 1;
                    if (abs(heroR - warriorR) <= 2 && abs(heroC - warriorC) <= 2)
                    {
                        proximity++;
                        heroIndex = j;
                    }
               }
            }
            if (proximity == 1 && heroes[heroIndex].getMyWarriors() < 4)
            {
                cout << heroes[heroIndex].getName() << " has added " << warriors[i].getName() << " to their party!" << endl;
                heroes[heroIndex].addWarrior(warriors[i], heroes[heroIndex].getMyWarriors());
                warriors[i].setFree("no");
                warriors[i].setRow(heroes[heroIndex].getRow());
                warriors[i].setColumn(heroes[heroIndex].getColumn());
                warriors[i].setLoyalty(warriors[i].getLoyalty() + 10);
                warriors[i].setMorale(warriors[i].getMorale() + 10);
            }
            proximity = 0;
        }
    }
}

/////////////////////////////////////////// COMPUTER ENCOUNTERS FUNCTION ///////////////////////////////////////////////////

void Board::computerEncounters()
{
    int heroR1;
    int heroC1;
    int heroR2;
    int heroC2;
    double h1battle;
    double h2battle;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == false && heroes[i].isAlive() == true)
        {
            heroR1 = heroes[i].getRow() - 1;
            heroC1 = heroes[i].getColumn() - 1;
            for (int j = 0; j < numHeroes; j ++)
            {
                if (j != i && heroes[j].getUser() == false && heroes[j].isAlive() == true)
                {
                    heroR2 = heroes[j].getRow() - 1;
                    heroC2 = heroes[j].getColumn() - 1;
                    if (abs(heroR1 - heroR2) <= 2 && abs(heroC1 - heroC2) <= 2)
                    {
                        if (heroes[i].getMyWarriors() == 0 && heroes[j].getMyWarriors() == 0)
                        {
                            if (heroes[i].getArmySize() > heroes[j].getArmySize())
                            {
                                cout << heroes[i].getName() << " has won the battle against " << heroes[j].getName() << endl;
                                cout << heroes[j].getName() << " has retired" << endl;
                                cout << endl;
                                heroes[j].setAlive(false);
                                heroes[i].setMoney(heroes[i].getMoney() + heroes[j].getMoney());
                                heroes[i].setInfluence(heroes[i].getInfluence() + heroes[j].getInfluence());
                                heroes[i].setArmySize(heroes[i].getArmySize() + heroes[j].getArmySize());
             		            for (int k = 0; k < maxRows; k++)
             		            {
             		                for (int x = 0; x < maxColumns; x++)
             		                {
             		                    if (gameBoard[k][x].getOwner() == heroes[j].getName())
             		                    {
             		                        gameBoard[k][x].setOwner(heroes[i], i);
             		                    }
             		                }
             		            }
         		                for (int k = 0; k < heroes[j].getMyWarriors(); k++)
         		                {
         		                    heroes[i].addWarrior(heroes[j].getWarrior(k), heroes[i].getMyWarriors());
         		                }
         		                if (heroes[i].getMyWarriors() > 4)
         		                {
         		                    heroes[i].setMyWarriors(4);
         		                }
                            }
                            else if (heroes[i].getArmySize() < heroes[j].getArmySize())
                            {
                                cout << heroes[j].getName() << " has won the battle against " << heroes[i].getName() << endl;
                                cout << heroes[i].getName() << " has retired" << endl;
                                cout << endl;
                                heroes[i].setAlive(false);
                                heroes[j].setMoney(heroes[i].getMoney() + heroes[j].getMoney());
                                heroes[j].setInfluence(heroes[i].getInfluence() + heroes[j].getInfluence());
                                heroes[j].setArmySize(heroes[i].getArmySize() + heroes[j].getArmySize());
             		            for (int k = 0; k < maxRows; k++)
             		            {
             		                for (int x = 0; x < maxColumns; x++)
             		                {
             		                    if (gameBoard[k][x].getOwner() == heroes[i].getName())
             		                    {
             		                        gameBoard[k][x].setOwner(heroes[j], j);
             		                    }
             		                }
             		            }
         		                for (int k = 0; k < heroes[i].getMyWarriors(); k++)
         		                {
         		                    heroes[j].addWarrior(heroes[i].getWarrior(k), heroes[j].getMyWarriors());
         		                }
         		                if (heroes[j].getMyWarriors() > 4)
         		                {
         		                    heroes[j].setMyWarriors(4);
         		                }
                            }
                            else
                            {
                                heroes[i].setArmySize(heroes[i].getArmySize() * 0.5);
                                heroes[j].setArmySize(heroes[j].getArmySize() * 0.5);
                            }
                        }
                        else if (heroes[i].getMyWarriors() == 0 && heroes[j].getMyWarriors() > 0)
                        {
                            cout << heroes[j].getName() << " has won the battle against " << heroes[i].getName() << endl;
                            cout << heroes[i].getName() << " has retired" << endl;
                            cout << endl;
                            heroes[i].setAlive(false);
                            heroes[j].setMoney(heroes[i].getMoney() + heroes[j].getMoney());
                            heroes[j].setInfluence(heroes[i].getInfluence() + heroes[j].getInfluence());
                            heroes[j].setArmySize(heroes[i].getArmySize() + heroes[j].getArmySize());
         		            for (int k = 0; k < maxRows; k++)
         		            {
         		                for (int x = 0; x < maxColumns; x++)
         		                {
         		                    if (gameBoard[k][x].getOwner() == heroes[i].getName())
         		                    {
         		                        gameBoard[k][x].setOwner(heroes[j], j);
         		                    }
         		                }
         		            }
     		                for (int k = 0; k < heroes[i].getMyWarriors(); k++)
     		                {
     		                    heroes[j].addWarrior(heroes[i].getWarrior(k), heroes[j].getMyWarriors());
     		                }
     		                if (heroes[j].getMyWarriors() > 4)
     		                {
     		                    heroes[j].setMyWarriors(4);
     		                }
                        }
                        else if (heroes[i].getMyWarriors() > 0 && heroes[j].getMyWarriors() == 0)
                        {
                            cout << heroes[i].getName() << " has won the battle against " << heroes[j].getName() << endl;
                            cout << heroes[j].getName() << " has retired" << endl;
                            cout << endl;
                            heroes[j].setAlive(false);
                            heroes[i].setMoney(heroes[i].getMoney() + heroes[j].getMoney());
                            heroes[i].setInfluence(heroes[i].getInfluence() + heroes[j].getInfluence());
                            heroes[i].setArmySize(heroes[i].getArmySize() + heroes[j].getArmySize());
         		            for (int k = 0; k < maxRows; k++)
         		            {
         		                for (int x = 0; x < maxColumns; x++)
         		                {
         		                    if (gameBoard[k][x].getOwner() == heroes[j].getName())
         		                    {
         		                        gameBoard[k][x].setOwner(heroes[i], i);
         		                    }
         		                }
         		            }
     		                for (int k = 0; k < heroes[j].getMyWarriors(); k++)
     		                {
     		                    heroes[i].addWarrior(heroes[j].getWarrior(k), heroes[i].getMyWarriors());
     		                }
     		                if (heroes[i].getMyWarriors() > 4)
     		                {
     		                    heroes[i].setMyWarriors(4);
     		                }
                        }
                        else
                        {
                            h1battle = heroes[i].getArmySize() * heroes[i].getWarriorStrength(rand() % heroes[i].getMyWarriors());
                            h2battle = heroes[j].getArmySize() * heroes[j].getWarriorStrength(rand() % heroes[j].getMyWarriors());
                            if (h1battle > h2battle)
                            {
                                cout << heroes[i].getName() << " has won the battle against " << heroes[j].getName() << endl;
                                cout << heroes[j].getName() << " has retired" << endl;
                                cout << endl;
                                heroes[j].setAlive(false);
                                heroes[i].setMoney(heroes[i].getMoney() + heroes[j].getMoney());
                                heroes[i].setInfluence(heroes[i].getInfluence() + heroes[j].getInfluence());
                                heroes[i].setArmySize(heroes[i].getArmySize() + heroes[j].getArmySize());
             		            for (int k = 0; k < maxRows; k++)
             		            {
             		                for (int x = 0; x < maxColumns; x++)
             		                {
             		                    if (gameBoard[k][x].getOwner() == heroes[j].getName())
             		                    {
             		                        gameBoard[k][x].setOwner(heroes[i], i);
             		                    }
             		                }
             		            }
         		                for (int k = 0; k < heroes[j].getMyWarriors(); k++)
         		                {
         		                    heroes[i].addWarrior(heroes[j].getWarrior(k), heroes[i].getMyWarriors());
         		                }
         		                if (heroes[i].getMyWarriors() > 4)
         		                {
         		                    heroes[i].setMyWarriors(4);
         		                }
                            }
                            else
                            {
                                cout << heroes[j].getName() << " has won the battle against " << heroes[i].getName() << endl;
                                cout << heroes[i].getName() << " has retired" << endl;
                                cout << endl;
                                heroes[i].setAlive(false);
                                heroes[j].setMoney(heroes[i].getMoney() + heroes[j].getMoney());
                                heroes[j].setInfluence(heroes[i].getInfluence() + heroes[j].getInfluence());
                                heroes[j].setArmySize(heroes[i].getArmySize() + heroes[j].getArmySize());
             		            for (int k = 0; k < maxRows; k++)
             		            {
             		                for (int x = 0; x < maxColumns; x++)
             		                {
             		                    if (gameBoard[k][x].getOwner() == heroes[i].getName())
             		                    {
             		                        gameBoard[k][x].setOwner(heroes[j], j);
             		                    }
             		                }
             		            }
         		                for (int k = 0; k < heroes[i].getMyWarriors(); k++)
         		                {
         		                    heroes[j].addWarrior(heroes[i].getWarrior(k), heroes[j].getMyWarriors());
         		                }
         		                if (heroes[j].getMyWarriors() > 4)
         		                {
         		                    heroes[j].setMyWarriors(4);
         		                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////// UPDATE RESOURCES FUNCTION ///////////////////////////////////////////////////

void Board::updateResources()
{
    int r;
    int c;
    int warriorR;
    int warriorC;
    string choice1;
    string choice2;
    string choice3;
    string choice4;
    int lowest = 50;
    int sumDistance;
    int heroIndex;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].isAlive() == true)
        {
            r = heroes[i].getRow() - 1;
            c = heroes[i].getColumn() - 1;
            if (gameBoard[r][c].setOwner(heroes[i], i) == 1 || gameBoard[r][c].getOwner() != heroes[i].getName())
            {
                gameBoard[r][c].setOwner(heroes[i], i);
                heroes[i].setMoney(heroes[i].getMoney() + gameBoard[r][c].getMoney());
                heroes[i].setArmySize(heroes[i].getArmySize() + gameBoard[r][c].getArmySize());
                if (gameBoard[r][c].getLetter() != 'w' && gameBoard[r][c].getLetter() != 'p' && heroes[i].getUser() == true)
                {
                    cout << "You have arrived in " << gameBoard[r][c].getName() << ". Do you want to listen to rumors? (Y/N): ";
                    getline(cin, choice1);
                    while (choice1 != "Y" && choice1 != "N")
                    {
                        cout << "Please enter Y or N: ";
                        getline(cin, choice1);
                    }
                    if (choice1 == "Y")
                    {
                        for (int j = 0; j < numHeroes; j++)
                        {
                            if (j != i)
                            {
                                sumDistance = abs(r - heroes[j].getRow()) + abs(c - heroes[j].getColumn());
                                if (sumDistance < lowest && heroes[j].isAlive() == true)
                                {
                                    lowest = sumDistance;
                                    heroIndex = j;
                                }
                            }
                        }
                        cout << heroes[heroIndex].getName() << " is " << lowest << " moves away." << endl;
                    }
                    cout << endl;
                    cout << "Do you want to buy more knights? (Y/N): ";
                    getline(cin, choice2);
                    while (choice2 != "Y" && choice2 != "N")
                    {
                        cout << "Please enter Y or N: ";
                        getline(cin, choice2);
                    }
                    if (choice2 == "Y")
                    {
                        cout << "Each knight costs 20 gold. You have " << heroes[i].getMoney() << " gold available.  How many would you like to buy? ";
                        getline(cin, choice3);
                        while (stoi(choice3) > (heroes[i].getMoney() / 20))
                        {
                            cout << "You may buy a maximum of " << heroes[i].getMoney() / 20 << " knights." << endl;
                            cout << "How many knights would you like to buy? ";
                            getline(cin, choice3);
                        }
                        heroes[i].setMoney(heroes[i].getMoney() - (stoi(choice3) * 20));
                        heroes[i].setArmySize(heroes[i].getArmySize() + stoi(choice3));
                    }
                }
            }
            else
            {
                gameBoard[r][c].setOwner(heroes[i], i);
            }
            if (gameBoard[r][c].getDragonglass() == true && heroes[i].getUser() == true && heroes[i].getMyWarriors() != 0)
            {
                cout << "Great news!  You have stumbled upond Dragonglass.  Choose which one of your warriors you would like to equip with Dragonglass:" << endl;
                for (int j = 0; j < heroes[i].getMyWarriors(); j++)
                {
                    cout << j + 1 << ". " << heroes[i].getWarriorName(j) << endl;
                }
                getline(cin, choice4);
                while (stoi(choice4) < 1 && stoi(choice4) > 4)
                {
                    cout << "Invalid input" << endl;
                    getline(cin, choice4);
                }
                heroes[i].setWarriorDragonglass(stoi(choice4) - 1);
                gameBoard[r][c].setDragonglass("no");
            }
            else
            {
                if (heroes[i].getMyWarriors() != 0)
                {
                    heroes[i].setWarriorDragonglass(rand () % heroes[i].getMyWarriors());
                    gameBoard[r][c].setDragonglass("no");
                }
            }
        }
    }
    for (int i = 0; i < numWarriors; i++)
    {
        if (warriors[i].getFree() == true)
        {
            warriorR = warriors[i].getRow() - 1;
            warriorC = warriors[i].getColumn() - 1;
            if (gameBoard[warriorR][warriorC].getDragonglass() == true)
            {
                cout << warriors[i].getName() << " has been equipped with Dragonglass!" << endl;
                warriors[i].setDragonglass("yes");
                gameBoard[warriorR][warriorC].setDragonglass("no");
            }
        }
    }
}


/////////////////////////////////////////// WINTER IS COMING FUNCTION ///////////////////////////////////////////////////
/**
    - 30% probability an event will occur
    - If an event occurs, equal probability between the four choices
*/

void Board::winterIsComing()
{
    double probability = 0.3;
    double randomNumber = (double)rand()/(RAND_MAX) + rand() % 1; // generates random decimal between 0 and 1
    int randomNumber2;
    int userIndex;
    if (randomNumber <= probability) // if the random number is less than or equal to the probability
    {
        randomNumber2 = rand() % 4 + 1; // generate another random number between 1 and r
        switch (randomNumber2)
        {
            case 1: cout << "Drought: There has been no rain in days and the army has very little food left!" << endl;
                    for (int i = 0; i < numHeroes; i++)
                    {
                        if (heroes[i].getUser() == true)
                        {
                            userIndex = i;
                        }
                    }
                    cout << heroes[userIndex].getName() << "'s warriors lose 10 morale and 10 strength." << endl;
                    cout << endl;
                    for (int i; i < heroes[userIndex].getMyWarriors(); i++)
                    {
                        heroes[userIndex].setWarriorStrength(i, heroes[userIndex].getWarriorStrength(i) - 10);
                        heroes[userIndex].setWarriorMorale(i, heroes[userIndex].getWarriorMorale(i) - 10);
                    }
                break;
            case 2: cout << "Deserters: This campaign is taking a very long time and the soldiers are tired and sad.  Some decide to leave!" << endl;
                    for (int i = 0; i < numHeroes; i++)
                    {
                        if (heroes[i].getUser() == true)
                        {
                            userIndex = i;
                        }
                    }
                    cout << heroes[userIndex].getName() << "'s warriors lose 10 loyalty and " << heroes[userIndex].getName() << " loses 10 knights." << endl;
                    cout << endl;
                    for (int i; i < heroes[userIndex].getMyWarriors(); i++)
                    {
                        heroes[userIndex].setWarriorLoyalty(i, heroes[userIndex].getWarriorLoyalty(i) - 10);
                        heroes[userIndex].setArmySize(heroes[userIndex].getArmySize() - 10);
                    }
                break;
            case 3: cout << "Jackpot: Your heroic cause has won the hearts of many noble and wealthy benefactors! They generously donate funds to your cause." << endl;
                    for (int i = 0; i < numHeroes; i++)
                    {
                        if (heroes[i].getUser() == true)
                        {
                            userIndex = i;
                        }
                    }
                    cout << heroes[userIndex].getName() << " doubles their money!" << endl;
                    cout << endl;
                    heroes[userIndex].setMoney(heroes[userIndex].getMoney() * 2);
                break; 
            case 4: cout << "Kindness: You decide to offer shelter to some refugees." << endl;
                    for (int i = 0; i < numHeroes; i++)
                    {
                        if (heroes[i].getUser() == true)
                        {
                            userIndex = i;
                        }
                    }
                    cout << heroes[userIndex].getName() << "'s warriors gain 10 loyalty and " << heroes[userIndex].getName() << " gains 10 knights." << endl;
                    cout << endl;
                    for (int i; i < heroes[userIndex].getMyWarriors(); i++)
                    {
                        heroes[userIndex].setWarriorLoyalty(i, heroes[userIndex].getWarriorLoyalty(i) + 10);
                        heroes[userIndex].setArmySize(heroes[userIndex].getArmySize() + 10);
                    }
                break;
        }
    }
}

/////////////////////////////////////////// PRINT TOTAL POINTS FUNCTION ///////////////////////////////////////////////////
/**
    - For each hero, prints number of tiles controlled and their total points
    - Returns the users total points
*/

void Board::printTotalPoints()
{
    for (int i = 0; i < numHeroes; i++)
    {
        int tileCount = 0;
        int pointCount = 0;
        if (heroes[i].isAlive() == true)
        {
            for (int j = 0; j < maxRows; j++)
            {
                for (int k = 0; k < maxColumns; k++)
                {
                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
                    {
                        tileCount++;
                        pointCount = pointCount + gameBoard[j][k].getPoints();
                    }
                }
            }
            cout << heroes[i].getName() << " controls " << tileCount << " tiles and has " << pointCount << " points." << endl;
        }
    }
    cout << endl;
}

/////////////////////////////////////////// GET USER POINTS FUNCTION ///////////////////////////////////////////////////
/**
    - For each hero, prints number of tiles controlled and their total points
    - Returns the users total points
*/

int Board::getUserPoints()
{
    int userPoints = 0;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == true)
        {
            for (int j = 0; j < maxRows; j++)
            {
                for (int k = 0; k < maxColumns; k++)
                {
                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
                    {
                        userPoints = userPoints + gameBoard[j][k].getPoints();
                    }
                }
            }
        }
    }
    return userPoints;
}

/////////////////////////////////////////// GET USER ARMY SIZE FUNCTION ///////////////////////////////////////////////////

/**
    - Returns the users army size
    - to be used in condition for white walkers
*/

int Board::getUserArmySize()
{
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == true)
        {
            return heroes[i].getArmySize();
        }
    }
}

/////////////////////////////////////////// IS USER ALIVE FUNCTION ///////////////////////////////////////////////////

/**
    - Returns if user is alive (T/F)
*/

bool Board::isUserAlive()
{
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == true)
        {
            return heroes[i].isAlive();
        }
    }
}

/////////////////////////////////////////// IS LAST HERO ALIVE FUNCTION ///////////////////////////////////////////////////

/**
    - Returns if user is the last hero alive (T/F)
*/

bool Board::isLastHero()
{
    int count = 0;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == false)
        {
            if (heroes[i].isAlive() == true)
            {
                count++;
            }
        }
    }
    if (count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/////////////////////////////////////////// GET USER TILES FUNCTION ///////////////////////////////////////////////////
/**
    - Returns the number of tiles the user controls
*/

int Board::getUserTiles()
{
    int tileCount = 0;
    for (int i = 0; i < numHeroes; i++) // cycle through heroes to find user
    {
        if (heroes[i].getUser() == true)
        {
            for (int j = 0; j < maxRows; j++)
            {
                for (int k = 0; k < maxColumns; k++)
                {
                    if (gameBoard[j][k].getOwner() == heroes[i].getName())
                    {
                        tileCount++; // count tile if owned by user
                    }
                }
            }
        }
    }
    return tileCount; // return the tile count
}

/////////////////////////////////////////// WHITE WALKERS FUNCTION ///////////////////////////////////////////////////
/**
    - Mechanics for final battle with White Walkers
    - return true if user won, false if loser lost
*/

bool Board::whiteWalkers()
{
    bool win = false;
    int turnCount = 0;
    int userIndex;
    double userPower = 0.0;
    double probability = 0.0;
    double randomNumber;
    int cityCount = 0;
    string choice;
    for (int i = 0; i < numHeroes; i++) // get users index
    {
        if (heroes[i].getUser() == true)
        {
            userIndex = i;
        }
    }
    userPower = heroes[userIndex].getArmySize(); // start user power score with army size
    for (int i = 0; i < heroes[userIndex].getMyWarriors(); i++)
    {
        userPower = userPower + (heroes[userIndex].getWarriorStrength(i) * (heroes[userIndex].getWarriorMorale(i) / 50)); // increase user power score with user warriors
        if (heroes[userIndex].getWarriorDragonglass(i) == true)
        {
            userPower = userPower + 10000;
        }
    }
    for (int i = 0; i < maxRows; i++)
    {
        for (int j = 0; j < maxColumns; j++)
        {
            if (gameBoard[i][j].getOwner() == heroes[userIndex].getName() && gameBoard[i][j].getLetter() != 'w' && gameBoard[i][j].getLetter() != 'p')
            {
                cityCount++;
            }
        }
    }
    userPower = userPower + ((cityCount + 1) * (heroes[userIndex].getInfluence() / 4));
    probability = 1 - exp(-userPower / 30000);
    randomNumber = (double)rand()/(RAND_MAX) + rand() % 1; // generates random decimal between 0 and 1
    if (randomNumber <= probability)
    {
        win = true;
    }
    else
    {
        win = false;
    }
    return win;
}

////////////////////////////////////////////// SPEICAL EVENT STANNIS /////////////////////////////////////////////////

/**
    - Mechanics for stannis special event
*/

void Board::stannisSpecialEvent()
{
    int indexS;
    string choice;
    int c;
    int r;
    for (int i = 0; i < numHeroes; i++) // find index for hero Stannis Baratheon
    {
        if (heroes[i].getName() == "Stannis Baratheon")
        {
            indexS = i;
        }
    }
    if (heroes[indexS].isAlive() == true) // if Stannis is alive
    {
        heroes[indexS].setAlive(false); // not anymore
        cout << "Stannis Baratheon has been consumed by his deomons!" << endl;
        cout << "Stannis Baratheon has retired.  Press F to pay respects."; // prompt user to pay respects
        getline(cin, choice);
        while (choice != "F" && choice != "f")
        {
            cout << "Have you no respect?! Press F to pay respects. ";
            getline(cin, choice);
            cout << endl;
        }
        cout << "Mood." << endl;
        cout << endl;
        for (int i = 0; i < heroes[indexS].getMyWarriors(); i++) // generates randome starting location for Stannis warriors
        {
            for (int j = 0; j < numWarriors; j++)
            {
                if (heroes[indexS].getWarriorName(i) == warriors[j].getName())
                {
                    warriors[j].setFree("yes");
                    c = rand() % maxColumns + 1; // generates random column number
                    r = rand() % maxRows + 1; // generates random row number
                    for (int k = 0; k < numWarriors; k++) // for loop less than num warriors
                    {
                        if (k != j) // check if warriors at index i are equal to warriors at index j
                        {
                            while (r == warriors[k].getRow() && c == warriors[k].getColumn() || gameBoard[r - 1][c - 1].getLetter() == 'w' && warriors[j].getShip() == false) // check that warriors are not in same spot as other characters, and if the tile is water they must have a ship
                            {
                                c = rand() % maxColumns + 1; // if the above condition is true, generate new numbers
                                r = rand() % maxRows + 1;
                            } 
                        }
                    }
                    warriors[j].setRow(r); 
                    warriors[j].setColumn(c);
                }
            }
        }
    }
}

////////////////////////////////////////////// SPEICAL EVENT CERSI /////////////////////////////////////////////////

/**
    - Mechanics for cersi special event
*/

// Special event for Cersi Lannister
void Board::cersiSpecialEvent()
{
    int indexC;
    int r;
    int c;
    for (int i = 0; i < numHeroes; i++) // find index for Cersei
    {
        if (heroes[i].getName() == "Cersei Lannister")
        {
            indexC = i;
        }
    }
    if (heroes[indexC].isAlive() == true) // check that Cersei is alive
    {
        heroes[indexC].removeWarrior("Jaime Lannister"); // remove jaime
        cout << "Jaime Lannister has left Cersi Lannister's party!  Jaime Lannister is now a free roaming warrior." << endl; // notify user
        cout << endl;
        for (int j = 0; j < numWarriors; j++)
        {
            if (warriors[j].getName() == "Jaime Lannister") // generates random starting location for Jaime
            {
                warriors[j].setFree("yes");
                c = rand() % maxColumns + 1; // generates random column number
                r = rand() % maxRows + 1; // generates random row number
                for (int k = 0; k < numWarriors; k++) // for loop less than num warriors
                {
                    if (k != j) // check if warriors at index i are equal to warriors at index j
                    {
                        while (r == warriors[k].getRow() && c == warriors[k].getColumn() || gameBoard[r - 1][c - 1].getLetter() == 'w' && warriors[j].getShip() == false) // check that warriors are not in same spot as other characters, and if the tile is water they must have a ship
                        {
                            c = rand() % maxColumns + 1; // if the above condition is true, generate new numbers
                            r = rand() % maxRows + 1;
                        } 
                    }
                }
                warriors[j].setRow(r); 
                warriors[j].setColumn(c);
            }
        }
    }
}

////////////////////////////////////////////// SPEICAL EVENT Sansa /////////////////////////////////////////////////

/**
    - Mechanics for sansa special event
*/

void Board::sansaSpecialEvent()
{
    int indexStark;
    int indexArya;
    for (int i = 0; i < numHeroes; i++) // find hero index for Sansa
    {
        if (heroes[i].getName() == "Sansa Stark")
        {
            indexStark = i;
        }
    }
    for (int i = 0; i < numWarriors; i++) // find warrior index for Arya
    {
        if (warriors[i].getName() == "Arya Stark")
        {
            indexArya = i;
        }
    }
    if (heroes[indexStark].isAlive() == true) // check that Sansa is alive
    {
        for (int i = 0; i < numHeroes; i++)
        {
            for (int j = 0; j < heroes[i].getMyWarriors(); j++)
            {
                if (heroes[i].getWarriorName(j) == "Arya Stark" && heroes[i].isAlive() == true) // if hero at index i is alive and has Arya
                {
                    cout << "Arya Stark has left " << heroes[i].getName() << "'s party!" << endl; // notify user Arya has left heroes party
                    cout << endl;
                    heroes[i].removeWarrior("Arya Stark"); // remove from party
                }
            }
        }
        cout << "Arya Stark has joined Sansa Stark's Party!" << endl; // notify that Arya has joined Sansa's party
        cout << endl;
        heroes[indexStark].addWarrior(warriors[indexArya], heroes[indexStark].getMyWarriors() - 1); // add Arya to Sansa'a party
        warriors[indexArya].setFree("no"); // Arya not free
    }
}

/////////////////////////////////////////// Special event Dany function ///////////////////////////////////////////////////
/**
    - Mechanics for dany special event
*/

void Board::danySpecialEvent()
{
    // Speical even for Daenerys Targaryen
    int indexD;
    int r; // hold value of row
    int c; // hold value of column
    Warrior Dragons ("Dragons", 180, 100, 80, "no", "no", "no", true); // create dragons warrior
    warriors[numWarriors - 1] = Dragons; // add dragons to warriors array
    for (int i = 0; i < numHeroes; i++) // find Dany index
    {
        if (heroes[i].getName() == "Daenerys Targaryen")
        {
            indexD = i;
        }
    }
    if (heroes[indexD].isAlive() == true) // check that Daenerys is alive
    {
        cout << "Daenerys Targaryen has added Dragons to her party!" << endl;
        cout << endl;
        heroes[indexD].setArmySize(heroes[indexD].getArmySize() + 5000); // increase army by 5k
        if (heroes[indexD].getMyWarriors() == 4) // if she has 4 warriors
        {
            Dragons.setStrength(Dragons.getStrength() * 1.1); // increase strength by 10%
            Dragons.setLoyalty(Dragons.getLoyalty() * 1.1); // increase loyalty by 10%
            Dragons.setMorale(Dragons.getMorale() * 1.1); // increase morale by 10%
            heroes[indexD].removeWarrior(heroes[indexD].getWarriorName(3)); // remove last warrior
            heroes[indexD].addWarrior(Dragons, 3); // add dragons to last index
        }
        else
        {
            heroes[indexD].addWarrior(Dragons, heroes[indexD].getMyWarriors() - 1);
        }
    }
}
    

string Board::getUserName()
{
    int userIndex;
    for (int i = 0; i < numHeroes; i++)
    {
        if (heroes[i].getUser() == true)
        {
            userIndex = i;
        }
    }
    return heroes[userIndex].getName();
}