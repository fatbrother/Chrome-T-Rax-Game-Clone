#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
    sf::FloatRect getHitbox();
    void setHitbox(sf::Sprite &);
    void drawHitbox(std::shared_ptr<sf::RenderWindow>);
    void moveHitbox(float, float); // x: + is to right  y: + is to down
    static bool isTouch(sf::FloatRect, sf::FloatRect);

protected:
    sf::FloatRect hitbox;
};

inline sf::FloatRect Entity::getHitbox()
{
    return hitbox;
}

inline void Entity::setHitbox(sf::Sprite &object)
{
    hitbox = object.getGlobalBounds();
    hitbox.left += 10;
    hitbox.width -= 15;
    hitbox.height -= 5;
}

inline void Entity::moveHitbox(float dx, float dy)
{
    hitbox.left += dx;
    hitbox.top += dy;
}

inline void Entity::drawHitbox(std::shared_ptr<sf::RenderWindow> window)
{
    sf::Vertex point1(sf::Vector2f(hitbox.left, hitbox.top + hitbox.height), sf::Color::Red);
    sf::Vertex point2(sf::Vector2f(hitbox.left, hitbox.top), sf::Color::Red);
    sf::Vertex point3(sf::Vector2f(hitbox.left + hitbox.width, hitbox.top), sf::Color::Red);
    sf::Vertex point4(sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height), sf::Color::Red);
    sf::Vertex line1[] = {point1, point2};
    sf::Vertex line2[] = {point2, point3};
    sf::Vertex line3[] = {point3, point4};
    sf::Vertex line4[] = {point1, point4};
    window->draw(line1, 2, sf::Lines);
    window->draw(line2, 2, sf::Lines);
    window->draw(line3, 2, sf::Lines);
    window->draw(line4, 2, sf::Lines);
}

inline bool Entity::isTouch(sf::FloatRect a, sf::FloatRect b)
{
    if (a.left + a.width >= b.left &&
        a.top + a.height >= b.top &&
        b.left + b.width >= a.left &&
        b.top + b.height >= a.top)
        return true;
    return false;
}