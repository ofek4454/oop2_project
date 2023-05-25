#pragma once

#include "Weapon.h"
#include "WindowManager.h"

class Undefined : public Weapon{
public:
    Undefined(bool isMine);

    ~Undefined() = default;
    virtual bool fight(Weapon& other) override;
    virtual bool fight(Scissors& other) override {}
    virtual bool fight(Paper& other) override {}
    virtual bool fight(Rock& other) override {}
    virtual bool fight(Hole& other) override {}
    virtual bool fight(Undefined& other) override {}
    virtual bool fight(Flag& other) override {}

private:
    void chooseWeapon(Weapon &other);
    void initChooseBox();

    sf::RectangleShape m_ChooseBoxRect;
    sf::Sprite m_weapons_textures[3];
    sf::Text m_ChooseWeaponText;
};


