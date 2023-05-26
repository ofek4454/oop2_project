#pragma once

#include "vector"
#include "memory"
#include "Consts.h"
#include "WindowManager.h"
#include "SFML/Graphics.hpp"
#include "ResourcesManager.h"
#include "Location.h"

class Board {
public:
    Board();
    void print();
    const std::array<std::array<sf::RectangleShape,BOARD_SIZE>,BOARD_SIZE> &getMatrix() const;
    sf::FloatRect getBoardBounds() const {return m_boardFrame[0].getGlobalBounds();}
    void setArrows(bool* directions = nullptr,Location location = Location(0,0),bool set = false);
    Direction_t getDirection(const sf::Vector2f pos) const;
private:
    void setFrames();
    std::array<std::array<sf::RectangleShape,BOARD_SIZE>,BOARD_SIZE> m_matrix;
    std::array<sf::Sprite,4> m_arrows;
    sf::RectangleShape m_boardFrame[5];
};
