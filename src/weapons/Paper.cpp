//
// Created by Bar Kobi on 21/05/2023.
//

#include "Paper.h"
#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Rock.h"
#include "Undefined.h"
#include "Warrior.h"

Paper::Paper(bool visible) : Weapon("P",visible) {
    auto weapon = ResourcesManager::instance().getTexture(PaperFlip);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(0, 169.5f, 55, 58));
    m_weapon_sprite.setScale(2.2,2.2);
    setSpriteLoc(sf::Vector2f(m_weapon_sprite.getPosition().x - m_weapon_sprite.getGlobalBounds().width * 0.125, m_weapon_sprite.getPosition().y - m_weapon_sprite.getGlobalBounds().height * 0.125));
    m_weaponIntRect = m_weapon_sprite.getTextureRect();
}

void Paper::fight(Scissors& other){
    Event event(FightPS, P2Won);
    EventLoop::instance().addEvent(event);
    lose();
}

void Paper::fight(Paper& other){
    Event event(FightPP,Tie);
    EventLoop::instance().addEvent(event);
}

void Paper::fight(Rock& other){
    Event event(FightRP, P1Won);
    EventLoop::instance().addEvent(event);
    other.lose();
}

void Paper::fight(Undefined& other){
    Event event(AttackingUndefined);
    EventLoop::instance().addEvent(event);
}

void Paper::fight(Hole& other){
    EventLoop::instance().addEvent(Event(HoleFall,P2Won));
    lose();
}

void Paper::fight(Flag& other){
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

void Paper::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}
