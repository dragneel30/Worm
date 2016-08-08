#include "../include/Entity.h"

Entity::Entity(std::string path)
    : texture(), sprite()
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
}

Entity::~Entity()
{

}

sf::Sprite Entity::getSprite()
{
    return sprite;
}
