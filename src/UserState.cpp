//
// Created by Bar Kobi on 20/05/2023.
//

#include "UserState.h"
#include "Rock.h"

UserState::UserState() : PlayerState(){}

void UserState::init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) {
    float x = matrix[BOARD_SIZE-1][0].getPosition().x;
    float y = matrix[BOARD_SIZE-1][0].getPosition().y - 30;

    int row = 7,col = 0;
    for(int i = 0; i < BOARD_SIZE*2; i++,col++) {
        if(i == BOARD_SIZE){
            row--;
            col = 0;
        }
        m_warriors.emplace_back(sf::Vector2f(x, y),true, Location(row,col));
        x+=matrix[0][0].getGlobalBounds().width;
        if(i== BOARD_SIZE - 1) {
            y -= matrix[BOARD_SIZE - 1][0].getGlobalBounds().height;
            x = matrix[BOARD_SIZE- 1][0].getPosition().x;
        }
    }
}

void UserState::hoverFlag(const int row, const int col) {
    for (auto &warrior: m_warriors)
        warrior.setTextureFlag(warrior.getLocation() == Location(row, col));
}

void UserState::hoverHole(const int row, const int col) {
    for (auto &warrior: m_warriors)
        warrior.setTextureHole(warrior.getLocation() == Location(row, col));
}
