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
    sf::Vector2f getRectPosition(const Location &location)const {return m_matrix[location.row][location.col].getPosition();}
private:
    std::shared_ptr<sf::RenderWindow> m_window;
    void setFrames();
    std::array<std::array<sf::RectangleShape,BOARD_SIZE>,BOARD_SIZE> m_matrix;
    std::array<sf::Sprite,4> m_arrows;
    sf::RectangleShape m_boardFrame[5];
    sf::RectangleShape m_logo;
};
