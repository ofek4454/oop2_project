
#include "PlayerState.h"
#include "iostream"

PlayerState::PlayerState(PlayerModel &player) : m_player(player){}

void PlayerState::handleHover(const int row, const int col) {
    for (auto &warrior: m_warriors){
        warrior->setHighlighted(warrior->getLocation() == Location(row, col));
    }
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


std::unique_ptr<Warrior> *PlayerState::getWarrior(const Location location) {
    for (int i = 0; i < m_warriors.size(); i++)
        if (m_warriors[i]->getLocation() == location)
            return &m_warriors[i];
    return NULL;
}


void PlayerState::checkDeletion() {
    std::erase_if(m_warriors,[](auto& warrior) {return warrior->isNeedToBeDeleted();});
}

const PlayerModel &PlayerState::getPlayerModel() const {
    return m_player;
}


bool PlayerState::setAsFlag(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    if(!warrior)
        return false;

    auto isSet = warrior->get()->setAsFlag(m_playerSymbol == "1");
    if(isSet)
        RoomState::instance().setBoardCell(Location(row, col), m_playerSymbol + "F");
    return isSet;
}

bool PlayerState::setAsHole(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    if(!warrior)
        return false;

    auto isSet = warrior->get()->setAsHole(m_playerSymbol == "1");
    if(isSet)
        RoomState::instance().setBoardCell(Location(row, col), m_playerSymbol + "H");
    return isSet;
}
