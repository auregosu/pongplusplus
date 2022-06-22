#include "Ball.hpp"

// Constructor.
Ball::Ball(float speed, sf::Color color, float width, float height, float radius)
{
    defaultPos.x = width*0.5;
    defaultPos.y = height*0.5;
    baseSpeed = speed;
    shape.setRadius(radius);
    shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);
    shape.setFillColor(color);
    shape.setPosition(defaultPos);
    speedX = baseSpeed;
}

// Get position.
sf::Vector2f Ball::getPos()
{
    return shape.getPosition();
}

// Get global bounds.
sf::FloatRect Ball::getGloBounds()
{
    return shape.getGlobalBounds();
}

// Set position.
void Ball::setPos(sf::Vector2f pos)
{
    shape.setPosition(pos);
}

// Set position to the center.
void Ball::setDefault()
{
    shape.setPosition(defaultPos);
}

// Set an offset to the position.
void Ball::move(float x, float y)
{
    shape.move(x, y);
}
