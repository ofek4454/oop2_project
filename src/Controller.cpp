//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<PlayerState> *p1, std::unique_ptr<PlayerState> *p2) : m_window(
        WindowManager::instance().getWindow()), m_p1(p1->get()),
                                                                                             m_p2(p2->get()) {
    m_p1->init(m_board.getMatrix());
    m_p2->init(m_board.getMatrix());
    initNames();
    initFlagAndHole();
}

void Controller::run() {
    print();
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                handleHover(move);
                return false;
            },
            [this](auto click, auto exit) {
                if (m_turn == P1) {
                    m_p1->doTurn(click);
                }
                return false;
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto exit) { return false; },
            [this](auto exit) {
//                m_p2->doTurn();
                handleAnimation();
                handleEvents();
                checkCollision();
                print();
            }
    );
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


void Controller::checkCollision() {
    auto p1_vec = m_p1->getAllWarriors();
    auto p2_vec = m_p2->getAllWarriors();
    for (auto &p1: *p1_vec)
        for (auto &p2: *p2_vec)
            if (p1->getLocation() == p2->getLocation()) {
                p2->getWeapon()->get()->fight(**p1->getWeapon());
            }

    m_p1->checkDeletion();
    m_p2->checkDeletion();
}

void Controller::handleAnimation() {
    if (!m_p1->isAnimating()) return;
    static sf::Clock clock;
    auto time = clock.getElapsedTime().asSeconds();
    if (time > 0.025) {
        clock.restart().asSeconds();
        if (m_p1->move()) {
            m_p1->setAnimating(false);
        }
    }
}

void Controller::handleHover(sf::Event::MouseMoveEvent &event) {
    if (BOARD_FRAME.contains(event.x, event.y)) {
        sf::Vector2f rect_pos = m_board.getMatrix()[0][0].getPosition();
        int row = (event.y - rect_pos.y) / RECT_SIZE;
        int col = (event.x - rect_pos.x) / RECT_SIZE;
        m_p1->handleHover(row, col);
    }
}

void Controller::initFlagAndHole() {
    bool flagChoosed = false;
    WindowManager::instance().eventHandler(
            [this, &flagChoosed](auto move, auto exit) {
                if (!BOARD_FRAME.contains(move.x, move.y)) return true;
                sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
                int row = (move.y - rect_size.top) / rect_size.height;
                int col = (move.x - rect_size.left) / rect_size.width;
                if (!flagChoosed) m_p1->hoverFlag(row, col);
                else m_p1->hoverHole(row, col);
                return false;
            },
            [this, &flagChoosed](auto click, auto &exit) {
                if (!BOARD_FRAME.contains(click.x, click.y)) return true;
                sf::FloatRect rect_size = m_board.getMatrix()[0][0].getGlobalBounds();
                int row = (click.y - rect_size.top) / rect_size.height;
                int col = (click.x - rect_size.left) / rect_size.width;
                if (row < BOARD_SIZE - 2) return true;
                if (!flagChoosed) {
                    m_p1->setAsFlag(row, col);
                    flagChoosed = true;
                } else {
                    m_p1->setAsHole(row, col);
                    exit = true;
                    return false;
                }
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto &exit) { return false; },
            [this](auto exit) {
                print();
            }
    );
    // TODO fetch enemy hole and flag
}

void Controller::handleEvents() {
    while (EventLoop::instance().hasEvent()) {
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()) {
            case FightRP:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BluePR : RedPR), 980,
                             84, 7);
                break;
            case FightRS:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueRS : RedRS), 994,
                             93, 7);
                break;
            case FightRR:
                animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3);
                break;
            case FightPS:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 900,
                             96, 6);
                break;
            case FightPP:
                animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3);
                break;
            case FightSS:
                animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3);
                break;
            case UndefinedChoose:{
                animateFight(ResourcesManager::instance().getTexture(BlueSP), 300,
                             96, 2);
                auto warrior1 = m_p1->getWarrior(m_p1->getWarriorLocation());
                if(warrior1 != NULL){
                    warrior1->get()->getWeapon()->get()->chooseWeapon();
                }
                break;
            }
            case UndefinedUndefined:{
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 300,
                             96, 2);
                auto warrior1 = m_p1->getWarrior(m_p1->getWarriorLocation());
                if(warrior1 != NULL){
                    warrior1->get()->getWeapon()->get()->chooseWeapon();
                }
                auto warrior2 = m_p2->getWarrior(m_p2->getWarriorLocation());
                if(warrior2 != NULL){
                    warrior2->get()->getWeapon()->get()->chooseWeapon();
                }
                break;
            }
            default:
                break;
        }
    }
}

void Controller::animateFight(sf::Texture *fightTexture, const int width, const int height, const int frames) {
    float frameWidth = width / frames;
    float frameSave = 0;
    int counter = 0;
    float arr[frames * 8];
    for(int i = 0; i < frames * 8;i++){
        if(i %  8  == 0 && i != 0){
            frameSave += frameWidth;
        }
        arr[i] = frameSave;
    }

    sf::Clock fightAnimationClock;
    sf::Texture bg;
    bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    bg.update(*m_window);

    sf::Sprite background(bg);
    sf::Sprite fightSprite(*fightTexture);

    auto boardBounds = BOARD_FRAME;
    fightSprite.setPosition(boardBounds.left + boardBounds.width / 2, boardBounds.top + boardBounds.height / 2);
    fightSprite.setOrigin(frameWidth / 2, height);
    fightSprite.setScale(2.2, 2.2);
    while (counter < frames * 8) {
        fightSprite.setTextureRect(sf::IntRect(arr[counter], 0, frameWidth, height));
        m_window->clear();
        m_window->draw(background);
        m_window->draw(fightSprite);
        m_window->display();
        if (fightAnimationClock.getElapsedTime().asSeconds() < 0.019 && frames > 5) continue;
        if (fightAnimationClock.getElapsedTime().asSeconds() < 0.03 && frames < 5) continue;
        fightAnimationClock.restart();
        counter++;
    }
    m_window->clear();
    m_window->draw(background);
    m_window->display();
}

void Controller::initNames() {
    m_p1Name.setFont(*ResourcesManager::instance().getFont());
    m_p2Name.setFont(*ResourcesManager::instance().getFont());
    m_p1Name.setCharacterSize(H3);
    m_p2Name.setCharacterSize(H3);
    m_p1Name.setFillColor(sf::Color::Blue);
    m_p2Name.setFillColor(sf::Color::Red);
    m_p1Name.setString(m_p1->getPlayerModel().m_name);
    m_p2Name.setString(m_p2->getPlayerModel().m_name);
    m_p1Name.setOrigin(m_p1Name.getGlobalBounds().width / 2, m_p1Name.getGlobalBounds().height / 2);
    m_p2Name.setOrigin(m_p2Name.getGlobalBounds().width / 2, m_p2Name.getGlobalBounds().height / 2);
    m_p1Name.setPosition(BOARD_FRAME.left + BOARD_FRAME.width / 2,
                         BOARD_FRAME.top + BOARD_FRAME.height +
                         m_p1Name.getGlobalBounds().height);
    m_p2Name.setPosition(BOARD_FRAME.left + BOARD_FRAME.width / 2,
                         BOARD_FRAME.top - m_p2Name.getGlobalBounds().height - RECT_SIZE / 2);
}
