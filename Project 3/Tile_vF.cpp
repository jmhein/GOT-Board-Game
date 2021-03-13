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
#include "Hero_v3.h"

using namespace std;

// Implementation file

Tile::Tile() // default constructor
{
    letter = ' ';
    name = "";
    money = 0;
    army_size = 0;
    points = 0;
    dragonglass = false;
    hero0 = 0;
    hero1 = 0;
    hero2 = 0;
    hero3 = 0;
    hero4 = 0;
    hero5 = 0;
    hero6 = 0;
}

Tile::Tile(char l, string tileName, int m, int a, int p) // parameterized constructor
{
    letter = l;
    name = tileName;
    money = m;
    army_size = a;
    points = p;
    dragonglass = false;
    hero0 = 0;
    hero1 = 0;
    hero2 = 0;
    hero3 = 0;
    hero4 = 0;
    hero5 = 0;
    hero6 = 0;
}

string Tile::getName()
{
    return name;
}

char Tile::getLetter()
{
    return letter;
}

int Tile::getMoney()
{
    return money;
}

int Tile::getArmySize()
{
    return army_size;
}

int Tile::getPoints()
{
    return points;
}

bool Tile::getDragonglass()
{
    return dragonglass;
}

string Tile::getOwner()
{
    return owner.getName();
}
   
void Tile::setName(string tileName)
{
    name = tileName;
}

void Tile::setLetter(string l)
{
    letter = l[0];
}

void Tile::setMoney(int m)
{
    money = m;
}

void Tile::setArmySize(int a)
{
    army_size = a;
}

void Tile::setPoints(int p)
{
    points = p;
}

void Tile::setDragonglass(string glass)
{
    if (glass == "yes")
    {
        dragonglass = true;
    }
    else
    {
        dragonglass = false;
    }
}

int Tile::setOwner(Hero h1, int index)
{
    owner = h1;
    if (index == 0)
    {
        hero0++;
        return hero0;
    }
    else if (index == 1)
    {
        hero1++;
        return hero1;
    }
    else if (index == 2)
    {
        hero2++;
        return hero2;
    }
    else if (index == 3)
    {
        hero3++;
        return hero3;
    }
    else if (index == 4)
    {
        hero4++;
        return hero4;
    }
    else if (index == 5)
    {
        hero5++;
        return hero5;
    }
    else
    {
        hero6++;
        return hero6;
    }
}
   
//////// MAY NEED TO ADD ADDITIONAL FUNCTIONS WHILE WORKING THROUGH GAME MECHANICS ///////////////////////
