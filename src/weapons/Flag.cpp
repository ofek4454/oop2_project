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

bool Flag::fight(Rock &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

bool Flag::fight(Paper &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}

bool Flag::fight(Scissors &other) {
    Event event(Won);
    EventLoop::instance().addEvent(event);
}
