#pragma once

#include "Weapon.h"
class Undefined : public Weapon{
public:
    Undefined(bool isMine){
        if(isMine){
            int rand = std::rand() % 3;
            auto wep = Weapons_t(rand);
            if(wep == Rock_t){
                auto weapon = ResourcesManager::instance().getWarriorTexture(Rps);
                m_weapon_sprite.setTexture(*weapon);
                m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55,58));
            }
            else if(wep == Paper_t){
                auto weapon = ResourcesManager::instance().getWarriorTexture(Rps);
                m_weapon_sprite.setTexture(*weapon);
                m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
            }
            else if(wep == Scissors_t){
                auto weapon = ResourcesManager::instance().getWarriorTexture(Rps);
                m_weapon_sprite.setTexture(*weapon);
                m_weapon_sprite.setTextureRect(sf::IntRect(110, 0, 55, 58));
            }
        }


    };

    ~Undefined() = default;
    virtual bool fight(Weapon& other) override;
    virtual bool fight(Scissors& other) override {}
    virtual bool fight(Paper& other) override {}
    virtual bool fight(Rock& other) override {}
    virtual bool fight(Hole& other) override {}
    virtual bool fight(Undefined& other) override {std::cout << "Undefined fight" << std::endl; return false;}
    virtual bool fight(Flag& other) override {}

};


