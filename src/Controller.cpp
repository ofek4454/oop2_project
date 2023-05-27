//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<PlayerState>* p1,std::unique_ptr<PlayerState>* p2) : m_window(WindowManager::instance().getWindow()), m_p1(p1->get()),
                           m_p2(p2->get()) {
    m_p1->init(m_board.getMatrix());
    m_p2->init(m_board.getMatrix());
    initNames();
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

        handleAnimation();

        checkCollision();
        print();
    }
}

void Controller::print() {
    m_window->clear();
    m_window->draw(*ResourcesManager::instance().getBackground());
    m_board.print();
    m_window->draw(m_p1Name);
    m_window->draw(m_p2Name);
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
            if (p1->getLocation() == p2->getLocation()){
                p2->getWeapon()->get()->fight(**p1->getWeapon());
            }

    m_p1->checkDeletion();
    m_p2->checkDeletion();
}

void Controller::handleAnimation() {
    if (!m_isAnimating) return;
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
            case FightRP:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BluePR : RedPR ), 980, 84, 7);
                break;
            case FightRS:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueRS : RedRS ), 994, 93, 7);
                break;
            case FightRR:
                animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3);
                break;
            case FightPS:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP ), 900, 96, 6);
                break;
            case FightPP:
                animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3);
                break;
            case FightSS:
                animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3);
                break;
            default:
                break;
        }
    }
}

void Controller::animateFight(sf::Texture *fightTexture, const int width,const int height, const int frames) {
    float frameWidth = width/frames;
    int frameX = 0;
    sf::Clock fightAnimationClock;
    sf::Texture bg;
    bg.create(WINDOW_WIDTH,WINDOW_HEIGHT);
    bg.update(*m_window);
    sf::Sprite background(bg);
    sf::Sprite fightSprite(*fightTexture);

    auto boardBounds = m_board.getBoardBounds();
    fightSprite.setPosition(boardBounds.left + boardBounds.width/2 , boardBounds.top + boardBounds.height/2);
    fightSprite.setOrigin(frameWidth/2,height);
    fightSprite.setScale(2,2);
    while(frameX < width){
        fightSprite.setTextureRect(sf::IntRect(frameX,0,frameWidth,height));
        m_window->clear();
        m_window->draw(background);
        m_window->draw(fightSprite);
        m_window->display();
        if(fightAnimationClock.getElapsedTime().asSeconds() < 0.2) continue;
        fightAnimationClock.restart();
        frameX+= frameWidth;
    }
    m_window->clear();
    m_window->draw(background);
    m_window->display();
}

void Controller::initNames() {
    m_p1Name.setFont(*ResourcesManager::instance().getFont());
    m_p2Name.setFont(*ResourcesManager::instance().getFont());
    m_p1Name.setCharacterSize(WINDOW_HEIGHT*0.05);
    m_p2Name.setCharacterSize(WINDOW_HEIGHT*0.05);
    m_p1Name.setFillColor(sf::Color::Blue);
    m_p2Name.setFillColor(sf::Color::Red);
    m_p1Name.setString(m_p1->getPlayerModel().m_name);
    m_p2Name.setString(m_p2->getPlayerModel().m_name);
    m_p1Name.setOrigin(m_p1Name.getGlobalBounds().width/2,m_p1Name.getGlobalBounds().height/2);
    m_p2Name.setOrigin(m_p2Name.getGlobalBounds().width/2,m_p2Name.getGlobalBounds().height/2);
    m_p1Name.setPosition(m_board.getBoardBounds().left+m_board.getBoardBounds().width/2 ,
                         m_board.getBoardBounds().top+m_board.getBoardBounds().height + m_p1Name.getGlobalBounds().height);
    m_p2Name.setPosition(m_board.getBoardBounds().left+m_board.getBoardBounds().width/2 ,
                         m_board.getBoardBounds().top - m_p2Name.getGlobalBounds().height - RECT_SIZE/2);
}
