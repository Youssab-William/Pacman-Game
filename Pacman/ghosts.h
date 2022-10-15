#pragma once
#include <stdio.h>
#include "board.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
using namespace sf;

class Ghosts
{
private:
    int currentRow;
    int currentColumn;
    Sprite shape;
    Texture texture;
    char direction;
    IntRect inky,pinky,clyde,blinky;
    int Row0 = 16;
    int Col0 = 23;
    int color;
public:
    Ghosts(int initialRow, int initialColumn, int which);
    void drawGhost(RenderWindow& window);
    void move(int direction, tile_type t);
    int getRow();
    int getColumn();
    char getDirection();
    void setDirection(char d);
    //void chaseAlgorithm();
    //void frightMode();
    void reset();
   Sprite getShape();
   int get_row0();
   int get_col0();
  
};



