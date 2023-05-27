#pragma once
#include "PlayerState.h"

class EnemyState : public PlayerState{
public:
    EnemyState(const std::string& name,const std::string& id);
    ~EnemyState() = default;
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix);

    virtual void hoverFlag(const int row, const int col){};
    virtual void hoverHole(const int row, const int col){};
    void setFlagAndHole();
private:
};


