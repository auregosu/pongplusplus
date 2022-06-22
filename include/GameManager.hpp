#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include "Ball.hpp"

enum gameState
{
    MENU,
    GAMEPLAY,
    GAMEONLINE
};

enum menuState
{
    GENERAL,
    SETTINGS,
    CHOOSEMODE,
    ONLINECONFIG,
    CONNECTING
};

class GameManager
{
public:
    float width = 1280, height = 800;

    bool vsCPU = true;

    // Round start = 0, Ongoing = 1, Pause = 2, Round finish = 3
    short int round = 0;

    gameState game = MENU;

    menuState menu = GENERAL;

    Player *p1, *p2;

    Ball* ball;

    std::string finalMessage = "change da world. Goodbye";

    // Constructor.
    GameManager() {};
    GameManager(float, float);

    void init(Player*, Player*, Ball*);

    void scoreCheck(sf::Text*);
    void movementAI(Player*);
    void ballDirCheck();
    void ballMovement(); 
};
#endif // GAME_MANAGER_HPP
