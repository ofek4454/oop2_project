//
// Created by Bar Kobi on 21/05/2023.
//

#include "Paper.h"

Paper::Paper(){
    auto weapon = ResourcesManager::instance().getWarriorTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
}
