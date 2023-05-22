#pragma once

#include "Consts.h"
#include "PlayerModel.h"
#include "Warrior.h"
#include "WindowManager.h"
#include "Weapon.h"

class PlayerState {
public:
    friend class PlayerModel;
    PlayerState() {}
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) = 0;
    void print();
    bool* checkAvailableLocations(Location location);
    void move(Direction direction,Location selectedLocation);
    Warrior* getWarrior(const Location location);
    std::vector<Warrior>* getAllWarriors() { return &m_warriors;}
    void handleHover(const sf::Event::MouseMoveEvent &event);
protected:
    std::vector<Warrior> m_warriors;
private:
    PlayerModel m_player;

};


