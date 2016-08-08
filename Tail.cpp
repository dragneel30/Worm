#include "../include/Tail.h"


Tail::Tail(sf::Vector2f pos)
    : position(pos)
{

}

void Tail::setPosition(sf::Vector2f newPos)
{
    position = newPos;
}

const sf::Vector2f& Tail::getPosition() const
{
    return position;
}
