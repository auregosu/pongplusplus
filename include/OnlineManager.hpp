#ifndef ONLINE_MANAGER_HPP
#define ONLINE_MANAGER_HPP
#include "GameManager.hpp"

class OnlineManager
{
public:
    bool confirm = false,
         writeIp = false,
         writePort = false,
         server = true;

    unsigned short portShort,
        port = 0,
        rPort;

    sf::Packet cPacket;

    std::string ipStr = "IP ADDRESS", portStr = "PORT", serverStr = "HOST";
    sf::IpAddress ip = sf::IpAddress::None, rIp = sf::IpAddress::None;
    sf::UdpSocket sSocket, rSocket, sSocketP, rSocketP, sSocketRnd, rSocketRnd;

    Player *p1, *p2;

    Ball *ball;

    GameManager *gameManager;

    // Constructor
    OnlineManager(GameManager*);

    // Define methods
    bool connect();
    bool confirmation();
    void receive();
    void send();

    void roundReceive();
    void roundSend();

    void exitGame();

    void scoreCounting(Player*);
    void ballCheck(sf::Text*);
};
#endif // ONLINE_MANAGER_HPP
