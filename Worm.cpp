#include "../include/Game.h"


Worm::Worm()
    : Entity("assets/snake.png")
{
    reset();
}

Worm::~Worm()
{

}

int Worm::getDefaultTailSize()
{
    return defaultTailSize;
}

void Worm::reset()
{
    tails.clear();
    headPos = sf::Vector2f(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
    tails.emplace_back(headPos);

    for ( int a = 0; a < defaultTailSize; a++ )
    {
        tails.emplace_back(tails.back().getPosition()+sf::Vector2f(GAMEOBJECT_WIDTH,0));
    }
    isDead = false;
    newDir = defaultDir;
    sprite.setPosition(headPos);
}


const std::vector<Tail>& Worm::getTails()
{
    return tails;
}

std::vector<sf::Vector2f> Worm::getSnakePosition()
{
   std::vector<sf::Vector2f> ret;
   for ( std::vector<Tail>::const_iterator iter = tails.begin(); iter != tails.end(); iter++ )
   {
       ret.emplace_back(iter->getPosition());
   }
   return ret;
}

bool Worm::getIsDead()
{
    return isDead;
}

bool Worm::isSelfCollided()
{
    std::vector<sf::Vector2f> temp = getSnakePosition();
    return (std::find(temp.begin()+1,temp.end(),headPos) != temp.end());
}

void Worm::showDead(sf::RenderWindow& window)
{
    static sf::Clock t = sf::Clock();
    static bool isVisible = false;
    if ( t.getElapsedTime().asSeconds() >= GAMEOBJECT_BLINKING_INTERVAL )
    {
        t.restart();
        isVisible = !isVisible;
    }
    if ( isVisible )
        draw(window);
}

void Worm::setNewDir(dir v)
{
    if ( v >= LEFT && v <= DOWN )
        if (((newDir == LEFT && v != RIGHT) ||
             (newDir == RIGHT && v != LEFT) ||
             (newDir == UP && v != DOWN) ||
             (newDir == DOWN && v != UP)))
            newDir = v;
}

void Worm::update()
{
    float offset = 16;
    sf::Vector2f newPosOffset = sf::Vector2f(0,0);
    if ( newDir == LEFT )
    {
        newPosOffset.x = -offset;
    }
    else if ( newDir == RIGHT )
    {
        newPosOffset.x = offset;
    }
    else if ( newDir == UP )
    {
        newPosOffset.y = -offset;
    }
    else if ( newDir == DOWN )
    {
        newPosOffset.y = offset;
    }
    processMove(headPos + newPosOffset);

}
#include <iostream>
void Worm::processMove(sf::Vector2f newHeadPos)
{
    for ( int a = tails.size()-1; a > 0; a-- )
    {
        tails[a].setPosition(tails[a-1].getPosition());
    }

    if ( Game::getGameLevel() == Game::EASY )
    {
        if ( isBoundaryCollided(sf::Vector2f(0,0),sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT)) )
        {
            if ( newHeadPos.x < 0 )
                newHeadPos.x = WINDOW_WIDTH;
            else if ( newHeadPos.y < 0 )
                newHeadPos.y = WINDOW_HEIGHT;
            else if ( newHeadPos.x > WINDOW_WIDTH )
                newHeadPos.x = -GAMEOBJECT_WIDTH;
            else if ( newHeadPos.y > WINDOW_HEIGHT )
                newHeadPos.y = -GAMEOBJECT_HEIGHT;
        }
    }

    else if ( Game::getGameLevel() == Game::HARD )
    {
        if ( isBoundaryCollided(sf::Vector2f(GAMEOBJECT_WIDTH,GAMEOBJECT_HEIGHT),sf::Vector2f(WINDOW_WIDTH-GAMEOBJECT_WIDTH,WINDOW_HEIGHT-GAMEOBJECT_HEIGHT)) )
        {
            isDead = true;
            return;
        }
    }

    headPos = newHeadPos;
    sprite.setPosition(headPos);
    tails[0].setPosition(headPos);

    if ( isSelfCollided() )
    {
        isDead = true;
    }
}


bool Worm::isBoundaryCollided(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight)
{
    return (headPos.x < topLeft.x || headPos.y < topLeft.y ||
            headPos.x > bottomRight.x || headPos.y > bottomRight.y);
}


void Worm::grow()
{
    tails.emplace_back(sf::Vector2f(tails.back().getPosition().x+16,tails.back().getPosition().y));
}


void Worm::draw(sf::RenderWindow& window)
{
    sf::Sprite spr = sf::Sprite(texture);
    for ( unsigned a = 0; a < tails.size(); a++ )
    {
        spr.setPosition(tails[a].getPosition());
        window.draw(spr);
    }
}
