
#include "Undefined.h"
#include "Warrior.h"
#include "EventLoop.h"

Undefined::Undefined() : Weapon("U")  {
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(0, 0, WEP_WIDTH, WEP_HEIGHT));
    m_weapon_sprite.setOrigin(m_weapon_sprite.getGlobalBounds().width / 2,m_weapon_sprite.getGlobalBounds().height / 2);
    m_weapon_sprite.setScale(RECT_SIZE * WEAPON_SCALE_FACTOR / m_weapon_sprite.getGlobalBounds().width,
                             RECT_SIZE * WEAPON_SCALE_FACTOR / m_weapon_sprite.getGlobalBounds().height);
    m_weaponIntRect = m_weapon_sprite.getTextureRect();
}

void Undefined::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}

void Undefined::fight(Scissors &other) {
    chooseWeapon();
}

void Undefined::fight(Paper &other) {
    chooseWeapon();
}

void Undefined::fight(Rock &other) {
    chooseWeapon();
}

void Undefined::fight(Undefined &other) {
    chooseWeapon();
}

void Undefined::fight(Hole &other) {
    EventLoop::instance().addEvent(Event(HoleFall,P2Won));
    lose();
}

void Undefined::fight(Flag &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}
