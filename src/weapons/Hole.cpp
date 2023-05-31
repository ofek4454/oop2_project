//
// Created by Bar Kobi on 21/05/2023.
//

#include "Hole.h"
#include "Flag.h"
#include "Scissors.h"
#include "Paper.h"
#include "Rock.h"
#include "Undefined.h"

Hole::Hole() : Weapon('H')  {
    auto weapon = ResourcesManager::instance().getTexture(Rps);
    m_weapon_sprite.setTexture(*weapon);
    m_weapon_sprite.setColor(sf::Color::Transparent);
}

void Hole::fight(Scissors& other){
    other.lose();
}

void Hole::fight(Paper& other){
    other.lose();
}

void Hole::fight(Rock& other){
    other.lose();
}

void Hole::fight(Undefined& other){
    other.lose();
}

void Hole::fight(Weapon& other){
    if (&other == this)
        return;

    other.fight(*this);
}