#include "../include/Game.h"
#include <algorithm>
#include <cstdlib>
#include "windows.h"
Food::Food()
    :Entity("assets/food.png"), t(), isVisible(true), positionsToAvoid()
{
    sprite.setTexture(texture);
}
Food::~Food()
{

}

void Food::reset()
{
    int x = 0, y = 0;
    do
    {
       x = rand() % (WINDOW_WIDTH - GAMEOBJECT_WIDTH) + GAMEOBJECT_WIDTH;
       y = rand() % (WINDOW_HEIGHT - GAMEOBJECT_HEIGHT) + GAMEOBJECT_HEIGHT;
    }while((x%GAMEOBJECT_WIDTH!=0||y%GAMEOBJECT_HEIGHT!=0)||std::find(positionsToAvoid.begin(),positionsToAvoid.end(),sf::Vector2f(x,y))!=positionsToAvoid.end());

    sprite.setPosition(sf::Vector2f(x,y));
    t.restart();
}

void Food::setPositionsToAvoid(const std::vector<sf::Vector2f>& newPositionsToAvoid)
{
    positionsToAvoid = newPositionsToAvoid;
}

void Food::update()
{
    if ( t.getElapsedTime().asSeconds() >= GAMEOBJECT_BLINKING_INTERVAL )
    {
        isVisible = !isVisible;
        t.restart();
    }
}
void Food::draw(sf::RenderWindow& window)
{
    if ( isVisible )
        window.draw(sprite);
}




