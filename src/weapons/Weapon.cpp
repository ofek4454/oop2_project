
#include "WindowManager.h"
#include "Weapon.h"
#include "Warrior.h"

void Weapon::draw() {
    auto window = WindowManager::instance().getWindow();
    window->draw(m_weapon_sprite);
}

void Weapon::moveWeapon(sf::Vector2f offset) {
    m_weapon_sprite.move(offset);
}

void Weapon::setOwner(Warrior *warrior) {
    m_warrior = warrior;
}