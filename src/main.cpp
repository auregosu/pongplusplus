#include "GUI.hpp"

int main()
{
    float width = 1280, height = 720;
    float speed = 3.f;
gameStart:
    // CREATION OF OBJECTS BOLETATION
    GameManager gameManager(width, height);

    Palette palette;

    Player p1(
        width * 0.025f, width * 0.1f,
        width * 0.0875f, height * 0.5f - width * 0.05,
        width * 0.0750, height * 0.5f - width * 0.0125,
        240*speed, 200*speed,
        Palette::P1, Palette::P1Tail); // rectangle width, rectangle height, position-halfwidth (0.1-0.0125), position-halfheight

    Player p2(
        width * 0.025f, width * 0.1f,
        width * 0.8875, height * 0.5f - width * 0.05,
        width * 0.9125, height * 0.5f - width * 0.0125,
        240*speed, 200*speed,
        Palette::P2, Palette::P2Tail);

    Ball ball(500*speed, Palette::Golden, width, height, width * 0.007);

    gameManager.init(&p1, &p2, &ball);

    OnlineManager onlineManager(&gameManager);

    sf::RenderWindow window(sf::VideoMode(width, height), "P O N G + +");

    sf::Text congrats;
    font.loadFromFile("8bitOperatorPlus-Bold.ttf");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2.f;
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    // Buttons.
    Button buttonPlay(font, "PLAY", width * 0.25f, height * 0.2f, width * 0.5f, height * 0.5f, p1.colorTail, p1.color);
    Button buttonSettings(font, "SETTINGS", width * 0.5f, height * 0.2f, width * 0.5f, height * 0.8f, p2.colorTail, p2.color);
    Button buttonApply(font, "APPLY", width * 0.25f, height * 0.2f, width * 0.5f, height * 0.8f, Palette::GoldenLight, Palette::Golden);
    Button buttonSpeed(font, std::to_string(speed), width * 0.2f, height * 0.2f, width * 0.2f, height * 0.5f, p2.colorTail, p2.color);
    Button buttonCPU(font, "CPU", width * 0.25f, height * 0.2f, width * 0.33f, height * 0.6f, p1.colorTail, p1.color);
    Button buttonLAN(font, "LAN", width * 0.25f, height * 0.2f, width * 0.66f, height * 0.6f, p2.colorTail, p2.color);
    Button buttonIP(font, onlineManager.ipStr, width * 0.25f, height * 0.2f, width * 0.5f, height * 0.6f, p1.colorTail, p1.color);
    Button buttonPort(font, onlineManager.portStr, width * 0.25f, height * 0.2f, width * 0.2f, height * 0.85f, p2.colorTail, p2.color);
    Button buttonHost(font, onlineManager.serverStr, width * 0.25f, height * 0.2f, width * 0.5f, height * 0.85f, Palette::GoldenLight, Palette::Golden);
    Button buttonConnect(font, "JOIN", width * 0.25f, height * 0.2f, width * 0.8, height * 0.85f, p2.colorTail, p2.color);

    Text title(font, "PONG++", width * 0.15f, Palette::Golden, width * 0.5f, height * 0.16f, true);
    Text connecting(font, "CONNECTING...", width * 0.1f, Palette::Golden, width * 0.5f, height * 0.5f, true);

    congrats.setFont(font);
    congrats.setCharacterSize(width * 0.1f);
    congrats.setString(gameManager.finalMessage);
    congrats.setPosition(width * 0.5f, height * 0.33);
    congrats.setColor(sf::Color::White);
    congrats.setOrigin(congrats.getLocalBounds().width * 0.5f, congrats.getLocalBounds().height * 0.5f);

    Text scoreP1Text(font, std::to_string(p1.score), width * 0.07, p1.color, width * 0.01, height * 0.5f - width * 0.0612, false);
    Text scoreP2Text(font, std::to_string(p2.score), width * 0.07, p2.color, width * 0.95, height * 0.5f - width * 0.0612, false);

    Text roundsP1Text(font, p1.rounds, width * 0.07, p1.color, 20, 0, false);
    Text roundsP2Text(font, p2.rounds, width * 0.07, p2.color, width - 75, 50, false);
    roundsP2Text.text.setScale(-1, 1);
    roundsP2Text.text.setOrigin(50.f, 50.f);

    Text rightClick(font, "RIGHT CLICK TO START", width * 0.05f, Palette::Golden, width * 0.5f, height * 0.33f, true);

    sf::RectangleShape bounds1(sf::Vector2f(width * 0.48, height));
    sf::RectangleShape bounds2(sf::Vector2f(width * 0.48, height));
    bounds2.setPosition(width * 0.52, 0);
    bounds1.setFillColor(Palette::Bounds);
    bounds2.setFillColor(Palette::Bounds);

    sf::Clock clock;
    sf::Time framerateLimit = sf::seconds(1.f / 60.f);
    float framerate;

    while (window.isOpen())
    {
        // Mouse P1 detection.
        sf::View view;
        float resizeRatio, resizeRatioX, resizeRatioY;
        sf::Vector2f halfWindowSize(width * 0.5f, height * 0.5f);
        if (window.hasFocus())
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            p1.mouse = window.mapPixelToCoords(pixelPos);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // Close window.
            case sf::Event::Closed:
                if (onlineManager.confirm)
                    onlineManager.exitGame();
                window.close();
                break;
            // Resize window.
            case sf::Event::Resized:
                resizeRatioX = width / event.size.width;
                resizeRatioY = height / event.size.height;
                if (event.size.height > event.size.width * (height / width))
                    resizeRatio = resizeRatioX;
                else
                    resizeRatio = resizeRatioY;
                std::cout << resizeRatio << std::endl;
                view = sf::View(halfWindowSize, sf::Vector2f(event.size.width, event.size.height));
                view.zoom(resizeRatio);
                window.setView(view);
                break;
            // Key input.
            case sf::Event::KeyPressed:
                if (gameManager.game != MENU)
                {
                    switch (event.key.code)
                    {
                    case keyboard.W:
                        p1.dir = N;
                        if (gameManager.vsCPU && gameManager.round == 1)
                            p2.extraSpeedCount += p2.extraSpeedBase;
                        break;
                    case keyboard.D:
                        p1.dir = S;
                        if (gameManager.vsCPU && gameManager.round == 1)
                            p2.extraSpeedCount += p2.extraSpeedBase;
                        break;
                    case keyboard.Q:
                        if (gameManager.round == 1)
                        {
                            p1.extraSpeedCount += p1.extraSpeedBase;
                            p2.extraSpeedCount += p2.extraSpeedBase;
                        }
                        break;
                    case keyboard.Escape:
                        if (onlineManager.confirm)
                            onlineManager.exitGame();
                        else
                        {
                            gameManager.game = MENU;
                            gameManager.menu = GENERAL;
                            gameManager.round = 0;
                        }
                        p1.score = 0;
                        p2.score = 0;
                        p1.rounds = "";
                        p2.rounds = "";
                        ball.setDefault();
                        p1.setPos(p1.pos);
                        p2.setPos(p2.pos);
                        p1.setTailPos(p1.posTail);
                        p2.setTailPos(p2.posTail);
                        p1.dir = NOMOV;
                        p2.dir = NOMOV;
                        onlineManager.confirm = false;
                        title.text.setString("PONG++");
                        title.text.setCharacterSize(width * 0.15);
                        title.center();
                        break;
                    case keyboard.Space:
                        if (gameManager.round == 1 || gameManager.round == 2)
                        {
                            if (gameManager.round == 2)
                                gameManager.round = 1;
                            else
                                gameManager.round = 2;
                        }
                        break;
                    default:
                        break;
                    }
                }
                else if (event.key.control && event.key.code == sf::Keyboard::V)
                {
                    if (onlineManager.writeIp && sf::Clipboard::getString().toAnsiString().length() < 16)
                        onlineManager.ipStr = sf::Clipboard::getString().toAnsiString();
                    else if (onlineManager.writePort && sf::Clipboard::getString().toAnsiString().length() < 5)
                        onlineManager.portStr = sf::Clipboard::getString().toAnsiString();
                }
                if (event.key.code == keyboard.Down)
                {
                    std::cout << "IP: " << onlineManager.ip << std::endl;
                    std::cout << "Received IP: " << onlineManager.rIp << std::endl;
                    std::cout << "Port: " << onlineManager.port << std::endl;
                    std::cout << "Connection: " << onlineManager.serverStr << std::endl;
                }
                else if (event.key.code == keyboard.Escape)
                {
                    title.text.setString("PONG++");
                    title.text.setCharacterSize(width * 0.15);
                    title.center();
                    gameManager.menu = GENERAL;
                }
                break;
            case sf::Event::KeyReleased:
                // if (!)
                //     p1.dir = NOMOV;
                break;
                // MOUSE EVENTS.
            case sf::Event::MouseButtonPressed:
                if (window.hasFocus())
                {
                    switch (gameManager.game)
                    {
                    case MENU:
                        switch (gameManager.menu)
                        {
                        case GENERAL:
                            if (buttonPlay.getGloBounds().contains(p1.mouse))
                            {
                                title.text.setString("CHOOSE MODE");
                                title.text.setCharacterSize(width * 0.1);
                                title.center();
                                gameManager.menu = CHOOSEMODE;
                            }
                            else if (buttonSettings.getGloBounds().contains(p1.mouse))
                            {
                                title.text.setString("SETTINGS");
                                title.text.setCharacterSize(width * 0.1);
                                title.center();
                                gameManager.menu = SETTINGS;
                            }
                            break;
                        case SETTINGS:
                            if (buttonApply.getGloBounds().contains(p1.mouse))
                            {
                                goto gameStart;
                            }
                            break;
                        case CHOOSEMODE:
                            if (buttonCPU.getGloBounds().contains(p1.mouse))
                            {
                                gameManager.vsCPU = true;
                                Palette::exchangeColors(true, 
                                        &p1.rect, &p1.tail, &scoreP1Text.text, &roundsP1Text.text, 
                                        &p2.rect, &p2.tail, &scoreP2Text.text, &roundsP2Text.text
                                        );
                                gameManager.game = GAMEPLAY;
                            }

                            else if (buttonLAN.getGloBounds().contains(p1.mouse))
                            {
                                title.text.setString("ENTER IP / PORT");
                                title.text.setCharacterSize(width * 0.1);
                                title.center();
                                gameManager.vsCPU = false;
                                gameManager.menu = ONLINECONFIG;
                            }
                            break;
                        case ONLINECONFIG:
                            if (buttonIP.getGloBounds().contains(p1.mouse))
                            {
                                buttonIP.rect.setFillColor(Palette::P1Highlight);
                                buttonPort.rect.setFillColor(Palette::P2Tail);
                                onlineManager.writeIp = true;
                                onlineManager.writePort = false;
                            }
                            else if (buttonPort.getGloBounds().contains(p1.mouse))
                            {
                                buttonPort.rect.setFillColor(Palette::P2Highlight);
                                buttonIP.rect.setFillColor(Palette::P1Tail);
                                onlineManager.writePort = true;
                                onlineManager.writeIp = false;
                            }
                            else
                            {
                                buttonIP.rect.setFillColor(Palette::P1Tail);
                                buttonPort.rect.setFillColor(Palette::P2Tail);
                                onlineManager.writeIp = false;
                                onlineManager.writePort = false;
                            }
                            if (buttonHost.getGloBounds().contains(p1.mouse))
                            {
                                if (onlineManager.server)
                                {
                                    onlineManager.serverStr = "USER";
                                    onlineManager.server = false;
                                }
                                else
                                {
                                    onlineManager.serverStr = "HOST";
                                    onlineManager.server = true;
                                }
                            }
                            if (buttonConnect.getGloBounds().contains(p1.mouse) &&
                                onlineManager.ip != "0.0.0.0" && onlineManager.port != 0)
                            {
                                if (!onlineManager.server)
                                    Palette::exchangeColors(false, 
                                            &p1.rect, &p1.tail, &scoreP1Text.text, &roundsP1Text.text, 
                                            &p2.rect, &p2.tail, &scoreP2Text.text, &roundsP2Text.text
                                            );
                                if (onlineManager.connect())
                                    gameManager.menu = CONNECTING;
                                else
                                    std::cout << "Failed connecting.\n";
                            }
                            break;
                        }
                    }
                    break;
                default:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        if (gameManager.round == 0)
                        {
                            if (gameManager.vsCPU)
                                gameManager.round = 1;
                            else
                            {
                                if (!ball.dirX)
                                {
                                    gameManager.round = 1;
                                    onlineManager.roundSend();
                                }
                            }
                        }
                    }
                    break;
                }
                break;
            case sf::Event::TextEntered:
                if (gameManager.menu == ONLINECONFIG)
                {
                    if (onlineManager.writeIp)
                    {
                        char c = static_cast<char>(event.text.unicode);
                        if (event.text.unicode > 45 && event.text.unicode < 58 && onlineManager.ipStr.length() < 15)
                            onlineManager.ipStr.push_back(c);
                        else if (event.text.unicode == 8 && onlineManager.ipStr.length() > 0)
                            onlineManager.ipStr.erase(onlineManager.ipStr.length() - 1, 1);
                        else if (event.text.unicode == 13 && onlineManager.ipStr.length() > 0)
                        {
                            buttonIP.rect.setFillColor(Palette::P1Tail);
                            onlineManager.writeIp = false;
                            onlineManager.ip = onlineManager.ipStr;
                        }
                    }
                    if (onlineManager.writePort)
                    {
                        int portInt;
                        char c = static_cast<char>(event.text.unicode);
                        if (event.text.unicode > 45 && event.text.unicode < 58 && onlineManager.portStr.length() < 5)
                            onlineManager.portStr.push_back(c);
                        else if (event.text.unicode == 8 && onlineManager.portStr.length() > 0)
                            onlineManager.portStr.erase(onlineManager.portStr.length() - 1, 1);
                        else if (event.text.unicode == 13 && onlineManager.portStr.length() > 0)
                        {
                            buttonPort.rect.setFillColor(Palette::P2Tail);
                            onlineManager.writePort = false;
                            portInt = std::stoi(onlineManager.portStr);
                            onlineManager.portShort = (unsigned short)portInt;
                            onlineManager.port = onlineManager.portShort;
                        }
                    }
                }
                break;
            }
        }

        window.clear(Palette::Void);

        switch (gameManager.game)
        {
        case MENU:
            switch (gameManager.menu)
            {
            case GENERAL:
                window.draw(buttonPlay.rect);
                window.draw(buttonPlay.text);
                window.draw(buttonSettings.rect);
                window.draw(buttonSettings.text);
                window.draw(title.text);
                break;
            case SETTINGS:
                window.draw(buttonApply.rect);
                window.draw(buttonApply.text);
                window.draw(buttonSpeed.rect);
                window.draw(buttonSpeed.text);
                window.draw(title.text);
                break;
            case CHOOSEMODE:
                window.draw(buttonCPU.rect);
                window.draw(buttonCPU.text);
                window.draw(buttonLAN.rect);
                window.draw(buttonLAN.text);
                window.draw(title.text);
                break;
            case ONLINECONFIG:
                // IP text entry.
                buttonIP.rect.setSize(sf::Vector2f(buttonIP.charSize / 1.8 * (onlineManager.ipStr.length() + 2), buttonIP.rect.getSize().y));
                buttonIP.text.setString(onlineManager.ipStr);
                buttonIP.center();
                window.draw(buttonIP.rect);
                window.draw(buttonIP.text);
                // Port text entry.
                buttonPort.rect.setSize(sf::Vector2f(buttonIP.charSize / 1.8 * (onlineManager.portStr.length() + 2), buttonIP.rect.getSize().y));
                buttonPort.text.setString(onlineManager.portStr);
                buttonPort.center();
                window.draw(buttonPort.rect);
                window.draw(buttonPort.text);
                // Host button.
                buttonHost.text.setString(onlineManager.serverStr);
                buttonHost.center();
                window.draw(buttonHost.rect);
                window.draw(buttonHost.text);
                // Join button.
                buttonConnect.center();
                window.draw(buttonConnect.rect);
                window.draw(buttonConnect.text);
                window.draw(title.text);
                break;
            case CONNECTING:
                window.draw(connecting.text);
                if (onlineManager.confirmation())
                {
                    onlineManager.rSocket.setBlocking(true);
                    // onlineManager.rSocketRnd.setBlocking(true);
                    onlineManager.rSocketP.setBlocking(true);
                    gameManager.game = GAMEONLINE;
                }
                else
                    std::cout << "Waiting for confirmation...\n";
                break;
            }
            break;
        case GAMEPLAY:
            window.draw(bounds1);
            window.draw(bounds2);
            p2.mouse.x = width - p1.mouse.x * -1;
            p2.mouse.y = height - p1.mouse.y;
            switch (gameManager.round)
            {
            case 0:
                // Draw instructions.
                if (p1.score == 0 && p2.score == 0 && p1.rounds == "" && p2.rounds == "")
                    window.draw(rightClick.text);
                // Player movement.
                p1.movement(height);
                gameManager.movementAI(gameManager.p2);
                // Draw ball.
                window.draw(ball.shape);
                // Draw players.
                window.draw(p2.tail);
                window.draw(p1.tail);
                window.draw(p2.rect);
                window.draw(p1.rect);
                break;
            case 1:
                // Ball movement.
                gameManager.ballMovement();
                onlineManager.ballCheck(&congrats);
                // Player movement.
                p1.movement(height);
                gameManager.movementAI(gameManager.p2);
                // Check the score.
                gameManager.scoreCheck(&congrats);
                // Draw ball.
                window.draw(ball.shape);
                // Draw players;
                window.draw(p2.tail);
                window.draw(p1.tail);
                window.draw(p2.rect);
                window.draw(p1.rect);
                break;
            case 3:
                // Draw players;
                window.draw(p2.tail);
                window.draw(p1.tail);
                window.draw(p2.rect);
                window.draw(p1.rect);
                // Draw win message.
                window.draw(congrats);
                break;
            }
            // Draw Score.
            scoreP1Text.text.setString(std::to_string(p1.score));
            window.draw(scoreP1Text.text);
            scoreP2Text.text.setString(std::to_string(p2.score));
            window.draw(scoreP2Text.text);
            roundsP1Text.text.setString(p1.rounds);
            window.draw(roundsP1Text.text);
            roundsP2Text.text.setString(p2.rounds);
            window.draw(roundsP2Text.text);
            break;
        case GAMEONLINE:
            window.draw(bounds1);
            window.draw(bounds2);
            onlineManager.roundReceive();
            onlineManager.send();
            onlineManager.receive();
            switch (gameManager.round)
            {
            case 0:
                // Draw instructions.
                if (!ball.dirX)
                    window.draw(rightClick.text);
                // Player movement.
                p1.movement(height);
                p2.movement(height);
                // Draw ball.
                window.draw(ball.shape);
                // Draw players.
                window.draw(p2.tail);
                window.draw(p1.tail);
                window.draw(p2.rect);
                window.draw(p1.rect);
                break;
            case 1:
                // Ball movement.
                if (onlineManager.server)
                {
                    gameManager.ballMovement();
                    onlineManager.ballCheck(&congrats);
                }
                else
                    gameManager.ballDirCheck();
                // Player movement.
                p1.movement(height);
                p2.movement(height);
                // Check the score.
                gameManager.scoreCheck(&congrats);
                // Draw ball.
                window.draw(ball.shape);
                // Draw players;
                window.draw(p2.tail);
                window.draw(p1.tail);
                window.draw(p2.rect);
                window.draw(p1.rect);
                break;
            case 3:
                // Draw players;
                window.draw(p2.tail);
                window.draw(p1.tail);
                window.draw(p2.rect);
                window.draw(p1.rect);
                // Draw win message.
                window.draw(congrats);
                break;
            case 2:
                break;
            case 4:
                onlineManager.exitGame();
                onlineManager.send();
                gameManager.game = MENU;
                gameManager.menu = GENERAL;
                gameManager.round = 0;
                break;
            }
            // Draw Score.
            scoreP1Text.text.setString(std::to_string(p1.score));
            window.draw(scoreP1Text.text);
            scoreP2Text.text.setString(std::to_string(p2.score));
            window.draw(scoreP2Text.text);
            roundsP1Text.text.setString(p1.rounds);
            window.draw(roundsP1Text.text);
            roundsP2Text.text.setString(p2.rounds);
            window.draw(roundsP2Text.text);
            break;
        }
        window.display();
        deltaTime = clock.restart();
        framerate = 1.f / deltaTime.asSeconds();
        // std::cout << framerate << std::endl;
    }

    return 0;
}

// std::cout << "you are boleta, man!" << std::endl;
