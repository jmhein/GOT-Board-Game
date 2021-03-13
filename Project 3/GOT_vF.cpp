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
#include "Tile_v3.h" // include header file
#include "Warrior_v3.h" // include header file
#include "Hero_v3.h" // include header file
#include "Board_v3.h" // include header file

using namespace std;

int main() 
{
    string play;
    cout << "Welcome to the G A M E of T H R O N E S!" << endl;
    cout << endl;
    cout << "Would you like to play the game? ";
    getline(cin, play);
    while (play != "Y" && play != "N" && play != "y" && play != "n")
    {
        cout << "Invalid selection ";
        getline(cin, play);
    }
    while (play == "y" || play == "Y")
    {
        // initilize game setup (warriors, heroes, cities, map, dragonglass)
        srand (time(NULL));
        int turn = 0;
        Board b;
        b.readWarriors("warriors.txt");
        b.readHeroes("heroesGOT.txt");
        b.readCities("citiesGOT.txt");
        b.initilizeBoard("mapGOT.txt");
        b.initilizeDragonglass();
        b.initilizeWarriors();
        b.initilizeHeroes();
        
        //get player name and hero selection
        string username;
        string choice;
        
        int finalBattle = 0;
        int whiteWalkerCount;
        bool win = false;
        cout << "State your name, Your Grace: ";
        getline(cin, username);
        cout << endl;
        cout << "Would you like to choose a hero " << username << ", Your Grace? (Y/N): ";
        getline(cin, choice);
        while (choice != "Y" && choice != "y" && choice != "n" && choice != "N")
        {
            cout << "Please enter a vaild option (Y/N)" << endl;
            getline(cin, choice);
        }
        if (choice == "Y" || choice == "y")
        {
            b.chooseHero();
        }
        else if (choice == "N" || choice == "n")
        {
            b.createHero(username);
        }
        while (b.isUserAlive() == true && win != true)
        {
            b.userTurn();
            b.computerTurn();
            b.moveWarriors();
            b.userHeroEncounters();
            b.warriorEncounters();
            b.computerEncounters();
            b.updateResources();
            b.winterIsComing();
            b.printTotalPoints();
            cout << "End of turn " << turn << endl;
            turn++;
            if (turn == 10)
            {
                b.danySpecialEvent();
                b.stannisSpecialEvent();
                b.cersiSpecialEvent();
                b.sansaSpecialEvent();
            }
            if (turn > 50 || b.getUserArmySize() >= 2000 || b.getUserTiles() >= 200 || b.getUserPoints() > 400 || b.isLastHero() == true)
            {
                cout << "Sad news! The White Walkers are approaching our location.  Would you like to battle them now? (Y/N): ";
                getline(cin, choice);
                while (choice != "Y" && choice != "N")
                {
                    cout << "Please enter Y or N: ";
                    getline(cin, choice);
                }
                if (choice == "Y") // if yes, battle white walkers
                {
                    while (finalBattle < 3 && win != true)
                    {
                        if (b.whiteWalkers() == true)
                        {
                            cout << "Congratulations, " << username << "! You have defeated the White Walkers and claimed the Iron Throne." << endl;
                            ofstream myfile;
                            myfile.open ("results2.txt", fstream::app);
                            myfile << username;
                            myfile << setw(30);
                            myfile << b.getUserName();
                            myfile << setw(20);
                            myfile << to_string(b.getUserPoints()) << endl;
                            myfile.close();
                            win = true;
                        }
                        else if (finalBattle < 3)
                        {
                            cout << "You did not beat the White Walkers this round, Your Grace." << endl;
                            finalBattle++;
                        }
                    }
                    if (finalBattle >= 3 && win != true)
                    {
                        cout << "You have died battling the White Walkers." << endl;
                        cout << "GAME OVER" << endl;
                        
                        win = true;
                    }
                }
                else
                {
                    cout << "You must face the White Walkers within 5 turns or you will die." << endl;
                    whiteWalkerCount++;
                }
                if (whiteWalkerCount > 5)
                {
                    cout << "You did not face the White Walkers in time, Your Grace." << endl;
                    cout << "GAME OVER" << endl;
                    win = true;
                }
            }
        }
        cout << "Would you like to play again? (Y/N) ";
        getline(cin, play);
        while (play != "Y" && play != "N" && play != "y" && play != "n")
        {
            cout << "Invalid selection ";
            getline(cin, play);
        }  
    }
}

