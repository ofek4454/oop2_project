
#include "Undefined.h"
#include "Warrior.h"
#include "EventLoop.h"

Undefined::Undefined(bool isMine) : Weapon('U')  {
    if (isMine) {
        int rand = std::rand() % 3;
        auto wep = Weapons_t(rand);
        auto weapon = ResourcesManager::instance().getTexture(Rps);
        m_weapon_sprite.setTexture(*weapon);
        if (wep == Rock_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55, 58));
        else if (wep == Paper_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
        else if (wep == Scissors_t)
            m_weapon_sprite.setTextureRect(sf::IntRect(110, 0, 55, 58));
    }
}

void Undefined::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}

void Undefined::fight(Scissors &other) {
    Event event(UndefinedChoose);
    EventLoop::instance().addEvent(event);
}

void Undefined::fight(Paper &other) {
    Event event(UndefinedChoose);
    EventLoop::instance().addEvent(event);
}

void Undefined::fight(Rock &other) {
    Event event(UndefinedChoose);
    EventLoop::instance().addEvent(event);
}

void Undefined::fight(Undefined &other) { Event event(UndefinedUndefined);
    EventLoop::instance().addEvent(event); }

void Undefined::fight(Hole &other) {
    lose();
}

void Undefined::fight(Flag &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

