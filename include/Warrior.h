#pragma once

#include "Consts.h"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "Undefined.h"
#include "Location.h"

class Warrior {
public:

    Warrior(const sf::Vector2f &pos,bool isMine,Location location = Location(-1,-1));

    sf::FloatRect getGlobalBounds() const;
    std::unique_ptr<Weapon>* getWeapon(){return &m_weapon;}
    void draw();
    Location getLocation() const {return m_location;}
private:
    Location m_location;
    std::unique_ptr<Weapon> m_weapon;
    sf::Sprite m_sprite;
};
