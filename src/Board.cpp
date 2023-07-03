#include "Board.h"
#include <iostream>

Board::Board() {

    m_window = WindowManager::instance().getWindow();
    float x = BOARD_FRAME.left;
    float y = BOARD_FRAME.top;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            auto rect = sf::RectangleShape();
            rect.setSize(sf::Vector2f(RECT_SIZE, RECT_SIZE));
            rect.setFillColor((i + j) % 2 == 0 ? BLUE_COLOR : LIGHT_BLUE_COLOR);
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
        spr.setScale(RECT_SIZE / 1024.f, RECT_SIZE / 1024.f);
        spr.setColor(sf::Color::Transparent);
    }

    setFrames();

    m_logo.setTexture(ResourcesManager::instance().getTexture(Logo));
    m_logo.setSize(sf::Vector2f(2.f * CIRCLE_RADIUS, 2.f * CIRCLE_RADIUS));
    m_logo.setPosition(CLOCK_CIRCLE_CENTER.x, WINDOW_HEIGHT * 0.355f - 1.1f * CIRCLE_RADIUS);
    m_logo.setOrigin(CIRCLE_RADIUS, CIRCLE_RADIUS);
}

void Board::print() {

    for (const auto &row: m_matrix) {
        for (const auto &rect: row) {
            m_window->draw(rect);
        }
    }

    for (auto &frame: m_boardFrame) {
        m_window->draw(frame);
    }
    m_window->draw(m_logo);
}

void Board::setFrames() {
    // board white frame
    m_boardFrame[0].setSize(sf::Vector2f(RECT_SIZE * BOARD_SIZE, RECT_SIZE * ROWS));
    m_boardFrame[0].setPosition(sf::Vector2f(m_matrix[0][0].getPosition().x - RECT_SIZE / 2.f,
                                             m_matrix[0][0].getPosition().y - RECT_SIZE / 2.f));
    m_boardFrame[0].setFillColor(sf::Color::Transparent);
    m_boardFrame[0].setOutlineColor(LIGHT_BLUE_COLOR);
    m_boardFrame[0].setOutlineThickness(7);

    // window frame
    m_boardFrame[1].setSize(sf::Vector2f(WINDOW_WIDTH * 0.95f, WINDOW_HEIGHT * 0.95f));
    m_boardFrame[1].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.025f, WINDOW_HEIGHT * 0.025f));
    m_boardFrame[1].setFillColor(sf::Color::Transparent);
    m_boardFrame[1].setOutlineColor(LIGHT_BLUE_COLOR);
    m_boardFrame[1].setOutlineThickness(10.f);

    // game info frame
    m_boardFrame[2].setSize(sf::Vector2f(WINDOW_WIDTH * 0.20f, 10.f));
    m_boardFrame[2].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775f, WINDOW_HEIGHT * 0.355f));
    m_boardFrame[2].setFillColor(LIGHT_BLUE_COLOR);

    m_boardFrame[3].setSize(sf::Vector2f(WINDOW_WIDTH * 0.20f, 10.f));
    m_boardFrame[3].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775f, WINDOW_HEIGHT * 0.685f));
    m_boardFrame[3].setFillColor(LIGHT_BLUE_COLOR);

    m_boardFrame[4].setSize(sf::Vector2f(10, WINDOW_HEIGHT * 0.95f));
    m_boardFrame[4].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775f, WINDOW_HEIGHT * 0.025f));
    m_boardFrame[4].setFillColor(LIGHT_BLUE_COLOR);
}
