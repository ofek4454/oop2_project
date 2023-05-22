//
// Created by Bar Kobi on 18/05/2023.
//

#include "PlayerState.h"


void PlayerState::handleHover(const sf::Event::MouseMoveEvent &event) {
    for(auto &warrior : m_warriors) {
        if(warrior.getGlobalBounds().contains(event.x,event.y)){
            //TODO handle hover
        }
    }
}


void PlayerState::print() {
    for(auto &warrior : m_warriors) {
        warrior.draw();
        warrior.getWeapon()->get()->draw();
    }
}