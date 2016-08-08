#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "config.h"

class Wall
{
    public:
        Wall();
        void draw(sf::RenderWindow&);
        const std::vector<sf::Vector2f>& getWalls();
    private:
        void buildStraightWall(int,int,const int,bool); ///draw horizontal or vertical wall
        bool isWallConflict(const sf::Vector2f&); ///check if 2 walls is in the same place ( thats a waste of resources if it returns true )
        static const int wallQuantity = ((WINDOW_HEIGHT/GAMEOBJECT_WIDTH)+(WINDOW_WIDTH/GAMEOBJECT_WIDTH))*2;
        std::vector<sf::Vector2f> walls;
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif // WALL_H
