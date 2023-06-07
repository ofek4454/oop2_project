//
// Created by Bar Kobi on 21/05/2023.
//

#include "Rock.h"
#include "Paper.h"
#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Undefined.h"
#include "Warrior.h"

Rock::Rock(bool visible) : Weapon("R",visible) {
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55,58));
}

 void Rock::fight(Scissors& other){
    Event event(FightRS, P1Won);
    EventLoop::instance().addEvent(event);
    other.lose();
}

 void Rock::fight(Paper& other){
     Event event(FightRP, P2Won);
     EventLoop::instance().addEvent(event);
     lose();
}

 void Rock::fight(Rock& other){
//    static bool first = true;
//    if(!first){
//        chooseWeapon();
//        first = true;
//        return;
//    }
//    first = false;
     Event event(FightRR,Tie);
     EventLoop::instance().addEvent(event);
//     chooseWeapon();
}

 void Rock::fight(Hole& other){
     EventLoop::instance().addEvent(Event(HoleFall,P2Won));
    lose();
}

 void Rock::fight(Flag& other){
     Event event(Won);
     EventLoop::instance().addEvent(event);
}

void Rock::fight(Undefined& other){
    Event event(AttackingUndefined);
    EventLoop::instance().addEvent(event);
}

void Rock::fight(Weapon &other) {
    if (&other == this)
        return;

    other.fight(*this);
}