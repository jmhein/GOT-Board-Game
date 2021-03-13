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
using namespace std;

// Implementation file

Warrior::Warrior() // default constructor
{
    name = ""; // name blank
    strength = 0; // strength 0
    loyalty = 0; // loyalty 0
    morale = 0; // morale 0
    row = 0; // row 0
    column = 0; // column 0
    freedom = true; // not allied with a hero
    ship = false; // no ship
    dragonglass = false; // no dragonglass
    alive = true;
}

Warrior::Warrior(string warriorName, int s, int l, int m, string f, string sail, string glass, bool alive) // parameterized constructor
{
    name = warriorName; // name equals input name
    strength = s; // strength equals input strength
    loyalty = l; // loyalty = input loyalty
    morale = m; // morale = input morale
    row = 0; // start position to be randomized during game setup
    column = 0; // start position to be randomized during game setup
    alive = true;
    if (f == "yes")
    {
        freedom = true; // if warrior is not allied to a hero - freedom is true
    }
    else
    {
        freedom = false; // otherwise false
    }
    
    if (sail == "yes")
    {
        ship = true; // if warrior has a ship, ship is true
    }
    else
    {
        ship = false; // otherwise false
    }
    if (glass == "yes")
    {
        dragonglass = true; // if warrior has dragonglass, dragonglass is true
    }
    else
    {
        dragonglass = false; // otherwise false
    }
}

string Warrior::getName()
{
    return name; // return name
}

int Warrior::getStrength() 
{
    return strength; // return strength
}

int Warrior::getLoyalty()
{
    return loyalty; // return loyalty
}

int Warrior::getMorale()
{
    return morale; // return morale
}

bool Warrior::getFree()
{
    return freedom; // return freedom (T/F)
}

bool Warrior::getShip()
{
    return ship; // return ship(T/F)
}

bool Warrior::getDragonglass()
{
    return dragonglass; // return dragonglass (T/F)
}

int Warrior::getRow()
{
    return row; // return row
}

int Warrior::getColumn()
{
    return column; // return column
}

bool Warrior::isAlive()
{
    return alive;
}

void Warrior::setName(string warriorName)
{
    name = warriorName;
}


void Warrior::setStrength(int s)
{
    if (s <= maxStrength && s >= 0) // if input is within bounds
    {
        strength = s; // strength = input
    }
}

void Warrior::setLoyalty(int l)
{
    if (l <= maxLoyaltyMorale && l >= 0) // if input is within bounds
    {
        loyalty = l; // loyalty = input
    }
}

void Warrior::setMorale(int m)
{
    if (m <= maxLoyaltyMorale && m >= 0) // if morale is within bounds
    {
        morale = m; // morale = input
    }
}

void Warrior::setFree(string f)
{
    if (f == "yes")
    {
        freedom = true; // freedom = input (T/F)
    }
    else
    {
        freedom = false;
    }
}

void Warrior::setShip(string sail)
{
    if (sail == "yes")
    {
        ship = true; // ship = input (T/F)
    }
    else
    {
        ship = false;
    }
}

void Warrior::setDragonglass(string glass)
{
    if (glass == "yes")
    {
        dragonglass = true; // dragonglass = input (T/F)
    }
    else
    {
        dragonglass = false;
    }
}

void Warrior::setRow(int r)
{
    if (r <= maxRow && r >= 0) // if input is within bounds
    {
        row = r; // row = input
    }
}

void Warrior::setColumn(int c) // if input is within bounds
{
    if (c <= maxColumn && c >= 0)
    {
        column = c; // column = input
    }
}

void Warrior::setAlive(bool d)
{
    alive = d;
}
