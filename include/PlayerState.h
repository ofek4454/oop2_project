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
    bool move(Direction direction,Location selectedLocation);
    Warrior* getWarrior(const Location location);
    std::vector<Warrior>* getAllWarriors() { return &m_warriors;}
    void handleHover(const int row, const int col);
protected:
    std::vector<Warrior> m_warriors;
private:
    float m_pixelOffset = RECT_SIZE / IMAGE_COUNT;
    PlayerModel m_player;

};


