//
// Created by Bar Kobi on 18/05/2023.
//

#include "PlayerState.h"
#include "iostream"

void PlayerState::handleHover(const sf::Event::MouseMoveEvent &event) {
    for (auto &warrior: m_warriors) {
        if (warrior.getGlobalBounds().contains(event.x, event.y)) {
            warrior.setHighlighted(true);
        } else {
            warrior.setHighlighted(false);
        }
    }
}


void PlayerState::print() {
    for (auto &warrior: m_warriors) {
        warrior.draw();
        warrior.getWeapon()->get()->draw();
    }
}

bool *PlayerState::checkAvailableLocations(Location location) {
    bool isOnPlayer = false;
    for (auto &warrior: m_warriors) {
        if (warrior.getLocation() == location) {
            isOnPlayer = true;
        }
    }
    if (!isOnPlayer) {
        return nullptr;
    }
    bool *locations = new bool[4];
    locations[0] = true;
    locations[1] = true;
    locations[2] = true;
    locations[3] = true;
    for (int i = 0; i < m_warriors.size(); i++) {
        auto warrior_loc = m_warriors[i].getLocation();
        if (warrior_loc == location)
            continue;
        if (location.row < 0 || (location.row - 1 == warrior_loc.row && location.col == warrior_loc.col))
            locations[Up] = false;
        if (location.col - 1 < 0 || (location.row == warrior_loc.row && location.col - 1 == warrior_loc.col))
            locations[Left] = false;
        if (location.col + 1 > BOARD_SIZE - 1 ||
            (location.row == warrior_loc.row && location.col + 1 == warrior_loc.col))
            locations[Right] = false;
        if (location.row + 1 > BOARD_SIZE - 1 ||
            (location.row + 1 == warrior_loc.row && location.col == warrior_loc.col))
            locations[Down] = false;
    }

    return locations;
}

bool PlayerState::move(Direction direction, Location selectedLocation) {
    auto warrior = getWarrior(selectedLocation);
    if (direction == Up) {
        if (counter == 6) {
            warrior->resetAnimation();
            counter = 0;
            warrior->setLocation(Location(selectedLocation.row - 1, selectedLocation.col));
            return true;
        }
        counter++;
        warrior->setSpriteLocation(sf::Vector2f(0, m_pixelOffset));
        warrior->setIntRect();
    }
    if (direction == Down) {
        warrior->setLocation(Location(selectedLocation.row + 1, selectedLocation.col));
        warrior->setSpriteLocation(sf::Vector2f(0, RECT_SIZE));
    }
    if (direction == Left) {
        warrior->setLocation(Location(selectedLocation.row, selectedLocation.col - 1));
        warrior->setSpriteLocation(sf::Vector2f(-RECT_SIZE, 0));
    }
    if (direction == Right) {
        warrior->setLocation(Location(selectedLocation.row, selectedLocation.col + 1));
        warrior->setSpriteLocation(sf::Vector2f(RECT_SIZE, 0));
    }
    return false;
}

Warrior *PlayerState::getWarrior(const Location location) {
    for (int i = 0; i < m_warriors.size(); i++) {
        if (m_warriors[i].getLocation() == location) {
            return &m_warriors[i];
        }
    }
}


