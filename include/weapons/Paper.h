#pragma once

#include "Weapon.h"

class Paper : public Weapon{
public:
    Paper();
    ~Paper() = default;
    virtual void fight(const Weapon& other) override {}
private:
    sf::Sprite m_weapon_sprite;
};


