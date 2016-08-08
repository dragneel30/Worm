#ifndef MENU_H
#define MENU_H
#include <array>
class Menu
{
    public:
        Menu();
        ~Menu();
        void draw(sf::RenderWindow&);
        void changeColorWhenHovered(); /// change the color of a text when hovered using processColorOfTextHovered()
        void changeStateWhenClicked(); /// update menu when a text if clicked
        enum state { DEFAULT, START, DIFFICULTY, SPEED, EXIT, EXITED, PAUSED, GAMEOVER, NONESTATE };
        void setMenuState(const state);
        state getMenuState();
        state getPreviousMenuState(); void setMousePosition(const sf::Vector2i&); /// setter of mousePosition
        void setScoreText(int); /// setter of score text
    protected:

    private:
        void changeQuitPosition(); /// quit text is used in paused and gameover
        bool isHovered(sf::Text&); /// check if mouse is hovering to a text
        bool processColorOfTextHovered(sf::Text&); /// check if mouse is hovering to a text using isHovered() then update the color of text

        state menuState;
        state previousMenuState;

        /// main menu
        sf::Text start;
        sf::Text difficulty;
        sf::Text speed;
        sf::Text exit;

        /// when started
        sf::Text pressanykeytostart;

        /// difficulty
        sf::Text easy;
        sf::Text hard;

        /// are you sure you want to exit the game
        sf::Text areyousureyouwanttotexit;
        sf::Text yes;
        sf::Text no;

        /// when paused
        sf::Text resume;

        /// when the game is over
        sf::Text gameover;
        sf::Text restart;


        sf::Text quit; /// when paused or game is over


        sf::Text score; /// score of game



        /// for choosing speed
        std::array<sf::Text,9> speedLevels;

        sf::Vector2i mousePosition; ///relative to window


        sf::Font defaultFont; /// default font of text
};

#endif // MENU_H
