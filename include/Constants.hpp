#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

inline sf::Time deltaTime = sf::Time::Zero;

// Abbreviations
inline sf::Font font;
inline sf::Keyboard keyboard;

class Palette
{
public:
    inline static sf::Color Void,
            P1,
            P1Tail,
            P1Highlight,
            P2,
            P2Tail,
            P2Highlight,
            Golden,
            GoldenLight,
            Bounds;

    // Constructors
    Palette();
    static void exchangeColors( bool,
        sf::RectangleShape*, sf::RectangleShape*, sf::Text*, sf::Text*, 
        sf::RectangleShape*, sf::RectangleShape*, sf::Text*, sf::Text*
        );
};

#endif // CONSTANTS_HPP
