//
// Created by Bar Kobi on 21/05/2023.
//

#include "Paper.h"
#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Rock.h"
#include "Undefined.h"

Paper::Paper(){
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 232, 55, 58));
}

bool Paper::fight(Scissors& other){
    Event event(FightScissorsPaper);
    EventLoop::instance().addEvent(event);
    lose();
}

bool Paper::fight(Paper& other){
    Event event(FightPaperPaper);
    EventLoop::instance().addEvent(event);
}

bool Paper::fight(Rock& other){
    Event event(FightRockPaper);
    EventLoop::instance().addEvent(event);
    other.lose();
}

bool Paper::fight(Hole& other){
    lose();
}

bool Paper::fight(Flag& other){
    Event event(Lose);
    EventLoop::instance().addEvent(event);
}

bool Paper::fight(Weapon &other) {
    if (&other == this)
        return false;

    other.fight(*this);
}
