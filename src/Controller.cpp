//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"

Controller::Controller() : m_window(WindowManager::instance().getWindow()), m_p1(std::make_unique<UserState>()),
                           m_p2(std::make_unique<EnemyState>()) {
    m_p1->init(m_board.getMatrix());
    m_p2->init(m_board.getMatrix());
    eventsHandler();
}

void Controller::eventsHandler() {
    print();
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window->close();
            if (event.type == sf::Event::MouseButtonReleased) clickHandler(event.mouseButton);

            print();
        }
    }
}

void Controller::print() {
    m_window->clear();
    m_window->draw(*ResourcesManager::instance().getBackground());
    m_board.print();
    m_p1->print();
    m_p2->print();

    m_window->display();
}

void Controller::clickHandler(sf::Event::MouseButtonEvent event) {
    if (m_board.getBoardBounds().contains(event.x, event.y)) {
        sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
        int row = (event.y - rect_size.top) / rect_size.height;
        int col = (event.x - rect_size.left) / rect_size.width;
        auto bool_arr = m_p1->checkAvailableLocations(Location(row, col));
        if (bool_arr) {
            m_board.setArrows(bool_arr, Location(row, col));
        } else
            return;
    }
}
