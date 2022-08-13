#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class ObstBase : public Entity
{
public:
    virtual void update(float , float ) = 0;
    void draw(std::shared_ptr<sf::RenderWindow>);
    bool isDelete();

protected:
    int speed;
    sf::Sprite object;
};

inline void ObstBase::draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(object);
    // drawHitbox(window);
}

inline bool ObstBase::isDelete()
{
    return object.getPosition().x <= -object.getTextureRect().width;
}

class Bird : public ObstBase
{
public:
    Bird();
    void update(float , float ) override;

private:
    bool type;
    float pastTime;
    static std::vector<int> hight;
    std::vector<sf::Texture> skins;
};

std::vector<int> Bird::hight = {50, 80, 100};

inline Bird::Bird()
{
    sf::Texture tmp;
    tmp.loadFromFile("material.png", sf::IntRect(134, 2, 46, 40));
    skins.push_back(tmp);
    tmp.loadFromFile("material.png", sf::IntRect(180, 2, 46, 40));
    skins.push_back(tmp);
    type = false;
    object.setTexture(skins[type]);
    object.setPosition(600, hight[rand() % 3]);
    setHitbox(object);
    speed = 220 + rand() % 41;
    pastTime = 0;
}

inline void Bird::update(float time, float level)
{
    pastTime += time;
    if (pastTime > 1.f / 6)
    {
        pastTime -= 1.f / 6;
        type = !type;
        object.setTexture(skins[type]);
    }
    object.move(-(time * (speed + 30 * level)), 0);
    moveHitbox(-(time * (speed + 30 * level)), 0);
}

class Cactus : public ObstBase
{
public:
    Cactus(sf::Texture &);
    void update(float , float ) override;
};

inline Cactus::Cactus(sf::Texture &texture)
{
    speed = 240;
    object.setTexture(texture);
    object.setPosition(600, 150 - object.getTextureRect().height);
    setHitbox(object);
}

inline void Cactus::update(float time, float level)
{
    object.move(-(time * (speed + 30 * level)), 0);
    moveHitbox(-(time * (speed + 30 * level)), 0);
}

class Obst
{
public:
    Obst();
    void update(float , float );
    void draw(std::shared_ptr<sf::RenderWindow>);
    void reset();
    std::pair<float, float> nearest();
    sf::FloatRect getHitbox();

private:
    int speed;
    int minLastDis;
    int maxLastDis;
    int sameObstTypeCnt;
    int maxSameTypeTimes;
    bool lastType;
    float lastDis;
    std::list<ObstBase *> obstOnStand;
    std::vector<sf::Texture> cactusSkin;
};

inline Obst::Obst()
{
    sf::Texture tmp;
    for (int i = 0; i < 4; i++)
    {
        tmp.loadFromFile("material.png", sf::IntRect(228 + 17 * i, 2, 17, 35));
        cactusSkin.push_back(tmp);
        tmp.loadFromFile("material.png", sf::IntRect(332 + 25 * i, 2, 25, 50));
        cactusSkin.push_back(tmp);
    }
    for (int i = 0; i < 3; i++)
    {
        tmp.loadFromFile("material.png", sf::IntRect(228 + 34 * i, 2, 34, 35));
        cactusSkin.push_back(tmp);
        tmp.loadFromFile("material.png", sf::IntRect(332 + 50 * i, 2, 50, 50));
        cactusSkin.push_back(tmp);
    }
    for (int i = 0; i < 2; i++)
    {
        tmp.loadFromFile("material.png", sf::IntRect(228 + 51 * i, 2, 51, 35));
        cactusSkin.push_back(tmp);
        tmp.loadFromFile("material.png", sf::IntRect(332 + 75 * i, 2, 75, 50));
        cactusSkin.push_back(tmp);
    }

    speed = 240;
    sameObstTypeCnt = 4;
    maxSameTypeTimes = 3;
    minLastDis = 300;
    maxLastDis = 600;
    lastDis = -200;
    lastType = 1;
}

inline void Obst::update(float time, float level)
{
    lastDis += (speed + 20 * level) * time;
    for (auto &&i : obstOnStand)
        i->update(time, level);
    if (obstOnStand.size() > 0 && obstOnStand.front()->isDelete())
        obstOnStand.pop_front();
    if ((lastDis > minLastDis && rand() % 300 == 0) || lastDis > maxLastDis)
    {
        bool type;
        if (sameObstTypeCnt > maxSameTypeTimes)
            type = !lastType, sameObstTypeCnt = 1;
        else
            type = rand() % 2;

        if (type == lastType)
            sameObstTypeCnt++;
        else
            sameObstTypeCnt = 1;

        switch (type)
        {
        case 0:
            obstOnStand.push_back(new Cactus(cactusSkin[rand() % cactusSkin.size()]));
            break;
        case 1:
            obstOnStand.push_back(new Bird());
            break;
        }
        lastDis = 0;
    }
}

inline void Obst::draw(std::shared_ptr<sf::RenderWindow> window)
{
    for (auto &&i : obstOnStand)
        i->draw(window);
}

inline void Obst::reset()
{
    lastDis = -200;
    lastType = 1;
    obstOnStand.clear();
}

inline sf::FloatRect Obst::getHitbox()
{
    if (obstOnStand.size())
        return obstOnStand.front()->getHitbox();
    else
        return sf::FloatRect();
}