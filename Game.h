#include "Worm.h"
#include "Menu.h"
#include "Food.h"
#include "Wall.h"

class Game
{
public:
    Game();
    void run();
    enum state{ INGAME,INMENU, NONESTATE }; /// i considered PAUSED and GAMEOVER as INMENU
    enum level{ EASY, HARD, NONELEVEL };
    enum speed{ ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };
    static void setGameLevel(const level);
    static void setGameState(const state);
    static void setGameSpeed(const speed);
    static level getGameLevel();
    static state getGameState();
    static speed getGameSpeed();
    static level gameLevel;
    static state gameState;
    static speed gameSpeed;
private:
    sf::RenderWindow gameWindow;

    void eventHandler(sf::Event);
    void update();
    void render();

    void initializeGame(); /// initialized gameobjects when the game starts
    void reinitializeGameFood(); /// boilerplate code

    Worm gameWorm;
    Menu gameMenu;
    Food gameFood;
    Wall gameWall;
};
