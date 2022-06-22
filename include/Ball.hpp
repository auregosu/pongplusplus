#ifndef BALL_H
#define BALL_H
#include "Player.hpp"

class Ball
{
public:
    sf::Vector2f defaultPos;
    bool dirX = false;
    float speedX, baseSpeed;
    float speedY;
    bool player;
    sf::CircleShape shape;

    // Constructor.
    Ball(float, sf::Color, float, float, float);

    // Get.
    sf::Vector2f getPos();
    sf::FloatRect getGloBounds();

    // Set.
    void setPos(sf::Vector2f);
    void setDefault();

    // Move.
    void move(float, float);
};

#endif // BALL_H
