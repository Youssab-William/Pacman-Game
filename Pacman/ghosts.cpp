#include"ghosts.h"
Ghosts::Ghosts(int initialRow, int initialColumn, int which)
{
 
    currentRow = initialRow;
    currentColumn = initialColumn;
    color = which;
        inky = IntRect(225,195, 33, 33);
        blinky = IntRect(225, 55, 33.5, 33);
        clyde = IntRect(225, 100, 33, 33);
        pinky = IntRect(225,150 , 33, 33);
    if(which==0)
        shape.setTextureRect(inky);
    else if(which==1)
        shape.setTextureRect(blinky);
    else if(which==2)
        shape.setTextureRect(pinky);
    else if(which==3)
        shape.setTextureRect(clyde);
    shape.setPosition(30 + 30 * initialColumn, 60 + 30 * initialRow);
    texture.loadFromFile("spritesheet2.png");
    shape.setTexture(texture);
  
    //shape.setSize(Vector2f(30, 30));
}




void Ghosts::drawGhost(RenderWindow& window)
{
    window.draw(shape);
}


char Ghosts::getDirection()
{
    return direction;
}




void Ghosts::setDirection(char d)
{
    direction = d;
}


void Ghosts::move(int direction, tile_type t)
{
    if (direction == 'U')
    {
        inky.left = 62 + 1 * 32.5;
        pinky.left = 62 + 1 * 32.5;
        blinky.left = 62 + 1 * 32.5;
        clyde.left = 62 + 1 * 32.5;
        if(color==0)
            shape.setTextureRect(inky);
        if (color == 1)
            shape.setTextureRect(pinky);
        if (color == 2)
            shape.setTextureRect(blinky);
        if (color == 3)
            shape.setTextureRect(clyde);

        if (t != tile_type::rock)
        {
            currentRow--;
            shape.move(0, -30);
        }
    }
    else if (direction == 'D')
    {
        inky.left = 62 + 3 * 32.5;
        pinky.left = 62 + 3 * 32.5;
        blinky.left = 62 + 3 * 32.5;
        clyde.left = 62 + 3 * 32.5;
        if (color == 0)
            shape.setTextureRect(inky);
        if (color == 1)
            shape.setTextureRect(pinky);
        if (color == 2)
            shape.setTextureRect(blinky);
        if (color == 3)
            shape.setTextureRect(clyde);
        if (t != tile_type::rock)
        {
            currentRow++;
            shape.move(0, 30);
        }
    }
    else if (direction == 'R')
    {
        inky.left = 62 + 7 * 32.5;
        pinky.left= 62 + 7 * 32.5;
        blinky.left= 62 + 7 * 32.5;
        clyde.left= 62 + 7 * 32.5;
        if (color == 0)
            shape.setTextureRect(inky);
        if (color == 1)
            shape.setTextureRect(pinky);
        if (color == 2)
            shape.setTextureRect(blinky);
        if (color == 3)
            shape.setTextureRect(clyde);
        if (t == tile_type::portalR)
        {
            shape.setPosition(30, 60 + currentRow * 30);
            currentColumn = 0;
        }

        if (t != tile_type::rock)
        {
            currentColumn++;
            shape.move(30, 0);
        }
    }
    else if (direction == 'L')
    {
       inky.left= 62 + 5 * 32.5;
       pinky.left = 62 + 5 * 32.5;
       blinky.left = 62 + 5 * 32.5;
       clyde.left = 62 + 5 * 32.5;
       if (color == 0)
           shape.setTextureRect(inky);
       if (color == 1)
           shape.setTextureRect(pinky);
       if (color == 2)
           shape.setTextureRect(blinky);
       if (color == 3)
           shape.setTextureRect(clyde);
        if (t == tile_type::portalL)
        {
            shape.setPosition(30 + 30 * (COLUMNS - 1), 60 + currentRow * 30);
            currentColumn = COLUMNS - 1;
        }
        if (t != rock)
        {
            currentColumn--;
            shape.move(-30, 0);
        }
    }
}




int Ghosts::getRow()
{
    return currentRow;
}




int Ghosts::getColumn()
{
    return currentColumn;
}

int Ghosts::get_row0()
{
    return Row0;
}
int Ghosts::get_col0()
{
    return Col0;
}

void Ghosts::reset()
{
    currentRow = 23;
    currentColumn = 16;
    shape.setPosition(30 + 30 * 23, 60 + 30 * 16);
    return;
}




Sprite Ghosts::getShape()
{
    return shape;
}
