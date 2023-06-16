#include "Referee.h"

Referee::Referee(Turn_t turn) : m_window(WindowManager::instance().getWindow()) , m_turn(turn){
    auto frameRectSize = sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.775,
                                      WINDOW_HEIGHT * 0.685 - WINDOW_HEIGHT * 0.355);
    m_sprite.setTexture(*ResourcesManager::instance().getTexture(RefereeTexture));
    m_sprite.setScale((frameRectSize.x / 263) * 0.6, (frameRectSize.y / 203) * 0.6);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 263, 203));
    m_sprite.setPosition(
            sf::Vector2f(WINDOW_WIDTH * 0.775 + ((WINDOW_WIDTH - WINDOW_WIDTH * 0.775) / 2) -
                         (m_sprite.getGlobalBounds().width / 2),
                         WINDOW_HEIGHT * 0.355 + ((WINDOW_WIDTH - WINDOW_WIDTH * 0.775,
                                 WINDOW_HEIGHT * 0.685 - WINDOW_HEIGHT * 0.355) / 2) -
                         (m_sprite.getGlobalBounds().height / 2)));
    m_rect = (turn == P1) ? 0 : 789;
    m_sprite.setTextureRect(sf::IntRect(m_rect, 0, 263, 203));
}

void Referee::animate(Turn_t turn) {
    static sf::Clock clock;

    if(clock.getElapsedTime().asSeconds() < 0.15)
        return;
    clock.restart();

    m_rect += (turn == P1) ? -263 : 263;
    if(m_rect < 0) m_rect = 0;
    if(m_rect > 789) m_rect = 789;

    m_sprite.setTextureRect(sf::IntRect(m_rect, 0, 263, 203));

    if (m_rect <= 0 && turn == P1) {
        if(turn != m_turn)
            ResourcesManager::instance().playSound(blueTurn);
        m_turn = turn;
    }
    else if (m_rect >= 789 && turn == P2) {
        if(turn != m_turn)
            ResourcesManager::instance().playSound(redTurn);
        m_turn = turn;
    }
}

void Referee::print() {
    m_window->draw(m_sprite);
}
