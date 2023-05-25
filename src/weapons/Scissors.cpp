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

bool Scissors::fight(Scissors& other) {
    Event event(FightScissorsScissors);
    EventLoop::instance().addEvent(event);
}

bool Scissors::fight(Paper& other) {
    Event event(FightPaperScissors);
    EventLoop::instance().addEvent(event);
    other.lose();
}

bool Scissors::fight(Rock& other) {
    Event event(FightRockScissors);
    EventLoop::instance().addEvent(event);
    lose();
}

bool Scissors::fight(Hole& other) {
    lose();
}

bool Scissors::fight(Flag& other) {
    Event event(Lose);
    EventLoop::instance().addEvent(event);
}