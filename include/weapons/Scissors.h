#pragma once

#include "Weapon.h"
#include "Event.h"
#include "EventLoop.h"

class Scissors : public Weapon{
public:
    Scissors();
    ~Scissors() = default;
    virtual bool fight(Weapon& other) override {}
    virtual bool fight(Scissors& other) override;
    virtual bool fight(Paper& other) override;
    virtual bool fight(Rock& other) override;
    virtual bool fight(Hole& other) override;
    virtual bool fight(Flag& other) override;
    virtual bool fight(Undefined& other) override {}



    sf::Sprite* getSprite() {return &m_weapon_sprite;}
private:
    sf::Sprite m_weapon_sprite;
};


