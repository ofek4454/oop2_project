#pragma once

#include "PlayerState.h"

class UserState : public PlayerState{
public:
    UserState(PlayerModel &player);
    ~UserState() = default;
    virtual void init();

    void checkAvailableLocations(Location location);
    virtual void hoverFlag(const int row, const int col);
    virtual void hoverHole(const int row, const int col);
    virtual void print();
    virtual bool move();
    virtual void doTurn(sf::Event::MouseButtonEvent *click = NULL,sf::Event::KeyEvent *key = NULL,Location indicator = Location(-1, -1));
    void setArrows(Location location = Location(0,0),bool set = false);
    Direction_t getDirection(const sf::Vector2f pos) const;

private:
    bool warriorIsNull = false;
    bool m_availableDirection[4];
    std::array<sf::Sprite,4> m_arrows;
    std::array<Location,4> m_arrowsLocation;
};
