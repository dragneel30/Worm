#include "../include/game.h"

std::vector<sf::Vector2f> appendVector(const std::vector<sf::Vector2f>& a,const std::vector<sf::Vector2f>& b)
{
    std::vector<sf::Vector2f> temp = a;
    for ( std::vector<sf::Vector2f>::const_iterator iter = b.begin(); iter != b.end(); iter++ )
    {
        temp.emplace_back(*iter);
    }
    return temp;
}

Game::level Game::gameLevel = Game::EASY;
Game::state Game::gameState = Game::INMENU;
Game::speed Game::gameSpeed = Game::ONE;

void Game::setGameLevel(const level newGameLevel)
{
    gameLevel = newGameLevel;
}
void Game::setGameState(const state newGameState)
{
    gameState = newGameState;
}

void Game::setGameSpeed(const speed newGameSpeed)
{
    gameSpeed = newGameSpeed;
}

Game::level Game::getGameLevel()
{
    return gameLevel;
}

Game::state Game::getGameState()
{
    return gameState;
}

Game::speed Game::getGameSpeed()
{
    return gameSpeed;
}


Game::Game()
    : gameWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),WINDOW_TITLE), gameWorm(), gameMenu(), gameFood(),
      gameWall()
{
    gameWindow.setFramerateLimit(MAXIMUM_FPS);
}

void Game::run()
{
    while(gameWindow.isOpen())
    {
        sf::Event e;
        while(gameWindow.pollEvent(e))
        {
            eventHandler(e);
        }
        update();
        render();
    }
}


void Game::initializeGame()
{
    gameState = INGAME;
    gameMenu.setMenuState(Menu::NONESTATE);
    reinitializeGameFood();
    gameFood.reset();
    gameWorm.reset();
    /// speed*15, max of 45 fps for gamespeed.
    gameWindow.setFramerateLimit((static_cast<int>(gameSpeed)+1)*15);
}

void Game::reinitializeGameFood()
{
    if ( gameLevel == EASY )
    {
        gameFood.setPositionsToAvoid(gameWorm.getSnakePosition());
        ///avoid food to spawn in snake position
    }
    else if ( gameLevel == HARD )
    {
        gameFood.setPositionsToAvoid(appendVector(gameWorm.getSnakePosition(),gameWall.getWalls()));
        ///avoid food to spawn in snake and wall position
    }
}
#include <iostream>
void Game::eventHandler(sf::Event e)
{
    if ( e.type == sf::Event::Closed )
    {
        gameWindow.close();
    }

    if ( gameState == INMENU )
    {
        if ( gameMenu.getMenuState() == Menu::EXITED )
        {
            gameWindow.close();
        }
        gameMenu.setMousePosition(sf::Mouse::getPosition(gameWindow)); /// save the mouse position in menu
        if ( e.type == sf::Event::MouseButtonPressed )
        {
            if ( gameMenu.getMenuState() == Menu::START ) /// press any key to start
            {
                initializeGame();
            }
            if ( e.mouseButton.button == sf::Mouse::Left )
            {
                gameMenu.changeStateWhenClicked(); /// menu updater
            }
        }
        else if ( e.type == sf::Event::MouseMoved )
        {
            gameMenu.changeColorWhenHovered(); /// the text turns red when u hovered it
        }
    }
    if ( e.type == sf::Event::KeyPressed )
    {
        if ( gameState == INGAME )
        {
            switch(e.key.code)
            {
            case sf::Keyboard::Up:
                gameWorm.setNewDir(Worm::UP);
                break;
            case sf::Keyboard::Down:
                gameWorm.setNewDir(Worm::DOWN);
                break;
            case sf::Keyboard::Right:
                gameWorm.setNewDir(Worm::RIGHT);
                break;
            case sf::Keyboard::Left:
                gameWorm.setNewDir(Worm::LEFT);
                break;
            case sf::Keyboard::P: /// pause
                gameState = INMENU;
                gameMenu.setMenuState(Menu::PAUSED);
                break;
            default:
                break;
            }
        }
        else if ( gameState == INMENU )
        {
            switch(e.key.code)
            {
            case sf::Keyboard::Escape: /// go back to previous state
                if ( gameMenu.getMenuState() == Menu::PAUSED )
                {
                    gameMenu.setMenuState(Menu::NONESTATE);
                    gameState = INGAME;
                }
                else if ( gameMenu.getMenuState() != Menu::GAMEOVER )
                {
                    gameMenu.setMenuState(gameMenu.getPreviousMenuState());
                }
                break;
            default: /// press any key to start
                if ( gameMenu.getMenuState() == Menu::START )
                {
                    initializeGame();
                }
                break;
            }
        }
    }
}

void Game::update()
{
    if ( gameState == INGAME )
    {
        if ( !gameWorm.getIsDead() ) /// check if snake is still alive
        {
            gameWorm.update();
            gameFood.update();
            if ( gameWorm.getSprite().getGlobalBounds().intersects(gameFood.getSprite().getGlobalBounds()) )
            {
                /// check if snake eats food
                gameWorm.grow(); ///grow snake tail
                reinitializeGameFood(); ///set the positions to avoid
                gameFood.reset(); ///respawn food
            }
        }
        else ///set the score if snake is dead
        {
            gameState = INMENU;
            gameMenu.setMenuState(Menu::GAMEOVER);
            gameMenu.setScoreText(gameWorm.getTails().size()-gameWorm.getDefaultTailSize()-1);
        }
    }
}

void Game::render()
{
    gameWindow.clear();
    if ( gameState == INMENU ) /// draw menu objects
    {
        gameMenu.draw(gameWindow);
        if ( gameMenu.getMenuState() == Menu::GAMEOVER )
        {
            gameWorm.showDead(gameWindow);
        }
    }
    else if ( gameState == INGAME ) /// draw in-game objects
    {
        if ( gameLevel == HARD )
        {
            gameWall.draw(gameWindow);
        }
        gameWorm.draw(gameWindow);
        gameFood.draw(gameWindow);
    }
    gameWindow.display();
}
