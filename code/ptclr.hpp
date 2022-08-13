#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class PtClr
{
public:
    PtClr();
    void update(float );
    void draw(std::shared_ptr<sf::RenderWindow>);
    void reset();
    float getLevel();

private:
    int hiScore;
    int shineCnt;
    bool isDraw;
    float level;
    float score;
    float levelUp;
    sf::Texture HI;
    std::vector<sf::Texture> nums;
    std::vector<sf::Sprite> table;
};

inline PtClr::PtClr()
{
    nums.resize(10);
    for (int i = 0; i < 10; i++)
        nums[i].loadFromFile("material.png", sf::IntRect(655 + 10 * i, 1, 10, 12));
    HI.loadFromFile("material.png", sf::IntRect(755, 1, 20, 12));
    score = 0, hiScore = 0;

    table.resize(11);
    for (int i = 0; i < 10; i++)
        table[i].setPosition(580 - i * 12, -10);
    for (int i = 5; i < 10; i++)
        table[i].setPosition(565 - i * 12, -10);
    table[10].setPosition(420, -10);

    isDraw = true;
}

inline void PtClr::update(float time)
{
    int tmp = 0;
    score += 10 * time;

    if (shineCnt < 8)
    {
        levelUp += time;
        if (levelUp > 0)
        {
            isDraw = !isDraw;
            levelUp -= 0.3;
            shineCnt++;
        }
    }
    else
    {
        tmp = score;
        for (int i = 0; i < 5; i++)
        {
            table[i].setTexture(nums[tmp % 10]);
            tmp /= 10;
        }
    }

    tmp = level;
    if (score / 100 > tmp + 1)
    {
        shineCnt = 0;
        levelUp = 0;
    }

    level = score / 100;
}

inline void PtClr::draw(std::shared_ptr<sf::RenderWindow> window)
{
    if (isDraw)
        for (int i = 0; i < 5; i++)
            window->draw(table[i]);
    for (int i = 5; i < 11; i++)
        window->draw(table[i]);
}

inline void ::PtClr::reset()
{
    hiScore = std::max((int)score, hiScore);
    score = 0;
    int tmp = hiScore;
    for (int i = 5; i < 10; i++)
    {
        table[i].setTexture(nums[tmp % 10], true);
        tmp /= 10;
    }
    table[10].setTexture(HI);
}

inline float ::PtClr::getLevel()
{
    return level;
}