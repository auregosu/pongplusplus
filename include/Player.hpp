#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Constants.hpp"

enum yMovement{NOMOV = 0, N, S};

class Player{
public:
    short int score;
    std::string rounds = "";
    float speed, tailSpeed, extraSpeedCount, extraSpeed, extraSpeedBase = 240;
    yMovement dir;
    sf::Vector2f size, pos, posTail, mouse;
    sf::Color color, colorTail;
    sf::RectangleShape rect;
    sf::RectangleShape tail;

    //Constructors
    inline Player(){};
    
    Player(float, float, float, float, float,
           float, float, float, sf::Color, sf::Color);
    //Get.
    sf::Vector2f getPos();
    sf::FloatRect getGloBounds();

    //Set.
    void setPos(sf::Vector2f);
    void setPosX(float);
    void setPosY(float);
    void setTailPos(sf::Vector2f);
    void setTailPosX(float);
    void setTailPosY(float);

    //Move.
    void move(float, float);
    void moveTail(float, float);

    //Control.
    void movement(float height);

};

#endif // PLAYER_H
