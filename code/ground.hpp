#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class Ground
{
public:
    Ground();
    void update(float , float );
    void draw(std::shared_ptr<sf::RenderWindow>);
    void reset();

private:
    bool type;
    int speed;
    std::vector<sf::Sprite> horiz;
    std::vector<sf::Texture> terrain;
};

inline Ground::Ground()
{
    type = 0;
    speed = 240;
    terrain.resize(2);
    terrain[0].loadFromFile("material.png", sf::IntRect(2, 54, 600, 12));
    terrain[1].loadFromFile("material.png", sf::IntRect(602, 54, 1200, 12));
    horiz.push_back(sf::Sprite(terrain[0]));
    horiz.push_back(sf::Sprite(terrain[1]));
    horiz[0].setPosition(0, 138);
    horiz[1].setPosition(600, 138);
}

inline void Ground::update(float time, float level)
{
    float dx = -(time * (speed + 30 * level));
    horiz[0].move(dx, 0);
    horiz[1].move(dx, 0);
    if (horiz[type].getPosition().x <= -600)
    {
        horiz[type].setTexture(terrain[rand() % 2]);
        horiz[type].setPosition(600, 138);
        type = !type;
    }
}

inline void Ground::draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(horiz[0]);
    window->draw(horiz[1]);
}

inline void Ground::reset()
{
    type = 0;
    horiz[0].setPosition(0, 138);
    horiz[0].setTexture(terrain[0]);
    horiz[1].setPosition(600, 138);
    horiz[1].setTexture(terrain[1]);
}