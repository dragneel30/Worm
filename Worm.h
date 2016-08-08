#ifndef WORM_H
#define WORM_H
#include <vector>
#include "Entity.h"
#include "tail.h"

class Worm : public Entity
{
    public:
        enum dir { LEFT, RIGHT, UP, DOWN };
        Worm();
        virtual ~Worm();
        void update();
        void draw(sf::RenderWindow&);
        void reset();
        void setNewDir(dir);
        void grow();
        const std::vector<Tail>& getTails();
        std::vector<sf::Vector2f> getSnakePosition();
        bool isBoundaryCollided(const sf::Vector2f&,const sf::Vector2f&); /// check if collided to wall
        bool getIsDead();
        void showDead(sf::RenderWindow&);
        bool isSelfCollided();
        static int getDefaultTailSize();
    private:
        static const dir defaultDir = LEFT;
        static const int defaultTailSize = 10;
        dir newDir;
        std::vector<Tail> tails;
        sf::Vector2f headPos;
        void processMove(sf::Vector2f newHeadPos);
        bool isDead;
};

#endif // WORM_H
