//
// Created by Bar Kobi on 21/05/2023.
//

#include "Undefined.h"

Undefined::Undefined(bool isMine) {
    if(isMine){
        int rand = std::rand() % 3;
        auto wep = Weapons_t(rand);
        auto weapon = ResourcesManager::instance().getWarriorTexture(Rps);
        m_weapon_sprite.setTexture(*weapon);
        if(wep == Rock_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55,58));
        else if(wep == Paper_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
        else if(wep == Scissors_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 0, 55, 58));
    }
}

bool Undefined::fight(Weapon &other) {
    if (&other == this)
        return false;

    other.fight(*this);
}
