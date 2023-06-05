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
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
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
