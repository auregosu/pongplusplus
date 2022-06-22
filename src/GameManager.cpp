#include "GameManager.hpp"

GameManager::GameManager(float _width, float _height)
{
    width = _width;
    height = _height;
}

void GameManager::init(Player* _p1, Player* _p2, Ball* _ball)
{
    p1 = _p1;
    p2 = _p2;
    ball = _ball;
}

void GameManager::scoreCheck(sf::Text *congrats)
{
    // Score maximum.
    if (p1->score == 10)
    {
        p1->score = 0;
        p2->score = 0;
        p1->rounds.push_back('+');
        round = 0;
    }
    else if (p2->score == 10)
    {
        p2->score = 0;
        p1->score = 0;
        p2->rounds.push_back('+');
        round = 0;
    }
    // Full maximum.
    if (p1->rounds == "+++")
    {
        finalMessage = "P1 WINS";
        round = 3;
        congrats->setString(finalMessage);
        congrats->setColor(p1->color);
        congrats->setOrigin(congrats->getLocalBounds().width * 0.5f, congrats->getLocalBounds().height * 0.5f);
    }
    else if (p2->rounds == "+++")
    {
        finalMessage = "P2 WINS";
        round = 3;
        congrats->setString(finalMessage);
        congrats->setColor(p2->color);
        congrats->setOrigin(congrats->getLocalBounds().width * 0.5f, congrats->getLocalBounds().height * 0.5f);
    }
}

void GameManager::movementAI(Player* p)
{
    yMovement lastDir = p->dir;
    if (ball->getPos().y < p->getPos().y + (p->size.y) - 30 && ball->getPos().y > p->getPos().y + 30)
        p->dir = lastDir;
    else if (ball->getPos().y < p->getPos().y + (p->size.y * 0.5f))
        p->dir = N;
    else if (ball->getPos().y > p->getPos().y + (p->size.y * 0.5f))
        p->dir = S;
    switch (p->dir)

    {
    case N:
        if (p->getPos().y > 0)
        {
            p->moveTail(0, -p->tailSpeed * deltaTime.asSeconds());
            p->move(0, -p->speed * deltaTime.asSeconds());
        }
        break;
    case S:
        if (p->getPos().y < height - 200)
        {
            p->moveTail(0, p->tailSpeed * deltaTime.asSeconds());
            p->move(0, p->speed * deltaTime.asSeconds());
        }
        break;
    }
}

void GameManager::ballDirCheck()
{
    if (ball->dirX)
    {
        p1->extraSpeedCount = 0;
        ball->speedX = ball->baseSpeed + p1->extraSpeed;
        ball->move(ball->speedX * deltaTime.asSeconds(), 0);
    }
    else
    {
        p2->extraSpeedCount = 0;
        ball->speedX = ball->baseSpeed + p2->extraSpeed;
        ball->move(-ball->speedX * deltaTime.asSeconds(), 0);
    }
}

void GameManager::ballMovement()
{
    if (ball->getGloBounds().intersects(p1->getGloBounds()))
    {
        // X Movement.
        ball->speedX = ball->baseSpeed;
        p2->extraSpeed = 0;
        p1->extraSpeed = p1->extraSpeedCount;
        ball->player = true;
        ball->dirX = true;
        ballDirCheck();
        // Y Movement.
        float difBallMouseX = p1->mouse.x - ball->getPos().x;
        float difBallMouseY = p1->mouse.y - ball->getPos().y;
        float scaleDifSpeed = difBallMouseX / (ball->speedX * deltaTime.asSeconds());
        ball->speedY = difBallMouseY / scaleDifSpeed;
    }
    else if (ball->getGloBounds().intersects(p2->getGloBounds()))
    {
        // X Movement.
        ball->speedX = ball->baseSpeed;
        p1->extraSpeed = 0;
        p2->extraSpeed = p2->extraSpeedCount;
        ball->player = false;
        ball->dirX = false;
        ballDirCheck();
        // Y Movement.
        float difBallMouseX = p2->mouse.x - ball->getPos().x;
        float difBallMouseY = p2->mouse.y - ball->getPos().y;
        float scaleDifSpeed = difBallMouseX / (ball->speedX * deltaTime.asSeconds());
        ball->speedY = difBallMouseY / scaleDifSpeed;
    }
    else
    {
        ballDirCheck();
    }
    // Movement set.
    ball->move(0, ball->speedY);
}

