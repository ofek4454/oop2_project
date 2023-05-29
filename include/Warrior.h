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
    ~Warrior() = default;
    std::unique_ptr<Weapon>* getWeapon(){return &m_weapon;}
    void draw();
    Location getLocation() const {return m_location;}
    void setLocation(Direction_t direction);
    void setSpriteLocation(const sf::Vector2f &offset,const sf::Vector2f &shadowoffset);
    void setHighlighted(bool isHighlighted);
    void setIntRect(int counter);
    void setTextureFlag(bool isHighlighted);
    void setTextureHole(bool isHighlighted);
    void setAsFlag();
    void setAsHole();
    bool canMove() const {return m_canMove;}
    void setWeapon(Weapons_t weapon);
    bool isNeedToBeDeleted() {return m_needToDelete;}

    void lose();

private:
    Location m_location;
    Location m_prevLocation;
    std::unique_ptr<Weapon> m_weapon;
    sf::Sprite m_sprite;
    sf::Sprite m_shadow;
    sf::IntRect m_initialIntRect;
    bool m_isMine;
    bool m_canMove = true;
    bool m_needToDelete = false;
};
