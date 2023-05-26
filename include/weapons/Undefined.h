#pragma once

#include "Weapon.h"
#include "WindowManager.h"

class Undefined : public Weapon{
public:
    Undefined(bool isMine);

    ~Undefined() = default;
    virtual void fight(Weapon& other) override;
    virtual void fight(Scissors& other) override;
    virtual void fight(Paper& other) override;
    virtual void fight(Rock& other) override;
    virtual void fight(Hole& other) override;
    virtual void fight(Undefined& other) override;
    virtual void fight(Flag& other) override;

    void chooseWeapon();
private:
    void initChooseBox();

    sf::RectangleShape m_ChooseBoxRect;
    sf::Sprite m_weapons_textures[3];
    sf::Text m_ChooseWeaponText;
};


