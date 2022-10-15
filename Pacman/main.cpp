#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "board.h"
#include"player.h"
#include"ghosts.h"
#include <stdexcept>
#include<fstream>
#include "BST.h"

int main()
{
    Event e;
    RenderWindow window;
    Board b;
    srand(unsigned(time(NULL)));
    bool p = true;
    bool drawReady = true;
    bool wait = true;
    int arr[37][33];
    ifstream inputFile;
    inputFile.open("Board.txt");
    if (inputFile.is_open())
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (!inputFile.eof())
                    inputFile >> arr[i][j];
            }
        }
    }
    inputFile.close();

    Sound pacmanEating, pacmanIntro, pacmanDie;
    SoundBuffer eatBuffer, introBuffer, dieBuffer;
    eatBuffer.loadFromFile("pacman_chomp.ogg");
    pacmanEating.setBuffer(eatBuffer);
    introBuffer.loadFromFile("pacmanIntro.ogg");
    pacmanIntro.setBuffer(introBuffer);
    dieBuffer.loadFromFile("pacman_death.ogg");
    pacmanDie.setBuffer(dieBuffer);

    Pacman player(27, 16, "sprite.png");
    Ghosts g1(16, 23, 0);
    Ghosts g2(5, 25, 1);
    Ghosts g3(11, 7, 2);
    Ghosts g4(1, 3, 3);


    window.create(VideoMode(1030, 1200), "Pacman Game");

    Text scoreT, readyT;
    Font scoreF;
    scoreF.loadFromFile("font.ttf");
    scoreT.setFont(scoreF);
    readyT.setFont(scoreF);
    scoreT.setCharacterSize(33);
    readyT.setCharacterSize(30);
    readyT.setString("READY");
    readyT.setPosition(30 + 30 * 14, 60 + 30 * 19);
    sf::Clock time;
    sf::Clock ghost1;
    sf::Clock ghost2;
    sf::Clock ghost3;
    sf::Clock ghost4;
    sf::Clock pcmn;

    time.restart();
    ghost1.restart();
    ghost2.restart();
    pcmn.restart();

    pacmanIntro.play();

    while (window.isOpen())
    {
        int x4 = rand() % 4;
        int x3 = rand() % 4;


        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            else if (e.key.code == Keyboard::Space)
            {
                wait = false;
                drawReady = false;
            }
            else if (e.type == Event::KeyPressed && wait == false)
            {
                switch (e.key.code)
                {
                case Keyboard::Up:
                    if (b.getType(player.getRow() - 1, player.getColumn()) != rock)
                        player.setDirection('U');
                    break;

                case Keyboard::Down:
                    if (b.getType(player.getRow() + 1, player.getColumn()) != rock)
                        player.setDirection('D');
                    break;
                case Keyboard::Right:
                    if (b.getType(player.getRow(), player.getColumn() + 1) != rock)
                        player.setDirection('R');
                    break;
                case Keyboard::Left:
                    if (b.getType(player.getRow(), player.getColumn() - 1) != rock)
                        player.setDirection('L');
                    break;
                }
            }
        }


        if (pcmn.getElapsedTime().asMilliseconds() > 150)
        {
            switch (player.getDirection())
            {
            case('U'):
            {
                player.move('U', b.getType(player.getRow() - 1, player.getColumn()));
                player.animationUp(pcmn);
                break;
            }
            case('D'):
            {
                player.move('D', b.getType(player.getRow() + 1, player.getColumn()));
                player.animationDown(pcmn);
                break;
            }
            case('L'):
            {
                player.move('L', b.getType(player.getRow(), player.getColumn() - 1));
                player.animationLeft(pcmn);
                break;
            }
            case('R'):
            {
                player.move('R', b.getType(player.getRow(), player.getColumn() + 1));
                player.animationRight(pcmn);
                break;
            }

            }
            pcmn.restart();
        }

        if (b.getType(player.getRow(), player.getColumn()) == tile_type::pellet)
        {
            b.eaten(player.getRow(), player.getColumn());
            pacmanEating.play();
            player.setScore(player.getScore() + 10);
        }
        if (b.getType(player.getRow(), player.getColumn()) == tile_type::power)
        {
            b.eaten(player.getRow(), player.getColumn());
            pacmanEating.play();

        }

         int x1 = bfs(arr,g1.getRow(), g1.getColumn(), player.getRow(), player.getColumn());
         int x2 = bfs(arr, g2.getRow(), g2.getColumn(), player.getRow(), player.getColumn());
        // int x3 = bfs(arr, g3.getRow(), g3.getColumn(), player.getRow(), player.getColumn());
        /* int x4 = bfs(arr, g4.getRow(), g4.getColumn(), player.getRow(), player.getColumn());*/
         


        switch (x1)
        {
        case 0:
            if (b.getType(g1.getRow() - 1, g1.getColumn()) != rock && wait == false)
                g1.setDirection('U');
            break;
        case 1:
            if (b.getType(g1.getRow() + 1, g1.getColumn()) != rock && wait == false)
                g1.setDirection('D');
            break;
        case 2:
            if (b.getType(g1.getRow(), g1.getColumn() + 1) != rock && wait == false)
                g1.setDirection('R');
            break;
        case 3:
            if (b.getType(g1.getRow(), g1.getColumn() - 1) != rock && wait == false)
                g1.setDirection('L');
            break;
        }

        if (ghost1.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g1.getDirection())
            {
            case('U'):
            {
                g1.move('U', b.getType(g1.getRow() - 1, g1.getColumn()));
                break;
            }
            case('D'):
            {
                g1.move('D', b.getType(g1.getRow() + 1, g1.getColumn()));
                break;
            }
            case('L'):
            {
                g1.move('L', b.getType(g1.getRow(), g1.getColumn() - 1));
                break;
            }
            case('R'):
            {
                g1.move('R', b.getType(g1.getRow(), g1.getColumn() + 1));
                break;
            }
            }
            ghost1.restart();
        }

        switch (x2)
        {
        case 0:
            if (b.getType(g2.getRow() - 1, g2.getColumn()) != rock && wait == false)
                g2.setDirection('U');
            break;
        case 1:
            if (b.getType(g2.getRow() + 1, g2.getColumn()) != rock && wait == false)
                g2.setDirection('D');
            break;
        case 2:
            if (b.getType(g2.getRow(), g2.getColumn() + 1) != rock && wait == false)
                g2.setDirection('R');
            break;
        case 3:
            if (b.getType(g2.getRow(), g2.getColumn() - 1) != rock && wait == false)
                g2.setDirection('L');
            break;
        }

        if (ghost2.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g2.getDirection())
            {
            case('U'):
            {
                g2.move('U', b.getType(g2.getRow() - 1, g2.getColumn()));
                break;
            }
            case('D'):
            {
                g2.move('D', b.getType(g2.getRow() + 1, g2.getColumn()));
                break;
            }
            case('L'):
            {
                g2.move('L', b.getType(g2.getRow(), g2.getColumn() - 1));
                break;
            }
            case('R'):
            {
                g2.move('R', b.getType(g2.getRow(), g2.getColumn() + 1));
                break;
            }
            }
            ghost2.restart();
        }
   
        switch (x3)
        {
        case 0:
            if (b.getType(g3.getRow() - 1, g3.getColumn()) != rock && wait == false)
                g3.setDirection('U');
            break;
        case 1:
            if (b.getType(g3.getRow() + 1, g3.getColumn()) != rock && wait == false)
                g3.setDirection('D');
            break;
        case 2:
            if (b.getType(g3.getRow(), g3.getColumn() + 1) != rock && wait == false)
                g3.setDirection('R');
            break;
        case 3:
            if (b.getType(g3.getRow(), g3.getColumn() - 1) != rock && wait == false)
                g3.setDirection('L');
            break;
        }

        if (ghost3.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g3.getDirection())
            {
            case('U'):
            {
                g3.move('U', b.getType(g3.getRow() - 1, g3.getColumn()));
                break;
            }
            case('D'):
            {
                g3.move('D', b.getType(g3.getRow() + 1, g3.getColumn()));
                break;
            }
            case('L'):
            {
                g3.move('L', b.getType(g3.getRow(), g3.getColumn() - 1));
                break;
            }
            case('R'):
            {
                g3.move('R', b.getType(g3.getRow(), g3.getColumn() + 1));
                break;
            }
            }
            ghost3.restart();
        }
        switch (x4)
        {
        case 0:
            if (b.getType(g4.getRow() - 1, g4.getColumn()) != rock && wait == false)
                g4.setDirection('U');
            break;
        case 1:
            if (b.getType(g4.getRow() + 1, g4.getColumn()) != rock && wait == false)
                g4.setDirection('D');
            break;
        case 2:
            if (b.getType(g4.getRow(), g4.getColumn() + 1) != rock && wait == false)
                g4.setDirection('R');
            break;
        case 3:
            if (b.getType(g4.getRow(), g4.getColumn() - 1) != rock && wait == false)
                g4.setDirection('L');
            break;
        }

        if (ghost4.getElapsedTime().asMilliseconds() >= 250)
        {
            switch (g4.getDirection())
            {
            case('U'):
            {
                g4.move('U', b.getType(g4.getRow() - 1, g4.getColumn()));
                break;
            }
            case('D'):
            {
                g4.move('D', b.getType(g4.getRow() + 1, g4.getColumn()));
                break;
            }
            case('L'):
            {
                g4.move('L', b.getType(g4.getRow(), g4.getColumn() - 1));
                break;
            }
            case('R'):
            {
                g4.move('R', b.getType(g4.getRow(), g4.getColumn() + 1));
                break;
            }
            }
            ghost4.restart();
        }

        if (player.getShape().getGlobalBounds().intersects(g1.getShape().getGlobalBounds())|| player.getShape().getGlobalBounds().intersects(g2.getShape().getGlobalBounds())|| player.getShape().getGlobalBounds().intersects(g3.getShape().getGlobalBounds()) || player.getShape().getGlobalBounds().intersects(g4.getShape().getGlobalBounds()))
        {
            p = false;
        }

        window.clear(Color::Black);

        if (drawReady)
            window.draw(readyT);


        b.drawBoard(window);

        scoreT.setString(to_string(player.getScore()));
        window.draw(scoreT);

        if (p==false)
        {
            pacmanDie.play();
            player.respawn();
          //  g1.reset();
            wait = true;
            drawReady = true;
            p = true;
        }
        
        player.drawOnWindow(window);
        g1.drawGhost(window);
        g2.drawGhost(window);
        g3.drawGhost(window);
        g4.drawGhost(window);

        if (b.getEatenPellets() == 359)
        {

            b.displayWin(window);

        }
        if (player.getLives() == 0)
        {
            b.displayLose(window);
        }


        window.display();

    }

        
        return 0;
    }


