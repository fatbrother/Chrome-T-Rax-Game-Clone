#include "ground.hpp"
#include "cloud.hpp"
#include "ptclr.hpp"
#include "obst.hpp"
#include "trex.hpp"

#define DIE -1
#define RUN 0
#define JUMP 1
#define SHIFT 2

class Game
{
public:
    Game();
    void run();

private:
    bool isUpdate;
    Obst obst;
    Trex trex;
    PtClr ptclr;
    Cloud cloud;
    Ground ground;
    sf::View view;
    sf::Clock clock;
    sf::Sprite gameOver;
    sf::Sprite againBotton;
    sf::Texture bottomTexture;
    sf::Texture gameOverTexture;
    std::shared_ptr<sf::RenderWindow> window;

    void draw();
    void render();
    void reset();
    void update(float);
    void FPStest(float);
    void startScene();
    void processEvents();
};

inline Game::Game()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1800, 450), "T-Rex");
    view.setCenter(300, 70);
    view.setSize(600, 200);
    window->setView(view);
    bottomTexture.loadFromFile("material.png", sf::IntRect(2, 2, 36, 36));
    againBotton.setTexture(bottomTexture);
    againBotton.setPosition(282, 60);
    gameOverTexture.loadFromFile("material.png", sf::IntRect(655, 15, 191, 11));
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(205, 40);
    isUpdate = true;
}

inline void Game::run()
{
    startScene();
    clock.restart();
    while (window->isOpen())
    {
        processEvents();
        if (isUpdate)
        {
            // std::thread t1(&Game::FPStest, this, clock.getElapsedTime().asSeconds());
            // t1.detach();
            update(clock.restart().asSeconds());
            render();
        }
    }
}

inline void Game::startScene()
{
    sf::Texture startDinoSkin;
    startDinoSkin.loadFromFile("material.png", sf::IntRect(40, 4, 44, 45));
    sf::RectangleShape curtain;
    curtain.setSize(sf::Vector2f(600, 200));
    curtain.setPosition(44, -30);
    sf::Sprite startDino(startDinoSkin);
    startDino.setPosition(0, 105);
    window->clear(sf::Color::White);
    window->draw(startDino);
    window->display();
    sf::Event event;
    bool isStart = false;
    while (window->isOpen())
    {
        while (window->pollEvent(event))
            if (event.type == sf::Event::EventType::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Space ||
                    event.key.code == sf::Keyboard::Key::Up)
                    isStart = true;
            }
            else if (event.type == sf::Event::EventType::Closed)
                window->close();
        if (isStart)
            break;
    }

    float pastTime = 0.0f;
    clock.restart();
    while (pastTime <= 1.5)
    {
        float oneFrame = clock.restart().asSeconds();
        pastTime += oneFrame;

        window->clear(sf::Color::White);
        trex.update(oneFrame);
        curtain.move(550 * oneFrame, 0);
        draw();
        window->draw(curtain);
        window->display();
    }
}

inline void Game::processEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::EventType::Closed:
            window->close();
            break;
        case sf::Event::EventType::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Key::Escape:
                window->close();
                break;
            case sf::Keyboard::Key::Space:
            case sf::Keyboard::Key::Up:
                isUpdate ? trex.sentOrder(JUMP) : reset();
                break;
            case sf::Keyboard::Key::Down:
                trex.sentOrder(SHIFT);
                break;
            default:
                break;
            }
            break;
        case sf::Event::EventType::KeyReleased:
            if (event.key.code == sf::Keyboard::Key::Down)
                trex.sentOrder(RUN);
            break;
        case sf::Event::EventType::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left && !isUpdate)
            {
                if (event.mouseButton.x < 950 &&
                    event.mouseButton.x > 850 &&
                    event.mouseButton.y < 270 &&
                    event.mouseButton.y > 205)
                    reset();
            }
        default:
            break;
        }
    }
}

inline void Game::reset()
{
    isUpdate = true;
    obst.reset();
    trex.reset();
    ptclr.reset();
    ground.reset();
    clock.restart();
}

inline void Game::update(float time)
{
    if (Entity::isTouch(trex.getHitbox(), obst.getHitbox()))
    {
        trex.sentOrder(DIE);
        isUpdate = false;
    }
    float level = ptclr.getLevel();

    std::thread threads[5] = {
        std::thread(&Cloud::update, &cloud, time, level),
        std::thread(&Obst::update, &obst, time, level),
        std::thread(&PtClr::update, &ptclr, time),
        std::thread(&Trex::update, &trex, time),
        std::thread(&Ground::update, &ground, time, level)};

    for (int i = 0; i < 5; i++)
        threads[i].join();
}

inline void Game::draw()
{
    ground.draw(window);
    cloud.draw(window);
    trex.draw(window);
    obst.draw(window);
    ptclr.draw(window);

    if (!isUpdate)
    {
        window->draw(againBotton);
        window->draw(gameOver);
    }
}

inline void Game::FPStest(float time)
{
    static float pastTime = 0;
    static int cnt = 0;
    static std::mutex mutex;

    pastTime += time, cnt++;
    if (pastTime >= 1.f)
    {
        mutex.lock();
        std::cout << cnt << std::endl;
        mutex.unlock();
        pastTime -= 1.f;
        cnt = 0;
    }
}

inline void Game::render()
{
    window->clear(sf::Color::White);
    draw();
    window->display();
}