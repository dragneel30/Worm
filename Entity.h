#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>


/// common members of food and worm

class Entity
{
    public:
        Entity(std::string);
        virtual ~Entity();
        virtual void update() = 0;
        virtual void draw(sf::RenderWindow&) = 0;
        virtual void reset() = 0;
        sf::Sprite getSprite();
    protected:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // ENTITY_H
