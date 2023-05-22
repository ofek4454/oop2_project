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
    virtual void fight(const Weapon& other) override {}
};


