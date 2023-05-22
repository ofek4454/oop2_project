#pragma once

#include "PlayerState.h"

class UserState : public PlayerState{
public:
    UserState();
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix);
private:
    void setFlagAndHole();
};
