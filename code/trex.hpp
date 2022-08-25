#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "entity.hpp"

class Trex : public Entity
{
public:
    Trex();
    void sentOrder(int);
    void update(float);
    void draw(std::shared_ptr<sf::RenderWindow>);
    void reset();

private:
    int type;     // control run or jump or shift
    int nextType; // store next type for ready
    bool state;   // control runing skin
    float gravity;
    float pastTime;
    float velocityDown;
    sf::Sprite object;
    sf::Texture jump;
    sf::Texture dead;
    std::vector<sf::Texture> run;
    std::vector<sf::Texture> shift;

    void setType();
    void updateDie();
    void updateRun(float time);
    void updateJump(float time);
    void updateShift(float time);
};

inline Trex::Trex()
{
    jump.loadFromFile("material.png", sf::IntRect(848, 2, 44, 45));
    dead.loadFromFile("material.png", sf::IntRect(1025, 2, 44, 45));
    run.resize(2);
    for (int i = 0; i < 2; i++)
        run[i].loadFromFile("material.png", sf::IntRect(936 + 44 * i, 2, 43, 45));
    shift.resize(2);
    for (int i = 0; i < 2; i++)
        shift[i].loadFromFile("material.png", sf::IntRect(1112 + 59 * i, 19, 59, 28));
    object.setPosition(0, 105);

    state = 0;
    pastTime = 0;
    type = RUN;
    nextType = JUMP;
    setHitbox(object);
}

inline void Trex::sentOrder(int order)
{
    switch (order)
    {
    case DIE:
        nextType = DIE;
        break;
    case RUN:
        nextType = RUN;
        break;
    case JUMP:
        if (type == JUMP)
            break;
        nextType = JUMP;
        break;
    case SHIFT:
        if (type == JUMP)
            gravity *= 10;
        nextType = SHIFT;
        break;
    }
}

inline void Trex::update(float time)
{
    if (type != nextType && type != JUMP)
        setType();
    switch (type)
    {
    case SHIFT:
        updateShift(time);
        break;
    case RUN:
        updateRun(time);
        break;
    case JUMP:
        updateJump(time);
        break;
    case DIE:
        updateDie();
        break;
    }
}

inline void Trex::draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(object);
    if (SHOW_HITBOX)
        drawHitbox(window);
}

inline void Trex::reset()
{
    state = 0;
    pastTime = 0;
    setType();
}

inline void Trex::setType()
{
    type = nextType;
    nextType = type == SHIFT ? SHIFT : RUN;
    switch (type)
    {
    case DIE:
        object.setTexture(dead, true);
        if (object.getPosition().y >= 105)
            object.setPosition(0, 105);
        break;
    case RUN:
        gravity = 0;
        velocityDown = 0;
        object.setTexture(run[state], true);
        object.setPosition(0, 105);
        setHitbox(object);
        break;
    case JUMP:
        velocityDown = JUMP_SPEED;
        gravity = GRAVITY;
        object.setTexture(jump, true);
        setHitbox(object);
        break;
    case SHIFT:
        object.setTexture(shift[state], true);
        object.setPosition(0, 120);
        setHitbox(object);
        break;
    }
}

inline void Trex::updateDie() {}

inline void Trex::updateShift(float time)
{
    pastTime += time;
    if (pastTime >= 1.f / 6)
    {
        pastTime -= 1.f / 6;
        state = !state;
        object.setTexture(shift[state]);
    }
}

inline void Trex::updateJump(float time)
{
    velocityDown += time * gravity;
    object.move(0, velocityDown * time);
    moveHitbox(0, velocityDown * time);
    if (object.getPosition().y >= 105 && velocityDown >= 0)
        setType();
}

inline void Trex::updateRun(float time)
{
    pastTime += time;
    if (pastTime >= 1.f / 6)
    {
        pastTime -= 1.f / 6;
        state = !state;
        object.setTexture(run[state]);
    }
}