#pragma once

#include "Consts.h"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "Undefined.h"

class Warrior {
public:

    Warrior(const sf::Vector2f &pos,bool isMine);

    sf::FloatRect getGlobalBounds() const;
    std::unique_ptr<Weapon>* getWeapon(){return &m_weapon;}
    void draw();

private:
    std::unique_ptr<Weapon> m_weapon;
    sf::Sprite m_sprite;
};
