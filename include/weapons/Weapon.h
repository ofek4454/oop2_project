#pragma once
#include "ResourcesManager.h"

class Weapon {
public:
    Weapon() = default;
    ~Weapon() = default;
    void draw();
    virtual void fight(const Weapon& other) = 0;
    void setSpriteLoc(sf::Vector2f pos) {m_weapon_sprite.setPosition(pos);}
protected:
    sf::Sprite m_weapon_sprite;
};


