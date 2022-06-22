#include "Constants.hpp"

Palette::Palette()
{
    Void = sf::Color(0x323748ff);
    P1 = sf::Color(0xe6436bff);
    P1Tail = sf::Color(0x7d3346ff);
    P1Highlight = sf::Color(0x9e5265ff);
    P2 = sf::Color(0x8fba80ff);
    P2Tail = sf::Color(0x496340ff);
    P2Highlight = sf::Color(0x637a5bff);
    Golden = sf::Color(0xFFC966ff);
    GoldenLight = sf::Color(0xB58224ff);
    Bounds = sf::Color(0x242836ff);
}

void Palette::exchangeColors( bool def,
    sf::RectangleShape* p1, sf::RectangleShape* p1T, sf::Text* p1S, sf::Text* p1R, 
    sf::RectangleShape* p2, sf::RectangleShape* p2T, sf::Text* p2S, sf::Text* p2R 
    )
{
    if (def)
    {
        p1->setFillColor(Palette::P1);
        p1T->setFillColor(Palette::P1Tail);
        p1S->setFillColor(Palette::P1);
        p1R->setFillColor(Palette::P1);
        p2->setFillColor(Palette::P2);
        p2T->setFillColor(Palette::P2Tail);
        p2S->setFillColor(Palette::P2);
        p2R->setFillColor(Palette::P2);
    } else
    {
        p1->setFillColor(Palette::P2);
        p1T->setFillColor(Palette::P2Tail);
        p1S->setFillColor(Palette::P2);
        p1R->setFillColor(Palette::P2);
        p2->setFillColor(Palette::P1);
        p2T->setFillColor(Palette::P1Tail);
        p2S->setFillColor(Palette::P1);
        p2R->setFillColor(Palette::P1);
    }
}
