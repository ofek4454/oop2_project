#include "PlayerState.h"
#include "iostream"

PlayerState::PlayerState(PlayerModel &player) : m_player(player){}

void PlayerState::handleHover(const int row, const int col) {
    for (auto &warrior: m_warriors){
        warrior->setHighlighted(warrior->getLocation() == Location(row, col));
    }
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

    auto isSet = warrior->get()->setAsFlag();
    if(isSet)
        RoomState::instance().setBoardCell(Location(row, col), m_playerSymbol + "F");
    return isSet;
}

bool PlayerState::setAsHole(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    if(!warrior){
        return false;
    }

    auto isSet = warrior->get()->setAsHole();
    if(isSet)
        RoomState::instance().setBoardCell(Location(row, col), m_playerSymbol + "H");
    return isSet;
}

Warrior *PlayerState::pickRandomWarrior() {
    std::vector<Warrior*> tempVector;
    for(auto& warrior : m_warriors){
        if(warrior->getWeapon()->get()->isVisible()){
            tempVector.push_back(warrior.get());
        }
    }
    if(tempVector.size() == 0)
        return NULL;

    int randomnumber = rand() % tempVector.size();
    return tempVector[randomnumber];
}
