#pragma once

#include "PlayerState.h"

class UserState : public PlayerState{
public:
    UserState(PlayerModel &player);
    ~UserState() = default;
    virtual void init();

    virtual void hoverFlag(const int row, const int col);
    virtual void hoverHole(const int row, const int col);
    virtual void print();
    virtual void doTurn(sf::Event::MouseButtonEvent *click);
    void setArrows(bool* directions = nullptr,Location location = Location(0,0),bool set = false);
    Direction_t getDirection(const sf::Vector2f pos) const;

private:
    std::array<sf::Sprite,4> m_arrows;
};
