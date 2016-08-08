#include "../include/Wall.h"

Wall::Wall()
{
   texture.loadFromFile("assets/wall.png");
   sprite.setTexture(texture);

   buildStraightWall(WINDOW_WIDTH-GAMEOBJECT_WIDTH,GAMEOBJECT_WIDTH,0,true);
   buildStraightWall(WINDOW_WIDTH,GAMEOBJECT_WIDTH,WINDOW_HEIGHT-GAMEOBJECT_HEIGHT,true);
   buildStraightWall(WINDOW_HEIGHT-GAMEOBJECT_HEIGHT,GAMEOBJECT_HEIGHT,WINDOW_WIDTH-GAMEOBJECT_WIDTH,false);
   buildStraightWall(WINDOW_HEIGHT-GAMEOBJECT_HEIGHT,GAMEOBJECT_HEIGHT,0,false);

}

const std::vector<sf::Vector2f>& Wall::getWalls()
{
    return walls;
}

void Wall::buildStraightWall(int conditionVal, int updateVal,const int val,bool isHorizontal)
{
    for ( int a = 0; a < conditionVal; a+=updateVal )
    {
        sf::Vector2f pos;
        if ( isHorizontal )
        {
            pos = sf::Vector2f(a,val);
        }
        else
        {
            pos = sf::Vector2f(val,a);
        }
        if ( !isWallConflict(pos) )
        {
            walls.emplace_back(pos);
        }
    }
}



bool Wall::isWallConflict(const sf::Vector2f& pos)
{
    return (std::find(walls.begin(),walls.end(),pos) != walls.end());
}

void Wall::draw(sf::RenderWindow& window)
{
    for ( unsigned a = 0; a < walls.size(); a++ )
    {
        sprite.setPosition(sf::Vector2f(walls[a].x,walls[a].y));
        window.draw(sprite);
    }
}
