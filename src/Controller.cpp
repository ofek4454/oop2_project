//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"

Controller::Controller() : m_window(WindowManager::instance().getWindow()), m_user(std::make_unique<UserState>()),
                           m_enemy(std::make_unique<EnemyState>()) {
    m_user->init(m_board.getMatrix());
    m_enemy->init(m_board.getMatrix());
    eventsHandler();
}

void Controller::print() {
    m_window->clear();
    m_window->draw(*ResourcesManager::instance().getBackground());
    m_board.print();
    m_user->print();
    m_enemy->print();

    m_window->display();
}

void Controller::eventsHandler() {
    print();
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {

            }

            print();
        }
    }
}
