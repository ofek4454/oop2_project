#pragma once

#include "Weapon.h"
class Scissors : public Weapon{
public:
    Scissors();
    ~Scissors() = default;
    virtual void fight(const Weapon& other) override {}

    sf::Sprite* getSprite() {return &m_weapon_sprite;}
private:
    sf::Sprite m_weapon_sprite;
};


