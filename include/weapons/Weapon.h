#pragma once
#include "ResourcesManager.h"
#include "iostream"
class Rock;
class Scissors;
class Paper;
class Undefined;
class Flag;
class Hole;

class Weapon {
public:
    Weapon() = default;
    virtual ~Weapon() = default;
    void draw();
    void setSpriteLoc(sf::Vector2f pos) {m_weapon_sprite.setPosition(pos);}
    void moveWeapon(sf::Vector2f offset);

    virtual bool fight(Weapon& other) = 0;
    virtual bool fight(Scissors& other) = 0;
    virtual bool fight(Paper& other) = 0;
    virtual bool fight(Rock& other) = 0;
    virtual bool fight(Hole& other) = 0;
    virtual bool fight(Undefined& other) = 0;
    virtual bool fight(Flag& other) = 0;


protected:
    sf::Sprite m_weapon_sprite;
};


