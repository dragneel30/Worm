#include "include/game.h"
#include <iostream>
int main()
{/*
    std::vector<int> a;
    a.emplace_back(1);
    a.emplace_back(2);
    a.emplace_back(3);
    std::cout << a[0] << std::endl;
    std::cout << a[1] << std::endl;
    std::cout << a[2] << std::endl;*/
///1,2,3

    srand(time(nullptr));
    Game myGame;
    myGame.run();
}
