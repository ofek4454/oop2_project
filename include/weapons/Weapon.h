#pragma once
#include "ResourcesManager.h"
#include "iostream"

class Rock;
class Scissors;
class Paper;
class Undefined;
class Flag;
class Hole;
class Warrior;

class Weapon {
public:
    Weapon(const std::string symbol,bool visible = true);
    virtual ~Weapon() = default;
    virtual void draw();
    void setSpriteLoc(sf::Vector2f pos) {m_weapon_sprite.setPosition(pos);}
    void moveWeapon(sf::Vector2f offset);

    virtual void fight(Weapon& other) = 0;
    virtual void fight(Scissors& other) = 0;
    virtual void fight(Paper& other) = 0;
    virtual void fight(Rock& other) = 0;
    virtual void fight(Hole& other) = 0;
    virtual void fight(Undefined& other) = 0;
    virtual void fight(Flag& other) = 0;

    void setOwner(Warrior *warrior);
    void lose();
    void chooseWeapon();
    void initChooseBox();
    void setVisible(bool visible) {m_is_visible = visible;}
    bool isVisible() const {return m_is_visible;}
    void setWeaponIntRect(int rect) {
        m_weapon_sprite.setTextureRect(sf::IntRect(110,rect,55,58));
    }
    void removeWeaponTexture(){m_weapon_sprite.setTextureRect(sf::IntRect(0,0,0,0));}

    std::string getSymbol() const {return m_symbol;}


protected:
    sf::Sprite m_weapon_sprite;
    Warrior *m_warrior;
    sf::Sprite m_weapons_textures[3];
private:
    bool m_is_visible = true;
    sf::RectangleShape m_ChooseBoxRect;
    sf::Text m_ChooseWeaponText;
    const std::string m_symbol;
};


