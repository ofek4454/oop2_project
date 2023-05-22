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
            if (event.type == sf::Event::MouseMoved) m_p1->handleHover(event.mouseMove);
        
            checkCollision();
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

void Controller::clickHandler(sf::Event::MouseButtonEvent &event) {
    if (m_isMoving) {
        auto dir = m_board.getDirection(sf::Vector2f(event.x, event.y));
        if (dir != Non_Direction) {
            m_p1->move(dir, m_selectedPlayerLocation);
        }
        m_board.setArrows();
        m_selectedPlayerLocation = Location(-1, -1);
        m_isMoving = false;
        return;
    }
    if (m_board.getBoardBounds().contains(event.x, event.y)) {
        sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
        int row = (event.y - rect_size.top) / rect_size.height;
        int col = (event.x - rect_size.left) / rect_size.width;
        auto bool_arr = m_p1->checkAvailableLocations(Location(row, col));
        if (bool_arr) {
            m_selectedPlayerLocation = Location(row, col);
            m_board.setArrows(bool_arr, m_selectedPlayerLocation, true);
            m_isMoving = true;
        }
    }
}

void Controller::checkCollision() {
    auto p1_vec = m_p1->getAllWarriors();
    auto p2_vec = m_p2->getAllWarriors();
    for(auto &p1 :*p1_vec) {
        for(auto &p2 :*p2_vec) {
            if (p1.getGlobalBounds().intersects(p2.getGlobalBounds())) {
                p1.getWeapon()->get()->fight(**p2.getWeapon());
            }
        }
    }
}
