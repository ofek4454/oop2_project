//
// Created by Bar Kobi on 21/05/2023.
//

#include "Rock.h"

Rock::Rock(){
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55,58));
}
