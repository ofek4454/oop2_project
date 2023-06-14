#include "Board.h"
#include <iostream>

Board::Board() {

    float x = BOARD_FRAME.left;
    float y = BOARD_FRAME.top;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            auto rect = sf::RectangleShape();
            rect.setSize(sf::Vector2f(RECT_SIZE, RECT_SIZE));
            rect.setFillColor((i + j) % 2 == 0 ? GREEN_COLOR : GRAY_COLOR);
            rect.setPosition(sf::Vector2f(x, y));
            rect.setOrigin(RECT_SIZE / 2, RECT_SIZE / 2);
            m_matrix[i][j] = rect;
            x += RECT_SIZE;
        }
        y += RECT_SIZE;
        x = BOARD_FRAME.left;
    }

    for (auto &spr: m_arrows) {
        spr.setTexture(*ResourcesManager::instance().getTexture(Arrow));
        spr.setScale(RECT_SIZE / 1024, RECT_SIZE / 1024);
        spr.setColor(sf::Color::Transparent);
    }

    setFrames();

}

void Board::print() {

    sf::RenderWindow *window = WindowManager::instance().getWindow();
    for (const auto &row: m_matrix) {
        for (const auto &rect: row) {
            window->draw(rect);
        }
    }

    for (auto &frame: m_boardFrame) {
        window->draw(frame);
    }
}

void Board::setFrames() {
    // board white frame
    m_boardFrame[0].setSize(sf::Vector2f(RECT_SIZE * 8, RECT_SIZE * 6));
    m_boardFrame[0].setPosition(sf::Vector2f(m_matrix[0][0].getPosition().x - RECT_SIZE / 2,
                                             m_matrix[0][0].getPosition().y - RECT_SIZE / 2));
    m_boardFrame[0].setFillColor(sf::Color::Transparent);
    m_boardFrame[0].setOutlineColor(sf::Color(255, 255, 255, 150));
    m_boardFrame[0].setOutlineThickness(2);

    // window frame
    m_boardFrame[1].setSize(sf::Vector2f(WINDOW_WIDTH * 0.95, WINDOW_HEIGHT * 0.95));
    m_boardFrame[1].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.025, WINDOW_HEIGHT * 0.025));
    m_boardFrame[1].setFillColor(sf::Color::Transparent);
    m_boardFrame[1].setOutlineColor(GRAY_COLOR);
    m_boardFrame[1].setOutlineThickness(10);

    // game info frame
    m_boardFrame[2].setSize(sf::Vector2f(WINDOW_WIDTH * 0.20, 10));
    m_boardFrame[2].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775, WINDOW_HEIGHT * 0.355));
    m_boardFrame[2].setFillColor(GRAY_COLOR);

    m_boardFrame[3].setSize(sf::Vector2f(WINDOW_WIDTH * 0.20, 10));
    m_boardFrame[3].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775, WINDOW_HEIGHT * 0.685));
    m_boardFrame[3].setFillColor(GRAY_COLOR);

    m_boardFrame[4].setSize(sf::Vector2f(10, WINDOW_HEIGHT * 0.95));
    m_boardFrame[4].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775, WINDOW_HEIGHT * 0.025));
    m_boardFrame[4].setFillColor(GRAY_COLOR);
}
