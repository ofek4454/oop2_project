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
    Warrior(const std::string id, const sf::Vector2f pos, bool isMine, Location location);
    ~Warrior() = default;
    std::unique_ptr<Weapon> *getWeapon() { return &m_weapon; }
    void draw();
    Location getLocation() const { return m_location; }
    void setLocation(Direction_t direction);
    void setSpriteLocation(const sf::Vector2f &offset, const sf::Vector2f &shadowoffset);
    void setHighlighted(bool isHighlighted);
    void setMovingIntRect(int counter, bool isEnemy = false);
    bool setHoleIntRect();
    void setTextureFlag(bool isHighlighted);
    void setTextureHole(bool isHighlighted);
    bool setAsFlag();
    std::string getId()const{return m_id;}

    void setTexture(bool reset = false);

    bool setAsHole();
    bool canMove() const { return m_canMove; }
    void setWeapon(Weapons_t weapon, bool visible = true);
    bool isNeedToBeDeleted() { return m_needToDelete; }
    void setNeedToBeDraw(bool drawable) { m_needToBeDraw = drawable; }
    bool isDrawable() { return m_needToBeDraw; }
    std::string getSymbol() const { return m_weapon->getSymbol(); }
    void lose();

private:
    const std::string m_id;
    Location m_location;
    std::unique_ptr<Weapon> m_weapon;
    sf::Texture m_throwTexture;
    sf::Sprite m_sprite;
    sf::Sprite m_shadow;
    sf::IntRect m_initialIntRect;
    sf::Texture m_initialTexture;
    bool m_isMine;
    bool m_canMove = true;
    bool m_needToDelete = false;
    bool m_needToBeDraw = true;
};
