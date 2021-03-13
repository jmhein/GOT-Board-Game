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
#include "Warrior_v3.h" // include header file
#include "Hero_v3.h"
using namespace std;

// Implementation file

Hero::Hero() // default constructor
{
    name = "";
    money = 0;
    influence = 0;
    army = 0;
    row = 0;
    column = 0;
    ship = false;
    myWarriors = 0;
    user = false;
    alive = true;
}

Hero::Hero(string heroName, int m, int i, int a, Warrior w1, Warrior w2, Warrior w3, Warrior w4, int r, int c, string sail, bool user, bool d) // parameterized constructor
{
    name = heroName;
    money = m;
    influence = i;
    row = r;
    column = c;
    if (sail == "yes")
    {
        ship = true;
    }
    else
    {
        ship = false;
    }
    warriors[0] = w1;
    warriors[1] = w2;
    warriors[2] = w3;
    warriors[3] = w4;
    user = false;
    alive = true;
}

string Hero::getName()
{
    return name; // return name
}

int Hero::getMoney() 
{
    return money; // return money
}

int Hero::getInfluence()
{
    return influence; // return influence
}

int Hero::getArmySize()
{
    return army; // return army size
}

int Hero::getRow()
{
    return row; // return army size
}

int Hero::getColumn()
{
    return column; // return army size
}

int Hero::getWarriorMorale(int z)
{
    return warriors[z].getMorale();
}

int Hero::getWarriorLoyalty(int x)
{
    return warriors[x].getLoyalty();
}

int Hero::getWarriorStrength(int w)
{
    return warriors[w].getStrength();
}

string Hero::getWarriorName(int y)
{
    return warriors[y].getName();
}

bool Hero::getWarriorDragonglass(int p)
{
    if (p < myWarriors)
    {
        return warriors[p].getDragonglass();
    }
}

bool Hero::getShip()
{
    return ship;
}

bool Hero::getUser()
{
    return user;
}

bool Hero::isAlive()
{
    return alive;
}

int Hero::getMyWarriors()
{
    return myWarriors; // return army size
}

Warrior Hero::getWarrior(int i)
{
    if (i < 4)
    {
        return warriors[i]; // return warrior at index i - MAY NEED TO MOVE
    }
}

void Hero::setName(string heroName)
{
    name = heroName;
}

void Hero::setMoney(int m)
{
    money = m;
}

void Hero::setInfluence(int i)
{
    influence = i;
}

void Hero::setArmySize(int a)
{
    army = a;
}

void Hero::setShip(string sail)
{
    if (sail == "yes")
    {
        ship = true;
    }
    else
    {
        ship = false;
    }
}

void Hero::setUser(bool u)
{
    user = u;
}

void Hero::setAlive(bool d)
{
    alive = d;
}

void Hero::setRow(int r)
{
    row = r;
    for (int i = 0; i < myWarriors; i++)
    {
        warriors[i].setRow(r);
    }
}

void Hero::setColumn(int c)
{
    column = c;
    for (int i = 0; i < myWarriors; i++)
    {
        warriors[i].setColumn(c);
    }
}

void Hero::setMyWarriors(int w)
{
    myWarriors = w;
}

void Hero::addWarrior(Warrior w, int i)
{
    if (myWarriors < 4)
    {
        warriors[i] = w;
        myWarriors++;
    }
    if (w.getShip() == true)
    {
        ship = true;
    }
}

void Hero::setWarriorDragonglass(int g)
{
    if (g < myWarriors)
    {
        warriors[g].setDragonglass("yes");
    }
}

void Hero::setWarriorStrength(int v, int s)
{
    if (v < myWarriors)
    {
        warriors[v].setStrength(s);
    }
}

void Hero::setWarriorMorale(int u, int m)
{
    if (u < myWarriors)
    {
        warriors[u].setMorale(m);
    }
}

void Hero::setWarriorLoyalty(int t, int l)
{
    if (t < myWarriors)
    {
        warriors[t].setLoyalty(l);
    }
}

void Hero::removeWarrior(string warriorName)
{
    Warrior temp_warriors[4];
    Warrior w1;
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        if (warriors[i].getName() != warriorName)
        {
            temp_warriors[k] = warriors[i];
            k++;
        }
    }
    myWarriors--;
    for (int i = 0; i < myWarriors; i++)
    {
        warriors[i] = temp_warriors[i];
    }
}