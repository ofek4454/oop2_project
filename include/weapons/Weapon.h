#pragma once
#include "ResourcesManager.h"
#include "iostream"

class Rock;
class Scissors;
class Paper;
class Undefined;
class Flag;
class Hole;
class Warrior;

class Weapon {
public:
    Weapon() = default;
    virtual ~Weapon() = default;
    virtual void draw();
    void setSpriteLoc(sf::Vector2f pos) {m_weapon_sprite.setPosition(pos);}
    void moveWeapon(sf::Vector2f offset);

    virtual void fight(Weapon& other) = 0;
    virtual void fight(Scissors& other) = 0;
    virtual void fight(Paper& other) = 0;
    virtual void fight(Rock& other) = 0;
    virtual void fight(Hole& other) = 0;
    virtual void fight(Undefined& other) = 0;
    virtual void fight(Flag& other) = 0;

    void setOwner(Warrior *warrior);
    void lose();

protected:
    sf::Sprite m_weapon_sprite;
    Warrior *m_warrior;

};


