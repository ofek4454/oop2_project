#pragma once

#include "Consts.h"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "Undefined.h"
#include "Location.h"

class Flag;
class Hole;
class Weapon;

class Warrior {
public:

    Warrior(const sf::Vector2f pos,bool isMine,Location location = Location(-1,-1));

    std::unique_ptr<Weapon>* getWeapon(){return &m_weapon;}
    void draw();
    Location getLocation() const {return m_location;}
    void setLocation(Direction direction);
    void setSpriteLocation(const sf::Vector2f &offset);
    void setHighlighted(bool isHighlighted);
    void setIntRect(int counter);
    void setTextureFlag(bool isHighlighted);
    void setTextureHole(bool isHighlighted);
    void setAsFlag();
    void setAsHole();
    bool canMove() const {return m_canMove;}
    void setWeapon(Weapons_t weapon, Weapon &otherToFight);

private:
    Location m_location;
    std::unique_ptr<Weapon> m_weapon;
    sf::Sprite m_sprite;
    sf::IntRect m_initialIntRect;
    bool m_canMove = true;
};
