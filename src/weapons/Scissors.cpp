//
// Created by Bar Kobi on 21/05/2023.
//

#include "Scissors.h"
#include "Rock.h"
#include "Paper.h"
#include "Hole.h"
#include "Flag.h"
#include "Undefined.h"

Scissors::Scissors(){
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 0, 55, 58));

}

void Scissors::fight(Scissors& other) {
    Event event(FightSS);
    EventLoop::instance().addEvent(event);
    // TODO make Undefined
}

void Scissors::fight(Paper& other) {
    Event event(FightPS, P1Won);
    EventLoop::instance().addEvent(event);
    other.lose();
}

void Scissors::fight(Rock& other) {
    Event event(FightRS, P2Won);
    EventLoop::instance().addEvent(event);
    lose();
}

void Scissors::fight(Hole& other) {
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