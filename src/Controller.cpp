//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"
#include "SoundFlip.h"
#include "RoomState.h"

Controller::Controller(std::unique_ptr<PlayerState> *p1, std::unique_ptr<PlayerState> *p2, bool isMeP1) : m_window(
        WindowManager::instance().getWindow()), m_user(p1->get()), m_enemy(p2->get()), m_serverTurn(isMeP1) {

    m_user->setPlayerSymbol(!isMeP1 ? "1" : "2");
    m_enemy->setPlayerSymbol(isMeP1 ? "1" : "2");
    m_user->init();
    m_enemy->init();
    m_turn = (Turn_t)RoomState::instance().getTurn();
    initGame();
    run();
}

void Controller::run() {
    print();
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                if (m_turn == m_serverTurn)
                    handleHover(move);
                else return true;
                return false;
            },
            [this](auto click, auto exit) {
                SoundFlip::instance().checkIfContains(click);
                if (m_turn == m_serverTurn) {
                    m_user->doTurn(&click);
                } else return true;
                return false;
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this](auto exit) {
                if (m_turn != m_serverTurn && !m_enemy->isAnimating() && !m_switchingTurn) {
                    static sf::Clock clock;
                    if(clock.getElapsedTime().asSeconds() > 1.5){
                        clock.restart().asSeconds();
                        if(isMyTurn()){
                            m_enemy->doTurn();
                        }
                    }
                }
                handleAnimation();
                handleEvents();
                checkCollision();
                if (m_switchingTurn)
                    changeTurnAnimation();
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
    m_user->print();
    m_enemy->print();
    m_window->draw(m_referee);
    SoundFlip::instance().draw(*m_window);


    m_window->display();
}


void Controller::checkCollision() {
    auto p1_vec = m_user->getAllWarriors();
    auto p2_vec = m_enemy->getAllWarriors();
    for (auto &p1: *p1_vec)
        for (auto &p2: *p2_vec)
            if (p1->getLocation() == p2->getLocation()) {
                p2->getWeapon()->get()->fight(**p1->getWeapon());
                m_currentP1 = p1.get();
                m_currentP2 = p2.get();
                m_currentP1->setNeedToBeDraw(false);
                m_currentP2->setNeedToBeDraw(false);
            }

    m_user->checkDeletion();
    m_enemy->checkDeletion();
}

void Controller::handleAnimation() {
    if (!m_user->isAnimating() && !m_enemy->isAnimating()) return;
    static sf::Clock clock;
    auto time = clock.getElapsedTime().asSeconds();
    if (time > 0.025) {
        clock.restart().asSeconds();
        if (m_turn == m_serverTurn && m_user->move()) {
            m_user->setAnimating(false);
            m_switchingTurn = true;
            return;
        }
        if (m_turn != m_serverTurn && m_enemy->move()) {
            m_enemy->setAnimating(false);
            m_switchingTurn = true;
            // clear waiting events
            sf::Event event;
            while (m_window->pollEvent(event));
            return;
        }
    }
}

void Controller::handleHover(sf::Event::MouseMoveEvent &event) {
    if (BOARD_FRAME.contains(event.x, event.y)) {
        sf::FloatRect rect_pos = BOARD_TOP_LEFT;
        int row = (event.y - rect_pos.top) / RECT_SIZE;
        int col = (event.x - rect_pos.left) / RECT_SIZE;
        m_user->handleHover(row, col);
    }
}

void Controller::handleEvents() {
    while (EventLoop::instance().hasEvent()) {
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()) {
            case FightRP:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BluePR : RedPR), 980,
                             84, 7, winP);
                break;
            case FightRS:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueRS : RedRS), 994,
                             93, 7, winR);
                break;
            case FightRR:
                animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3, tieR);
                break;
            case FightPS:
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 900,
                             96, 6, winS);
                break;
            case FightPP:
                animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3, tieP);
                break;
            case FightSS:
                animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3, tieS);
                break;
            case UndefinedChoose: {
                animateFight(ResourcesManager::instance().getTexture(BlueSP), 300,
                             96, 2);
                ResourcesManager::instance().playSound(ChooseWeapon);
                auto warrior1 = m_user->getWarrior(m_user->getWarriorLocation());
                if (warrior1 != NULL) {
                    warrior1->get()->getWeapon()->get()->chooseWeapon();
                }
                break;
            }
            case UndefinedUndefined: {
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 300,
                             96, 2);
                ResourcesManager::instance().playSound(ChooseWeapon);
                auto warrior1 = m_user->getWarrior(m_user->getWarriorLocation());
                if (warrior1 != NULL) {
                    warrior1->get()->getWeapon()->get()->chooseWeapon();
                }
                auto warrior2 = m_enemy->getWarrior(m_enemy->getWarriorLocation());
                if (warrior2 != NULL) {
                    warrior2->get()->getWeapon()->get()->chooseWeapon();
                }
                break;
            }
            default:
                break;
        }
        ResourcesManager::instance().playSound(event.getWinner() == P1Won ? WinFight : event.getWinner() == P2Won ? LoseFight : NUMBER_OF_SOUNDS - 1);
        if(event.getWinner() == P1Won || event.getWinner() == P2Won){
            m_currentP1->setNeedToBeDraw(true);
            m_currentP2->setNeedToBeDraw(true);
            sf::sleep(sf::seconds(1.5));
        }
    }

}

void Controller::animateFight(sf::Texture *fightTexture, const int width, const int height, const int frames,
                              Sounds_t soundToPlay) {
    ResourcesManager::instance().playSound(JumpFight);
    float frameWidth = width / frames;
    float frame = 0;
    int currentFrameCounter = 0;
    float arr[frames * 8];
    for (int i = 0; i < frames * 8; i++) {
        if (i % 8 == 0 && i != 0)
            frame += frameWidth;
        arr[i] = frame;
    }

    sf::Clock fightAnimationClock;
    sf::Texture bg;
    bg.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    bg.update(*m_window);

    sf::Sprite background(bg);
    sf::Sprite fightSprite(*fightTexture);

    auto boardBounds = BOARD_FRAME;
    fightSprite.setPosition(boardBounds.left + boardBounds.width / 2 - RECT_SIZE / 2,
                            boardBounds.top + boardBounds.height / 2 - RECT_SIZE / 2);
    fightSprite.setOrigin(frameWidth / 2, height);
    fightSprite.setScale(2.2, 2.2);
    while (currentFrameCounter < frames * 8) {
        fightSprite.setTextureRect(sf::IntRect(arr[currentFrameCounter], 0, frameWidth, height));
        m_window->clear();
        m_window->draw(background);
        m_window->draw(fightSprite);
        m_window->display();
        if (fightAnimationClock.getElapsedTime().asSeconds() < 0.019 && frames > 5) continue;
        if (fightAnimationClock.getElapsedTime().asSeconds() < 0.03 && frames < 5) continue;
        fightAnimationClock.restart();
        currentFrameCounter++;
        if (currentFrameCounter == frames * 4 && soundToPlay != NoSound) {
            ResourcesManager::instance().playSound(soundToPlay);
        }
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
    m_p1Name.setString(m_user->getPlayerModel().m_name);
    m_p2Name.setString(m_enemy->getPlayerModel().m_name);
    m_p1Name.setOrigin(m_p1Name.getGlobalBounds().width / 2, m_p1Name.getGlobalBounds().height / 2);
    m_p2Name.setOrigin(m_p2Name.getGlobalBounds().width / 2, m_p2Name.getGlobalBounds().height / 2);
    m_p1Name.setPosition(BOARD_FRAME.left - RECT_SIZE / 2 + BOARD_FRAME.width / 2,
                         BOARD_FRAME.top - RECT_SIZE / 2 + BOARD_FRAME.height +
                         m_p1Name.getGlobalBounds().height);
    m_p2Name.setPosition(BOARD_FRAME.left - RECT_SIZE / 2 + BOARD_FRAME.width / 2,
                         BOARD_FRAME.top - RECT_SIZE / 2 - m_p2Name.getGlobalBounds().height - RECT_SIZE / 2);
}

void Controller::initGame() {
    auto frameRectSize = sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH * 0.775,
                                      WINDOW_HEIGHT * 0.685 - WINDOW_HEIGHT * 0.355);
    m_referee.setTexture(*ResourcesManager::instance().getTexture(Referee));
    m_referee.setScale((frameRectSize.x / 241.5) * 0.6, (frameRectSize.y / 164) * 0.6);
    m_referee.setTextureRect(sf::IntRect(0, 0, 241.5, 164));
    m_referee.setPosition(
            sf::Vector2f(WINDOW_WIDTH * 0.775 + ((WINDOW_WIDTH - WINDOW_WIDTH * 0.775) / 2) -
                         (m_referee.getGlobalBounds().width / 2),
                         WINDOW_HEIGHT * 0.355 + ((WINDOW_WIDTH - WINDOW_WIDTH * 0.775,
                                 WINDOW_HEIGHT * 0.685 - WINDOW_HEIGHT * 0.355) / 2) -
                         (m_referee.getGlobalBounds().height / 2)));
    m_refereeRect += (m_serverTurn == P1) ? 0 : 724.5;
    m_referee.setTextureRect(sf::IntRect(m_refereeRect, 0, 241.5, 164));

    bool flagChoosed = false;
    initNames();
    WindowManager::instance().eventHandler(
            [this, &flagChoosed](auto move, auto exit) {
                if (!BOARD_FRAME.contains(move.x, move.y)) return true;
                sf::FloatRect rect_pos = BOARD_TOP_LEFT;
                int row = (move.y - rect_pos.top) / rect_pos.height;
                int col = (move.x - rect_pos.left) / rect_pos.width;
                if (!flagChoosed) m_user->hoverFlag(row, col);
                else m_user->hoverHole(row, col);
                return false;
            },
            [this, &flagChoosed](auto click, auto &exit) {
                if (!BOARD_FRAME.contains(click.x, click.y)) return true;
                sf::FloatRect rect_pos = BOARD_TOP_LEFT;
                int row = (click.y - rect_pos.top) / rect_pos.height;
                int col = (click.x - rect_pos.left) / rect_pos.width;
                if (row < BOARD_SIZE - 2) return true;
                if (!flagChoosed){
                    if (m_user->setAsFlag(row, col))
                        flagChoosed = true;
                }
                else{
                    if (m_user->setAsHole(row, col))
                        exit = true;
                }

                return false;
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto &exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this](auto exit) {
                print();
            }
    );
    RoomState::instance().uploadFlagAndHole();
    /*
    std::pair<Location,Location> opponentFlagAndHole;
    sf::Clock clock;
    do{
        if(clock.getElapsedTime().asSeconds() < 1) continue;
        clock.restart();
        opponentFlagAndHole = RoomState::instance().getOpponentFlagAndHole();
    } while (opponentFlagAndHole.first == Location(-1,-1));

    m_enemy->setAsFlag(opponentFlagAndHole.first.row,opponentFlagAndHole.first.col);
    m_enemy->setAsHole(opponentFlagAndHole.second.row,opponentFlagAndHole.second.col);*/
}

void Controller::changeTurnAnimation() {
    static sf::Clock animationClock;
    auto time = animationClock.getElapsedTime().asSeconds();
    if (time > 0.1) {
        animationClock.restart().asSeconds();
        m_refereeRect += (m_turn == m_serverTurn) ? 241.5 : -241.5;
        if (m_refereeRect >= 724.5 && m_turn == m_serverTurn) {
            m_switchingTurn = false;
            ResourcesManager::instance().playSound(redTurn);
            m_turn = (Turn_t)!m_serverTurn;
            RoomState::instance().changeTurn(m_turn);
            RoomState::instance().upload();
        }
        if (m_refereeRect <= 0 && m_turn != m_serverTurn) {
            m_switchingTurn = false;
            ResourcesManager::instance().playSound(blueTurn);
            m_turn = (Turn_t)m_serverTurn;
        }
        m_referee.setTextureRect(sf::IntRect(m_refereeRect, 0, 241.5, 164));
    }
}
