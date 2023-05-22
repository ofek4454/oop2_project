#pragma once

#include "Consts.h"
#include "PlayerModel.h"
#include "Warrior.h"
#include "WindowManager.h"
#include "Warrior.h"
#include "Weapon.h"

class PlayerState {
public:
    friend class PlayerModel;
    PlayerState() {}
    virtual void init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) = 0;
    void print();
protected:
    std::vector<Warrior> m_warriors;
    void handleHover(const sf::Event::MouseMoveEvent &event);
private:
    PlayerModel m_player;

};


