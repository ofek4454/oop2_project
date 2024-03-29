#include "GameBar.h"

/**
 * create gameBar, calculate each text position.
 */
GameBar::GameBar() {
    m_window = WindowManager::instance().getWindow();

    m_sprites[P1].setTexture(*ResourcesManager::instance().getTexture(Warriors));
    m_sprites[P1].setTextureRect(sf::IntRect(0, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT));
    m_sprites[P1].setScale(RECT_SIZE / IMAGE_WIDTH * 0.7f, RECT_SIZE / IMAGE_WIDTH * 0.7f);
    m_sprites[P1].setOrigin(m_sprites[P1].getLocalBounds().width / 2.f, m_sprites[P1].getLocalBounds().height / 2.f);
    m_sprites[P1].setPosition(BOARD_FRAME.left,BOARD_FRAME.top - RECT_SIZE / 2.f + BOARD_FRAME.height + H3);

    m_sprites[P2].setTexture(*ResourcesManager::instance().getTexture(Warriors));
    m_sprites[P2].setTextureRect(sf::IntRect(0, IMAGE_HEIGHT * 3, IMAGE_WIDTH,
                                             IMAGE_HEIGHT));
    m_sprites[P2].setScale(RECT_SIZE / IMAGE_WIDTH * 0.7f, RECT_SIZE / IMAGE_WIDTH * 0.7f);
    m_sprites[P2].setOrigin(m_sprites[P2].getLocalBounds().width / 2.f, m_sprites[P2].getLocalBounds().height / 2.f);

    m_sprites[P2].setPosition(BOARD_FRAME.left,
                              BOARD_FRAME.top - RECT_SIZE / 2.f - (H3 * 0.7f) - RECT_SIZE / 2.f);


    m_statsText[0] = TextClass(": 16",H3,sf::Vector2f(m_sprites[P1].getPosition().x + WINDOW_WIDTH * 0.05f, m_sprites[P1].getPosition().y)).getText();
    m_statsText[1] = TextClass(": 16",H3, sf::Vector2f(m_sprites[P2].getPosition().x + WINDOW_WIDTH * 0.05f, m_sprites[P2].getPosition().y)).getText();

}

/**
 * draw the game bar
 * @param window the window to draw on
 */
void GameBar::drawStats() {
    m_window->draw(m_sprites[P1]);
    m_window->draw(m_statsText[P1]);
    m_window->draw(m_sprites[P2]);
    m_window->draw(m_statsText[P2]);
    m_timer.print();
}

/**
 * update the texts with a given stats
 * @param stats
 */
void GameBar::updateGameBar(int userWarriors, int enemyWarriors) {
    m_timer.updateCount();

    m_statsText[0].setString(": " + std::to_string(userWarriors));
    m_statsText[1].setString(": " + std::to_string(enemyWarriors));
}


void GameBar::resetClock(bool myTurn) {
    m_timer.setCount(30);
    m_timer.setColor(myTurn ? sf::Color::White : sf::Color::Red);
}

void GameBar::setClock(int time) {
    m_timer.setCount(time);
}
