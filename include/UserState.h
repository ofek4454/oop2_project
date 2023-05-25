#pragma once

#include "PlayerState.h"

class UserState : public PlayerState{
public:
    UserState();
    ~UserState() = default;
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix);

    virtual void hoverFlag(const int row, const int col);
    virtual void hoverHole(const int row, const int col);
private:
    //void setFlagAndHole(sf::FloatRect rect_size);

};
