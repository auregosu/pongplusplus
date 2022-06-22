#include "OnlineManager.hpp"

// Constructor.
OnlineManager::OnlineManager(GameManager *_gameManager)
{
    gameManager = _gameManager;
    p1 = gameManager->p1;
    p2 = gameManager->p2;
    ball = gameManager->ball;
    ip = sf::IpAddress::getPublicAddress();
    port = 12345;
    ipStr = ip.toString();
    portStr = std::to_string(port);
}

bool OnlineManager::connect()
{
    rSocket.setBlocking(false);
    sSocket.setBlocking(false);
    rSocketRnd.setBlocking(false);
    sSocketRnd.setBlocking(false);
    rSocketP.setBlocking(false);
    sSocketP.setBlocking(false);

    if (server)
    {
        if (rSocket.bind(port) != sf::Socket::Done)
            return false;

        if (rSocketP.bind(port + 2) != sf::Socket::Done)
            return false;

        if (rSocketRnd.bind(port + 4) != sf::Socket::Done)
            return false;

        return true;
    }
    else
    {
        if (rSocket.bind(port + 1) != sf::Socket::Done)
            return false;

        if (rSocketP.bind(port + 3) != sf::Socket::Done)
            return false;

        if (rSocketRnd.bind(port + 5) != sf::Socket::Done)
            return false;

        return true;
    }
}

bool OnlineManager::confirmation()
{
    if (server)
    {
        if (rSocket.receive(cPacket, rIp, rPort) == sf::Socket::Done)
            cPacket >> confirm;
        ip = rIp;
    }
    else
    {
        confirm = true;
        cPacket << confirm;
        sSocket.send(cPacket, ip, port);
        std::cout << "Sending confirmation...\n";
    }
    return confirm;
}

void OnlineManager::receive()
{
    sf::Packet rPacket, rPacketP;

    float rPosY, rPosTailY, rExtraSpeedCount;
    float rMouse[2], rBall[2];
    bool rDirX, rPlayer;

    if (rSocket.receive(rPacket, rIp, rPort) == sf::Socket::Done)
    {
        rPacket >> rExtraSpeedCount >> rBall[0] >> rBall[1] >> rDirX >> rPlayer;
        // Ball
        if (!server)
        {
            ball->setPos(sf::Vector2f(-rBall[0] + gameManager->width, rBall[1]));
            ball->dirX = !rDirX;
            ball->player = !rPlayer;
        }

        // Everything else
        p2->extraSpeedCount = rExtraSpeedCount;
    }
    if (rSocketP.receive(rPacketP, rIp, rPort) == sf::Socket::Done)
    {
        rPacketP >> rPosY >> rPosTailY >> rMouse[0] >> rMouse[1];

        // Everything else
        p2->setPos(sf::Vector2f(p2->getPos().x, rPosY));
        p2->tail.setPosition(p2->tail.getPosition().x, rPosTailY);
        p2->mouse = sf::Vector2f(rMouse[0], rMouse[1]);
    }
}

void OnlineManager::send()
{
    sf::Packet sPacket, sPacketP;

    sPacket
        << p1->extraSpeedCount
        << ball->getPos().x
        << ball->getPos().y
        << ball->dirX
        << ball->player;

    sPacketP
        << p1->getPos().y
        << p1->tail.getPosition().y
        << p1->mouse.x
        << p1->mouse.y;

    if (server)
    {
        if (sSocket.send(sPacket, ip, port + 1) != sf::Socket::Done)
            std::cout << "Problem sending packages." << std::endl;

        if (sSocketP.send(sPacketP, ip, port + 3) != sf::Socket::Done)
            std::cout << "Problem sending packages." << std::endl;
    }
    else
    {
        if (sSocket.send(sPacket, ip, port) != sf::Socket::Done)
            std::cout << "Problem sending packages." << std::endl;

        if (sSocketP.send(sPacketP, ip, port + 2) != sf::Socket::Done)
            std::cout << "Problem sending packages." << std::endl;
    }
}

void OnlineManager::roundReceive()
{
    short int rScoreP2, rScoreP1;
    short int rRoundState;

    std::string rRoundsP2, rRoundsP1;
    sf::Packet rPacketRnd;

    if (rSocketRnd.receive(rPacketRnd, rIp, rPort) == sf::Socket::Done)
    {
        rPacketRnd >> rRoundState >> rScoreP2 >> rRoundsP2 >> rScoreP1 >> rRoundsP1;

        if (!server)
        {
            p1->score = rScoreP1;
            p2->score = rScoreP2;
            p1->rounds = rRoundsP1;
            p2->rounds = rRoundsP2;
        }
        if (rRoundState != -1)
        {
            gameManager->round = rRoundState;
        }
    }
}

void OnlineManager::roundSend()
{
    sf::Packet sPacketRnd;

    sPacketRnd
        << gameManager->round
        << p1->score
        << p1->rounds
        << p2->score
        << p2->rounds;

    if (server)
    {
        if (sSocketRnd.send(sPacketRnd, ip, port + 5) != sf::Socket::Done)
            std::cout << "Problem sending packages." << std::endl;
    }
    else
    {
        if (sSocketRnd.send(sPacketRnd, ip, port + 4) != sf::Socket::Done)
            std::cout << "Problem sending packages." << std::endl;
    }
}

void OnlineManager::exitGame()
{
    short int exitRound = 4;

    rSocket.setBlocking(false);
    sSocket.setBlocking(false);
    rSocketRnd.setBlocking(false);
    sSocketRnd.setBlocking(false);
    rSocketP.setBlocking(false);
    sSocketP.setBlocking(false);

    gameManager->round = 4;

    std::cout << "Exiting online game.\n";

    roundSend();

    confirm = false;
}

void OnlineManager::scoreCounting(Player* p)
{
    p->score++;
    ball->setDefault();
    ball->speedY = 0;
    gameManager->round = 0;
    if (!gameManager->vsCPU)
        roundSend();
}

void OnlineManager::ballCheck(sf::Text* congrats)
{
    sf::Vector2f ballPos(ball->getPos());
    if (ballPos.y < 0 || ballPos.y > gameManager->height)
    {
        if (ballPos.x > p2->getPos().x + 25)
            scoreCounting(p1);
        else if (ballPos.x < p1->getPos().x - 25)
            scoreCounting(p2);
        else if (ballPos.x < gameManager->width * 0.5f && !ball->player)
            scoreCounting(p1);
        else if (ballPos.x > gameManager->width * 0.5f && ball->player)
            scoreCounting(p2);
        else if (ball->player)
            scoreCounting(p2);
        else
            scoreCounting(p1);
        if (p1->score > p2->score)
            ball->dirX = true;
        else
            ball->dirX = false;
        gameManager->scoreCheck(congrats);
    }
    else if (ballPos.x < 0 || ballPos.x > gameManager->width)
    {
        if (ballPos.x < 0)
            scoreCounting(p2);
        else
            scoreCounting(p1);
        if (p1->score > p2->score)
            ball->dirX = true;
        else
            ball->dirX = false;
        gameManager->scoreCheck(congrats);
    }
}

