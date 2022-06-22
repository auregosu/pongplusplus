#ifndef GUI_HPP
#define GUI_HPP
#include "OnlineManager.hpp"

class Text
{
    public:
        sf::Text text;
        sf::Font font;
        std::string textStr;
        int charSize;
        sf::Color color;
        int width, height;
        Text(sf::Font, std::string, int, sf::Color, int, int, bool);
        void center();
};

class Button
{
public:
    float charSize;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape rect;

    // Constructor.
    Button(sf::Font, std::string, float, float, float, float, sf::Color, sf::Color);

    sf::FloatRect getGloBounds();
    void center();
};

#endif // GUI_HPP
