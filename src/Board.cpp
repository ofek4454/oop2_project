#include "Board.h"

Board::Board() {

    float x = WINDOW_WIDTH / 3 - rect_size * BOARD_SIZE / 2;
    float y = WINDOW_HEIGHT / 2 - rect_size * BOARD_SIZE / 2.2;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            auto rect = sf::RectangleShape();
            rect.setSize(sf::Vector2f(rect_size, rect_size));
            rect.setFillColor((i + j) % 2 == 0 ? sf::Color(181, 221, 94) : sf::Color(181, 193, 105));
            rect.setPosition(sf::Vector2f(x, y));
            rect.setOrigin(rect_size / 2, rect_size / 2);
            m_matrix[i][j] = rect;
            x += rect_size;
        }
        y += rect_size;
        x = WINDOW_WIDTH / 3 - rect_size * BOARD_SIZE / 2;
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

const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &Board::getMatrix() const {
    return m_matrix;
}

void Board::setFrames() {
    m_boardFrame[0].setSize(sf::Vector2f(rect_size * 8, rect_size * 8));
    m_boardFrame[0].setPosition(sf::Vector2f(m_matrix[0][0].getPosition().x - m_matrix[0][0].getLocalBounds().width / 2,
                                             m_matrix[0][0].getPosition().y -
                                             m_matrix[0][0].getGlobalBounds().height / 2));
    m_boardFrame[0].setFillColor(sf::Color::Transparent);
    m_boardFrame[0].setOutlineColor(sf::Color(220, 252, 200));
    m_boardFrame[0].setOutlineThickness(2);

    m_boardFrame[1].setSize(sf::Vector2f(rect_size * 12, WINDOW_HEIGHT * 0.95));
    m_boardFrame[1].setPosition(sf::Vector2f(50, 20));
    m_boardFrame[1].setFillColor(sf::Color::Transparent);
    m_boardFrame[1].setOutlineColor(sf::Color(181, 193, 105));
    m_boardFrame[1].setOutlineThickness(10);

    float y = 20;
    for (int i = 2; i < 5; i++) {
        m_boardFrame[i].setSize(sf::Vector2f((WINDOW_HEIGHT * 0.6), (WINDOW_HEIGHT * 0.95) / 3));
        m_boardFrame[i].setPosition(
                sf::Vector2f(m_boardFrame[1].getPosition().x + m_boardFrame[1].getGlobalBounds().width, y));
        m_boardFrame[i].setFillColor(sf::Color::Transparent);
        m_boardFrame[i].setOutlineColor(sf::Color(181, 193, 105));
        m_boardFrame[i].setOutlineThickness(10);
        y += m_boardFrame[i].getGlobalBounds().height - 20;
    }


}