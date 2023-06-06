//
// Created by Bar Kobi on 21/05/2023.
//

#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Paper.h"
#include "Rock.h"
#include "Undefined.h"

Hole::Hole(bool visible) : Weapon("H",visible)  {
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setColor(sf::Color::Transparent);
}

void Hole::fight(Scissors& other){
    EventLoop::instance().addEvent(Event(    CancelSwitchingTurn));
    EventLoop::instance().addEvent(Event(HoleFall,P1Won));
    other.lose();
}

void Hole::fight(Paper& other){
    EventLoop::instance().addEvent(Event(    CancelSwitchingTurn));
    EventLoop::instance().addEvent(Event(HoleFall,P1Won));
    other.lose();
}

void Hole::fight(Rock& other){
    EventLoop::instance().addEvent(Event(    CancelSwitchingTurn));
    EventLoop::instance().addEvent(Event(HoleFall,P1Won));
    other.lose();
}

void Hole::fight(Undefined& other){
    EventLoop::instance().addEvent(Event(    CancelSwitchingTurn));
    EventLoop::instance().addEvent(Event(HoleFall,P1Won));
    other.lose();
}

void Hole::fight(Weapon& other){
    if (&other == this)
        return;

    other.fight(*this);
}