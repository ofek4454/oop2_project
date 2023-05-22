#pragma once

#include "vector"
#include "memory"
#include "Consts.h"
#include "WindowManager.h"
#include "SFML/Graphics.hpp"

class Board {
public:
    Board();
    void print();
    const std::array<std::array<sf::RectangleShape,BOARD_SIZE>,BOARD_SIZE> &getMatrix() const;
private:
    void setFrames();
    std::array<std::array<sf::RectangleShape,BOARD_SIZE>,BOARD_SIZE> m_matrix;
    sf::RectangleShape m_boardFrame[5];
};
