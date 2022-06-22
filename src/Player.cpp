#include "Player.hpp"

// Constructor
Player::Player(float _sizeX, float _sizeY, float _posX, float _posY,
               float _posTailX, float _posTailY, float _speed,
               float _tailSpeed, sf::Color _color, sf::Color _colorTail)
{
    size.x = _sizeX;
    size.y = _sizeY;
    score = 0;
    pos.x = _posX;
    pos.y = _posY;
    posTail.x = _posTailX;
    posTail.y = _posTailY;
    speed = _speed;
    tailSpeed = _tailSpeed;
    color = _color;
    colorTail = _colorTail;
    rect.setSize(size);
    rect.setPosition(pos);
    rect.setFillColor(color);
    tail.setSize(sf::Vector2f(size.x * 0.5f, size.y * 0.25f));
    tail.setPosition(posTail);
    tail.setFillColor(colorTail);
}

// Get Position.
sf::Vector2f Player::getPos()
{
    return rect.getPosition();
}

// Get the global bounds.
sf::FloatRect Player::getGloBounds()
{
    return rect.getGlobalBounds();
}

// Set player's position.
void Player::setPos(sf::Vector2f vec)
{
    rect.setPosition(vec);
}

// Set tail's position.
void Player::setTailPos(sf::Vector2f vec)
{
    tail.setPosition(vec);
}

// Set an offset to the position of the player.
void Player::move(float x, float y)
{
    rect.move(x, y);
}

// Set an offset to the position of the tail.
void Player::moveTail(float x, float y)
{
    tail.move(x, y);
}

// Player control
void Player::movement(float height)
{
    switch (dir)
    {
    case N:
        if (getPos().y > 0)
        {
            moveTail(0, -tailSpeed * deltaTime.asSeconds());
            move(0, -speed * deltaTime.asSeconds());
        }
        break;
    case S:
        if (getPos().y < height - size.y)
        {
            moveTail(0, tailSpeed * deltaTime.asSeconds());
            move(0, speed * deltaTime.asSeconds());
        }
        break;
    }
}

