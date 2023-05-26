#pragma once

#include "Consts.h"
#include "PlayerModel.h"
#include "Warrior.h"
#include "WindowManager.h"
#include "Weapon.h"

class PlayerState {
public:
    friend class PlayerModel;
    PlayerState() = default;
    virtual ~PlayerState() = default;
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) = 0;
    void print();
    bool* checkAvailableLocations(Location location);
    bool move(Direction_t direction,Location selectedLocation);
    Warrior* getWarrior(const Location location);
    std::vector<Warrior>* getAllWarriors() { return &m_warriors;}
    void handleHover(const int row, const int col);

    virtual void hoverFlag(const int row, const int col) = 0;
    virtual void hoverHole(const int row, const int col) = 0;

    void checkDeletion();
    void setAsFlag(const int row, const int col);
    void setAsHole(const int row, const int col);
//    void updateFlagAnimation(Location location);

protected:
    std::vector<Warrior> m_warriors;
private:
    float m_pixelOffset = RECT_SIZE / IMAGE_COUNT;
    PlayerModel m_player;

};


