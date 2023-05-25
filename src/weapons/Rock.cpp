//
// Created by Bar Kobi on 21/05/2023.
//

#include "Rock.h"
#include "Paper.h"
#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Undefined.h"

Rock::Rock(){
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setTextureRect(sf::IntRect(110, 116, 55,58));
}

 bool Rock::fight(Scissors& other){
    Event event(FightScissorsRock);
    EventLoop::instance().addEvent(event);
    other.lose();
}

 bool Rock::fight(Paper& other){
     Event event(FightPaperRock);
     EventLoop::instance().addEvent(event);
     lose();
}

 bool Rock::fight(Rock& other){
     Event event(FightRockRock);
     EventLoop::instance().addEvent(event);
}

 bool Rock::fight(Hole& other){
    lose();
}

 bool Rock::fight(Flag& other){
     Event event(Lose);
     EventLoop::instance().addEvent(event);
}