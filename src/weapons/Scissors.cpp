//
// Created by Bar Kobi on 21/05/2023.
//

#include "Scissors.h"
#include "Rock.h"
#include "Paper.h"
#include "Hole.h"
#include "Flag.h"
#include "Undefined.h"
#include "Warrior.h"

Scissors::Scissors(bool visible) : Weapon("S",visible) {
    auto weapon = ResourcesManager::instance().getTexture(ScissorsFlip);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(0, 169.5f, 55, 58));
    m_weapon_sprite.setScale(2.2,2.2);
    setSpriteLoc(sf::Vector2f(m_weapon_sprite.getPosition().x - m_weapon_sprite.getGlobalBounds().width * 0.125, m_weapon_sprite.getPosition().y - m_weapon_sprite.getGlobalBounds().height * 0.125));

    m_weaponIntRect = m_weapon_sprite.getTextureRect();

}

void Scissors::fight(Scissors& other) {
    Event event(FightSS,Tie);
    EventLoop::instance().addEvent(event);
}

void Scissors::fight(Paper& other) {
    Event event(FightPS, P1Won);
    EventLoop::instance().addEvent(event);
    other.lose();
}

void Scissors::fight(Undefined& other){
    Event event(AttackingUndefined);
    EventLoop::instance().addEvent(event);
}

void Scissors::fight(Rock& other) {
    Event event(FightRS, P2Won);
    EventLoop::instance().addEvent(event);
    lose();
}

void Scissors::fight(Hole& other) {
    EventLoop::instance().addEvent(Event(HoleFall,P2Won));
    lose();
}

void Scissors::fight(Flag& other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

void Scissors::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}