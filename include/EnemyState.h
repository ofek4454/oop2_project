#pragma once
#include "PlayerState.h"

class EnemyState : public PlayerState{
public:
    EnemyState();
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix);
private:
    void setFlagAndHole();
};


