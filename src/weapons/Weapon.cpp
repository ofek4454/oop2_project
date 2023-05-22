//
// Created by Bar Kobi on 21/05/2023.
//
#include "WindowManager.h"
#include "Weapon.h"

void Weapon::draw() {
    auto window = WindowManager::instance().getWindow();
    window->draw(m_weapon_sprite);
}

void Weapon::moveWeapon(sf::Vector2f offset) {
    m_weapon_sprite.move(offset);
}
