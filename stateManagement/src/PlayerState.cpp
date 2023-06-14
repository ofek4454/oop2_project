#include "PlayerState.h"
#include "iostream"

PlayerState::PlayerState(PlayerModel &player) : m_player(player){}

void PlayerState::handleHover(const int row, const int col) {
    for (auto &warrior: m_warriors){
        if(warrior.second->getSymbol() == "F" || warrior.second->getSymbol() == "H") continue;
        warrior.second->setHighlighted(warrior.second->getLocation() == Location(row, col));
    }
}

Warrior *PlayerState::getWarrior(const Location location){
    for(auto &warrior : m_warriors)
        if (warrior.second->getLocation() == location)
            return warrior.second.get();
    return NULL;
}

Warrior *PlayerState::getWarrior(const std::string warriorId){
    return m_warriors.contains(warriorId) ? m_warriors[warriorId].get() : NULL;
}

void PlayerState::checkDeletion() {
    std::erase_if(m_warriors,[](auto& warrior) {return warrior.second->isNeedToBeDeleted();});
}

const PlayerModel &PlayerState::getPlayerModel() const {
    return m_player;
}


bool PlayerState::setAsFlag(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    if(!warrior)
        return false;

    auto isSet = warrior->setAsFlag();
    if(isSet)
        RoomState::instance().setBoardCell(Location(row, col), m_playerSymbol + "F");
    return isSet;
}

bool PlayerState::setAsHole(const int row, const int col) {
    auto warrior = getWarrior(Location(row,col));
    if(!warrior){
        return false;
    }

    auto isSet = warrior->setAsHole();
    if(isSet)
        RoomState::instance().setBoardCell(Location(row, col), m_playerSymbol + "H");
    return isSet;
}

Warrior* PlayerState::pickRandomWarrior() {
    std::vector<Warrior*> tempVector;
    for(auto& warrior : m_warriors){
        if(warrior.second->getWeapon()->isVisible()){
            tempVector.push_back(warrior.second.get());
        }
    }
    if(tempVector.size() == 0)
        return NULL;

    int randomNumber = rand() % tempVector.size();
    return tempVector[randomNumber];
}
