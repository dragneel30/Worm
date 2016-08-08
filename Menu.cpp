#include "../include/Game.h"
#include <sstream>
#include <ostream>
const sf::Vector2f middleScreen = sf::Vector2f(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);

std::string intToStr(int v)
{
    std::stringstream stream;
    stream << v;
    return stream.str();
}

int strToInt(std::string v)
{
    return atoi(v.c_str());
}

Menu::Menu()
    : menuState(DEFAULT), previousMenuState(DEFAULT), start("Start",defaultFont,DEFAULT_FONT_SIZE),
        difficulty("Difficulty",defaultFont,DEFAULT_FONT_SIZE), speed("speed",defaultFont,DEFAULT_FONT_SIZE),
            exit("exit",defaultFont,DEFAULT_FONT_SIZE), pressanykeytostart("Press any key to start",defaultFont,DEFAULT_FONT_SIZE),
                easy("easy",defaultFont,DEFAULT_FONT_SIZE), hard("hard",defaultFont,DEFAULT_FONT_SIZE),
                    areyousureyouwanttotexit("Are you sure you want to exit?",defaultFont,DEFAULT_FONT_SIZE),
                        yes("yes",defaultFont,DEFAULT_FONT_SIZE),no("no",defaultFont,DEFAULT_FONT_SIZE),
                            resume("resume",defaultFont,DEFAULT_FONT_SIZE), gameover("GAME OVER!",defaultFont,DEFAULT_FONT_SIZE),
                                restart("restart",defaultFont,DEFAULT_FONT_SIZE), quit("quit",defaultFont,DEFAULT_FONT_SIZE),
                                    score("",defaultFont,DEFAULT_FONT_SIZE), mousePosition(0,0)
{
    speedLevels.fill(sf::Text("1",defaultFont,DEFAULT_FONT_SIZE));
    defaultFont.loadFromFile("assets/arial.ttf"); ///load default font
    ///sets the positions of all text in the screen
    start.setPosition(middleScreen.x-(start.getGlobalBounds().width/2),middleScreen.y-((DEFAULT_FONT_SIZE*3)/2));
    difficulty.setPosition(middleScreen.x-(difficulty.getGlobalBounds().width/2),start.getPosition().y+DEFAULT_FONT_SIZE);
    speed.setPosition(middleScreen.x-(speed.getGlobalBounds().width/2),difficulty.getPosition().y+DEFAULT_FONT_SIZE);
    exit.setPosition(middleScreen.x-(exit.getGlobalBounds().width/2),speed.getPosition().y+DEFAULT_FONT_SIZE);
    pressanykeytostart.setPosition(middleScreen.x-(pressanykeytostart.getGlobalBounds().width/2),((middleScreen.y/2)-(DEFAULT_FONT_SIZE/2)));
    easy.setPosition(middleScreen.x-(easy.getGlobalBounds().width/2),middleScreen.y-((DEFAULT_FONT_SIZE*2)/2));
    hard.setPosition(middleScreen.x-(hard.getGlobalBounds().width/2),easy.getPosition().y+DEFAULT_FONT_SIZE);
    areyousureyouwanttotexit.setPosition(middleScreen.x-(areyousureyouwanttotexit.getGlobalBounds().width/2),middleScreen.y-((DEFAULT_FONT_SIZE*3)/2));
    yes.setPosition(middleScreen.x-(yes.getGlobalBounds().width/2),areyousureyouwanttotexit.getPosition().y+DEFAULT_FONT_SIZE);
    no.setPosition(middleScreen.x-(no.getGlobalBounds().width/2),yes.getPosition().y+DEFAULT_FONT_SIZE);
    resume.setPosition(middleScreen.x-(resume.getGlobalBounds().width/2),middleScreen.y-((DEFAULT_FONT_SIZE*2)/2));
    gameover.setPosition(middleScreen.x-(gameover.getGlobalBounds().width/2),middleScreen.y-((DEFAULT_FONT_SIZE*4)/2));
    score.setPosition(0,gameover.getPosition().y+DEFAULT_FONT_SIZE);
    restart.setPosition(middleScreen.x-(restart.getGlobalBounds().width/2),score.getPosition().y+DEFAULT_FONT_SIZE);
    quit.setPosition(middleScreen.x-(quit.getGlobalBounds().width/2),0);
    speedLevels[0].setPosition(middleScreen.x-(speedLevels[0].getGlobalBounds().width/2),middleScreen.y-((DEFAULT_FONT_SIZE*speedLevels.size())/2));

    for ( int a = 1; a < speedLevels.size(); a++ )
    {
        speedLevels[a].setString(intToStr(a+1));
        speedLevels[a].setPosition(middleScreen.x-(speedLevels[0].getGlobalBounds().width/2),speedLevels[a-1].getPosition().y+DEFAULT_FONT_SIZE);
    }
}

void Menu::setScoreText(int sc)
{
    score.setString("");
    score.setString("Score: "+intToStr(sc));
    score.setPosition((middleScreen.x-(score.getGlobalBounds().width/2)),score.getPosition().y);
}

Menu::~Menu()
{

}

Menu::state Menu::getPreviousMenuState()
{
    return previousMenuState;
}

void Menu::changeQuitPosition()
{
    sf::Vector2f newPos = quit.getPosition();
    if ( menuState == PAUSED )
    {
        newPos = sf::Vector2f(newPos.x,resume.getPosition().y+DEFAULT_FONT_SIZE);
    }
    else if ( menuState == GAMEOVER )
    {
        newPos = sf::Vector2f(newPos.x,restart.getPosition().y+DEFAULT_FONT_SIZE);
    }
    quit.setPosition(newPos);
}
void Menu::draw(sf::RenderWindow& window)
{
    if ( menuState == DEFAULT )
    {
        window.draw(start);
        window.draw(difficulty);
        window.draw(speed);
        window.draw(exit);
    }
    else if ( menuState == START )
    {
        window.draw(pressanykeytostart);
    }
    else if ( menuState == DIFFICULTY )
    {
        window.draw(easy);
        window.draw(hard);
    }
    else if ( menuState == SPEED )
    {
        for ( int a = 0; a < speedLevels.size(); a++ )
        {
            window.draw(speedLevels[a]);
        }
    }
    else if ( menuState == EXIT )
    {
        window.draw(areyousureyouwanttotexit);
        window.draw(yes);
        window.draw(no);
    }
    else if ( menuState == PAUSED )
    {
        window.draw(resume);
        window.draw(quit);
    }
    else if ( menuState == GAMEOVER )
    {
        window.draw(score);
        window.draw(gameover);
        window.draw(restart);
        window.draw(quit);
    }
}
void Menu::changeColorWhenHovered()
{
    if ( menuState == DEFAULT )
    {  /// conditional statements to avoid executing multiple functions (e.g, only 1 of them can be mousehovered)
        if ( processColorOfTextHovered(start) ) {}
        else if ( processColorOfTextHovered(difficulty) ) {}
        else if ( processColorOfTextHovered(speed) ) {}
        else if ( processColorOfTextHovered(exit) ) {}
    }
    else if ( menuState == DIFFICULTY )
    {
        if ( processColorOfTextHovered(easy) ) {}
        else if ( processColorOfTextHovered(hard) ) {}
    }
    else if ( menuState == SPEED )
    {
        for ( int a = 0; a < speedLevels.size(); a++ )
        {
            if (processColorOfTextHovered(speedLevels[a]))
            {
                break;
            }
        }
    }
    else if ( menuState == EXIT )
    {
        if ( processColorOfTextHovered(yes) ) {}
        else if ( processColorOfTextHovered(no) ) {}
    }
    else if ( menuState == PAUSED )
    {
        if ( processColorOfTextHovered(resume) ) {}
        else if ( processColorOfTextHovered(quit) ) {}
    }
    else if ( menuState == GAMEOVER )
    {
        if ( processColorOfTextHovered(restart) ) {}
        else if ( processColorOfTextHovered(quit) ) {}
    }
}
void Menu::changeStateWhenClicked()
{
    state temp = previousMenuState;
    previousMenuState = menuState;
    if ( menuState == DEFAULT )
    {
        if ( isHovered(start) )
        {
            menuState = START;
        }
        else if ( isHovered(difficulty) )
        {
            menuState = DIFFICULTY;
        }
        else if ( isHovered(speed) )
        {
            menuState = SPEED;
        }
        else if ( isHovered(exit) )
        {
            menuState = EXIT;
        }
    }
    else if ( menuState == DIFFICULTY )
    {
        if ( isHovered(easy) )
        {
            Game::setGameLevel(Game::EASY);
            menuState = DEFAULT;
        }
        else if ( isHovered(hard) )
        {
            Game::setGameLevel(Game::HARD);
            menuState = DEFAULT;
        }
    }
    else if ( menuState == SPEED )
    {
        for ( int a = 0; a < speedLevels.size(); a++ )
        {
            if(isHovered(speedLevels[a]))
            {
                Game::setGameSpeed(static_cast<Game::speed>(a));
                menuState = DEFAULT;
                break;
            }
        }
    }
    else if ( menuState == EXIT )
    {
        if ( isHovered(yes) )
        {
            menuState = EXITED;
        }
        else if ( isHovered(no) )
        {
            menuState = DEFAULT;
        }
    }
    else if ( menuState == PAUSED )
    {
        if ( isHovered(resume) )
        {
            Game::setGameState(Game::INGAME);
        }
        else if ( isHovered(quit) )
        {
            menuState = DEFAULT;
            Game::setGameState(Game::INMENU);
        }
    }
    else if ( menuState == GAMEOVER )
    {
        if ( isHovered(restart) )
        {
            menuState = START;
            Game::setGameState(Game::INMENU);
        }
        else if ( isHovered(quit) )
        {
            menuState = DEFAULT;
            Game::setGameState(Game::INMENU);
        }
    }

    if ( menuState == previousMenuState )
    {
        previousMenuState = temp;
    }
}

void Menu::setMenuState(const state newMenuState)
{
    previousMenuState = menuState;
    menuState = newMenuState;
    if ( newMenuState == PAUSED || newMenuState == GAMEOVER )
    {
        changeQuitPosition();
    }
}

Menu::state Menu::getMenuState()
{
    return menuState;
}

bool Menu::isHovered(sf::Text& txt)
{
    sf::Vector2f txtPos = txt.getPosition();
    return (mousePosition.x > txtPos.x && mousePosition.y > txtPos.y &&
            mousePosition.x < txtPos.x + txt.getGlobalBounds().width &&
            mousePosition.y < txtPos.y + txt.getGlobalBounds().height);
}

bool Menu::processColorOfTextHovered(sf::Text& txt)
{
    if ( isHovered(txt) )
    {
        txt.setColor(sf::Color::Red);
    }
    else
    {
        txt.setColor(sf::Color::White);
    }
    return 0;
}

void Menu::setMousePosition(const sf::Vector2i& newMousePos)
{
    mousePosition = newMousePos;
}



