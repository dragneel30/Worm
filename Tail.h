#ifndef TAIL_H
#define TAIL_H


#include <SFML/System/Vector2.hpp>

class Tail
{
    public:
        Tail(sf::Vector2f);
        void setPosition(sf::Vector2f newPos);
        const sf::Vector2f& getPosition() const;
    private:
        sf::Vector2f position;
};

#endif // TAIL_H
