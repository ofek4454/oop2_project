#pragma once

#include "vector"
#include "array"
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
    sf::RectangleShape *getFrame(int frame) {return &m_boardFrame[frame];}
private:
    void setFrames();
    std::array<std::array<sf::RectangleShape,BOARD_SIZE>,BOARD_SIZE> m_matrix;
    std::array<sf::Sprite,4> m_arrows;
    sf::RectangleShape m_boardFrame[5];
    sf::RectangleShape m_logo;
};
