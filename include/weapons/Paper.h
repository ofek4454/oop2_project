#pragma once

#include "Weapon.h"

class Paper : public Weapon{
public:
    Paper();
    ~Paper() = default;
    virtual bool fight(Weapon& other) override {}
    virtual bool fight(Scissors& other) override {}
    virtual bool fight(Paper& other) override {}
    virtual bool fight(Rock& other) override {}
    virtual bool fight(Hole& other) override {}
    virtual bool fight(Undefined& other) override {}
    virtual bool fight(Flag& other) override {}
private:
    sf::Sprite m_weapon_sprite;
};

