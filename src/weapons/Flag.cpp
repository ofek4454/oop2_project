//
// Created by Bar Kobi on 21/05/2023.
//

#include "Flag.h"
#include "Scissors.h"
#include "Paper.h"
#include "Rock.h"
#include "Hole.h"
#include "Undefined.h"

Flag::Flag() {
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setColor(sf::Color::Transparent);
}

void Flag::fight(Rock &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

void Flag::fight(Paper &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

void Flag::fight(Scissors &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

void Flag::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}

void Flag::fight(Undefined &other){
    Event event(Won);
    EventLoop::instance().addEvent(event);
}
