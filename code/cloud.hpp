#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class Cloud
{
public:
    Cloud();
    void update(float, float);
    void draw(std::shared_ptr<sf::RenderWindow>);

private:
    int speed;
    int lastCloud;
    sf::Texture cloudPaint;
    std::vector<sf::Sprite> clouds;
};

inline Cloud::Cloud()
{
    cloudPaint.loadFromFile("material.png", sf::IntRect(86, 2, 46, 14));
    clouds.push_back(sf::Sprite(cloudPaint));
    clouds.back().setPosition(610, 20 + rand() % 50);
    int last = 600;
    for (int i = 1; i < 5; i++)
    {
        clouds.push_back(sf::Sprite(cloudPaint));
        last += rand() % 300;
        clouds.back().setPosition(last, 20 + rand() % 50);
    }
    speed = 60;
    lastCloud = 4;
}

inline void Cloud::update(float time, float level)
{
    for (int i = 0; i < 5; i++)
    {
        clouds[i].move(-(time * (speed + 30 * level)), 0);
        if (clouds[i].getPosition().x < -46)
        {
            float lastSite = clouds[lastCloud].getPosition().x;
            clouds[i].setPosition(lastSite + 100 + rand() % 300, 20 + rand() % 50);
            lastCloud = i;
        }
    }
}

inline void Cloud::draw(std::shared_ptr<sf::RenderWindow> window)
{

    for (int i = 0; i < 5; i++)
        window->draw(clouds[i]);
}