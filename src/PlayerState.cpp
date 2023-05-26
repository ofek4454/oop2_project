
#include "PlayerState.h"
#include "iostream"

void PlayerState::handleHover(const int row, const int col) {
    for (auto &warrior: m_warriors)
        warrior->setHighlighted(warrior->getLocation() == Location(row, col));
}

void PlayerState::print() {
    for (auto &warrior: m_warriors)
        warrior->draw();
}

bool *PlayerState::checkAvailableLocations(Location location) {
    auto warrior = getWarrior(location);

    if (warrior == NULL || !warrior->get()->canMove())
        return nullptr;

    bool *locations = new bool[4];
    locations[0] = true;
    locations[1] = true;
    locations[2] = true;
    locations[3] = true;

    for (int i = 0; i < m_warriors.size(); i++) {
        auto warrior_loc = m_warriors[i]->getLocation();
        if (warrior_loc == location)
            continue;
        if (location.row <= 0 || (location.row - 1 == warrior_loc.row && location.col == warrior_loc.col))
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

bool PlayerState::move(Direction_t direction, Location selectedLocation) {
    static int imageCounter = 0;
    auto warrior = getWarrior(selectedLocation);
    if (direction == Up)
        warrior->get()->setSpriteLocation(sf::Vector2f(0, -m_pixelOffset));
    if (direction == Down)
        warrior->get()->setSpriteLocation(sf::Vector2f(0, +m_pixelOffset));
    if (direction == Left)
        warrior->get()->setSpriteLocation(sf::Vector2f(-m_pixelOffset, 0));
    if (direction == Right)
        warrior->get()->setSpriteLocation(sf::Vector2f(m_pixelOffset, 0));

    warrior->get()->setIntRect(imageCounter);
    imageCounter++;
    if(imageCounter == IMAGE_COUNT){
        imageCounter = 0;
        warrior->get()->setLocation(direction);
        return true;
    }
    return false;
}

std::unique_ptr<Warrior> *PlayerState::getWarrior(const Location location) {
    for (int i = 0; i < m_warriors.size(); i++)
        if (m_warriors[i]->getLocation() == location)
            return &m_warriors[i];
    return NULL;
}

void PlayerState::setAsFlag(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    warrior->get()->setAsFlag();
}

void PlayerState::setAsHole(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    warrior->get()->setAsHole();
}

void PlayerState::checkDeletion() {
    std::erase_if(m_warriors,[](auto& warrior) {return warrior->isNeedToBeDeleted();});
}

//void PlayerState::updateFlagAnimation(Location location) {
//    static int imgCounter = 0;
//    auto warrior = getWarrior(location);
//    warrior->setIntRect(imgCounter);
//    imgCounter++;
//    if(imgCounter == IMAGE_COUNT){
//        imgCounter = 0;
//    }
//}


