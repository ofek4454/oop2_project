//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"

Controller::Controller() : m_window(WindowManager::instance().getWindow()), m_p1(std::make_unique<UserState>()),
                           m_p2(std::make_unique<EnemyState>()) {
    m_p1->init(m_board.getMatrix());
    m_p2->init(m_board.getMatrix());
    initFlagAndHole();
    run();
}

void Controller::run() {
    print();
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window->close();
            if (event.type == sf::Event::MouseButtonReleased) clickHandler(event.mouseButton);
            if (event.type == sf::Event::MouseMoved) handleHover(event.mouseMove);
        }
        handleEvents();

        if (m_isAnimating)
            handleAnimation();

        checkCollision();
        print();
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
        m_direction = m_board.getDirection(sf::Vector2f(event.x, event.y));
        m_board.setArrows();
        m_isMoving = false;
        if(m_direction != Non_Direction){
            m_isAnimating = true;
        }
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
    for (auto &p1: *p1_vec)
        for (auto &p2: *p2_vec)
            if (p1.getLocation() == p2.getLocation()){
                p1.getWeapon()->get()->fight(**p2.getWeapon());
            }
}

void Controller::handleAnimation() {
    static sf::Clock clock;
    auto time = clock.getElapsedTime().asSeconds();
    if (time > 0.025) {
        clock.restart().asSeconds();
        if (m_p1->move(m_direction, m_selectedPlayerLocation)) {
            m_isAnimating = false;
        }
    }
}

void Controller::handleHover(sf::Event::MouseMoveEvent &event) {
    if (m_board.getBoardBounds().contains(event.x, event.y)) {
        sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
        int row = (event.y - rect_size.top) / rect_size.height;
        int col = (event.x - rect_size.left) / rect_size.width;
        m_p1->handleHover(row, col);
    }
}

void Controller::initFlagAndHole() {
    bool flagChoosed = false;
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) m_window->close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if(!m_board.getBoardBounds().contains(event.mouseButton.x,event.mouseButton.y)) continue;
                sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
                int row = (event.mouseButton.y - rect_size.top) / rect_size.height;
                int col = (event.mouseButton.x - rect_size.left) / rect_size.width;
                if(row < BOARD_SIZE-2) continue;
                if(!flagChoosed){
                    m_p1->setAsFlag(row,col);
                    flagChoosed= true;
                } else{
                    m_p1->setAsHole(row,col);
                    return;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if(!m_board.getBoardBounds().contains(event.mouseMove.x,event.mouseMove.y)) continue;
                sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
                int row = (event.mouseMove.y - rect_size.top) / rect_size.height;
                int col = (event.mouseMove.x - rect_size.left) / rect_size.width;
                if(!flagChoosed) m_p1->hoverFlag(row,col);
                else m_p1->hoverHole(row,col);
            }
        }
        print();
    }
    // TODO fetch enemy hole and flag
}

void Controller::handleEvents() {
    while(EventLoop::instance().hasEvent()){
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()){
            case FightPaperPaper:{
                animateFight(ResourcesManager::instance().getTexture(PaperPaper));
            }
        }
    }
}

void Controller::animateFight(sf::Texture *fightTexture) {
    int frameCounter = 0;
    sf::Clock fightAnimationClock;
    sf::Texture bg;
    bg.loadFromImage(m_window->capture());
    sf::Sprite background(bg);
    sf::Sprite fightSprite(*fightTexture);
    while(frameCounter < 980){
        if(fightAnimationClock.getElapsedTime().asSeconds() < 0.15) continue;
        fightAnimationClock.restart();
        fightSprite.setTextureRect(sf::IntRect(frameCounter,0,140,87));
        m_window->clear();
        m_window->draw(background);
        m_window->draw(fightSprite);
        m_window->display();
        frameCounter+= 140;
    }


}
