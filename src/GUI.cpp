#include "GUI.hpp"

Text::Text(
    sf::Font _font, std::string _string, int _size, sf::Color _color,
    int _width, int _height, bool centered = false
    )
{
    font = _font;
    textStr = _string;
    charSize = _size;
    color = _color;
    width = _width;
    height = _height;
    text.setFont(font);
    text.setString(textStr);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(width, height);
    if (centered)
    text.setOrigin(
            Text::text.getLocalBounds().width / 2.f,
            Text::text.getLocalBounds().height / 2.f);
}
void Text::center()
{
    text.setOrigin(text.getLocalBounds().width * 0.5f, text.getLocalBounds().height * 0.5f);
}
Button::Button(
        sf::Font _font, std::string _string, float _width, float _height,
        float posX, float posY, sf::Color colorRect, sf::Color colorText
        )
{
    float offsetX = _width * 0.033f, offsetY = _height * 0.033f;

    charSize = sqrtf(_width) * 3.f;

    font = _font;

    rect.setSize(sf::Vector2f(_width, _height));
    rect.setPosition(posX, posY);
    rect.setFillColor(colorRect);
    rect.setOrigin(rect.getLocalBounds().width * 0.5f, rect.getLocalBounds().height * 0.5f);
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setPosition(posX - offsetX, posY - offsetY);
    text.setString(_string);
    text.setFillColor(colorText);
    text.setOrigin(text.getLocalBounds().width * 0.5f, text.getLocalBounds().height * 0.5f);
}
sf::FloatRect Button::getGloBounds()
{
    return rect.getGlobalBounds();
}
void Button::center()
{
    rect.setOrigin(rect.getLocalBounds().width * 0.5f, rect.getLocalBounds().height * 0.5f);
    text.setOrigin(text.getLocalBounds().width * 0.5f, text.getLocalBounds().height * 0.5f);
}
