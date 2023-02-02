#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class AgainButton
{
public:
    AgainButton();
    void draw(std::shared_ptr<sf::RenderWindow> window);
    bool isClicked(sf::Vector2i mousePos);

private:
    sf::RectangleShape button;
    sf::Texture texture;
};

inline AgainButton::AgainButton()
{
    texture.loadFromFile("material.png", sf::IntRect(2, 2, 36, 36));
    button.setTexture(&texture);
    button.setSize(sf::Vector2f(36, 36));
    button.setPosition(282, 60);
}

inline void AgainButton::draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(button);
}

inline bool AgainButton::isClicked(sf::Vector2i mousePos)
{
    if (mousePos.x >= 850 && mousePos.x <= 950 && mousePos.y >= 200 && mousePos.y <= 270)
        return true;
    return false;
}