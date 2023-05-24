//
// Created by Bar Kobi on 21/05/2023.
//

#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Paper.h"
#include "Rock.h"
#include "Undefined.h"

Hole::Hole() {
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setColor(sf::Color::Transparent);
}
