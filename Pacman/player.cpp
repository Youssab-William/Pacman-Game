#include"player.h"

Pacman::Pacman(int initialRow, int initialColumn, string imageName)
{
    currentRow = initialRow;
    currentColumn = initialColumn;
    spriteShapeUp = IntRect(158, 0, 33, 33);
    spriteShapeDown = IntRect(222, 0, 33, 33);
    spriteShapeLeft = IntRect(127, 0, 33, 33);
    spriteShapeRight = IntRect(33, 0, 33, 33);
    shape.setPosition(30 + 30 * initialColumn, 60 + 30 * initialRow);
    texture.loadFromFile(imageName);
    shape.setTexture(texture);
    shape.setTextureRect(spriteShapeRight);
    numOfLives = 3;
    score = -10;
    highScore = 0;
}




void Pacman::move(char direction, tile_type t)
{
    if (direction == 'U' || direction == 'u')
    {
        if (t != tile_type::rock)
        {
            currentRow--;
            shape.move(0, -30);
        }
    }
    else if (direction == 'D' || direction == 'd')
    {
        if (t != tile_type::rock)
        {
            currentRow++;
            shape.move(0, 30);
        }
    }
    else if (direction == 'R' || direction == 'r')
    {
        if (t == tile_type::portalR)
        {
            shape.setPosition(30, 60 + currentRow * 30);
            currentColumn = 0;
            return;
        }
        else if (t != rock)
        {
            currentColumn++;
            shape.move(30, 0);
        }

    }
    else if (direction == 'L' || direction == 'l')
    {
        if (t == tile_type::portalL)
        {
            shape.setPosition(30 + 30 * (COLUMNS - 1), 60 + currentRow * 30);
            currentColumn = COLUMNS - 1;
            return;
        }
        else if (t != tile_type::rock)
        {
            currentColumn--;
            shape.move(-30, 0);
        }
    }
}




void Pacman::drawOnWindow(RenderWindow& window)
{
    window.draw(shape);
}




int Pacman::getRow()
{
    return currentRow;
}




int Pacman::getColumn()
{
    return currentColumn;
}




void Pacman::setDirection(char d)
{
    direction = d;
}




char Pacman::getDirection()
{
    return direction;
}




void Pacman::animationUp(Clock c)
{
    if (spriteShapeUp.left == 191)
        spriteShapeUp.left = 158;
    else
        spriteShapeUp.left += 33;

    shape.setTextureRect(spriteShapeUp);
    c.restart();
}




void Pacman::animationDown(Clock c)
{
    if (spriteShapeDown.left == 255)
        spriteShapeDown.left = 222;
    else
        spriteShapeDown.left += 33;

    c.restart();
    shape.setTextureRect(spriteShapeDown);
}




void Pacman::animationLeft(Clock c)
{
    if (spriteShapeLeft.left == 127)
        spriteShapeLeft.left = 94;
    else
        spriteShapeLeft.left += 33;

    c.restart();
    shape.setTextureRect(spriteShapeLeft);
}




void Pacman::animationRight(Clock c)
{
    if (spriteShapeRight.left == 33)
        spriteShapeRight.left = 0;
    else
        spriteShapeRight.left += 33;

    c.restart();
    shape.setTextureRect(spriteShapeRight);
}




Sprite Pacman::getShape()
{
    return shape;
}




void Pacman::respawn()
{
    shape.setPosition(30 + 30 * 16, 60 + 30 * 27);
    direction = 'u';
    currentRow = 27;
    currentColumn = 16;
    numOfLives--;
}




int Pacman::getLives()
{
    return numOfLives;
}




void Pacman::setScore(int s)
{
    score = s;
}




void Pacman::setHighScore(int hs)
{
    highScore = hs;
}




int Pacman::getScore()
{
    return score;
}




int Pacman::getHighScore()
{
    return highScore;
}
