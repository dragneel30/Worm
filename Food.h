#ifndef FOOD_H
#define FOOD_H

#include "Entity.h"

class Food : public Entity
{
    public:
        Food();
        virtual ~Food();
        void update(); ///update the food to visible or not
        void draw(sf::RenderWindow&);
        void reset();
        void setPositionsToAvoid(const std::vector<sf::Vector2f>&); ///sets the position to avoid when spawning food
    private:
        sf::Clock t;
        bool isVisible;
        std::vector<sf::Vector2f> positionsToAvoid;
};

#endif // FOOD_H
