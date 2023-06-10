//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"
#include "SoundFlip.h"
#include "RoomState.h"
#include "exception"
#include "cmath"

Controller::Controller(std::unique_ptr<PlayerState> *p1, std::unique_ptr<PlayerState> *p2, bool isMeP1) : m_window(
        WindowManager::instance().getWindow()), m_user(p1->get()), m_enemy(p2->get()), myTurn(isMeP1 ? P1 : P2),
                                                                                                          m_referee(
                                                                                                                  isMeP1
                                                                                                                  ? P1
                                                                                                                  : P2) {
    m_countdown.setFont(*ResourcesManager::instance().getFont());
    m_countdown.setCharacterSize(64);
    m_countdown.setFillColor(sf::Color::White);
    m_countdown.setStyle(sf::Text::Bold);
    m_circle.setFillColor(sf::Color::Transparent);
    m_circle.setOutlineThickness(2.0f);
    m_circle.setOutlineColor(sf::Color::White);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775 + ((WINDOW_HEIGHT * 0.95 - WINDOW_HEIGHT * 0.775)) + 10,
                                      WINDOW_HEIGHT * 0.685 - radius +
                                      (WINDOW_HEIGHT * 0.95 - WINDOW_HEIGHT * 0.685 + 10)));
//    m_shuffleButton.setSize(sf::Vector2f(WINDOW_WIDTH * 0.19, WINDOW_HEIGHT * 0.1));
//    m_shuffleButton.setTexture(ResourcesManager::instance().getTexture(ShuffleButton));
//    m_shuffleButton.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.775 + 10,
//                                             WINDOW_HEIGHT * 0.355 - m_shuffleButton.getGlobalBounds().height - 10));
    m_user->setPlayerSymbol(isMeP1 ? "1" : "2");
    m_enemy->setPlayerSymbol(!isMeP1 ? "1" : "2");
    m_user->init();
    m_enemy->init();
    initGame();
    run();
}

void Controller::run() {
    LoadingGame();
    print();
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                if (isMyTurn() && !m_user->isAnimating())
                    handleHover(move);
                else return true;
                return false;
            },
            [this](auto click, auto exit) {
                SoundFlip::instance().checkIfContains(click);
                if (isMyTurn() && !m_user->isAnimating()) {
                    m_user->doTurn(&click);
                } else return true;
                return false;
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this](auto exit) {
                if (!isMyTurn() && !m_enemy->isAnimating()) {
                    static sf::Clock clock;
                    if (clock.getElapsedTime().asSeconds() > 0.2) {
                        clock.restart().asSeconds();
                        if (RoomState::instance().getTurn() == myTurn) {
                            if (RoomState::instance().getRoom().getLastMove().starts_with("tie")) {
                                // attacker only
                                handleTie();
                            }
                            else if (RoomState::instance().getRoom().getLastMove().starts_with("Win")){
                                m_turn = myTurn;
                                EventLoop::instance().addEvent(Lose);
                            }
                            else
                                m_enemy->doTurn();
                        }
                    }
                }
                handleAnimation();
                if (isMyTurn()) {
                    checkCollision();
                    handleEvents();
                }
                print();
            }
    );
}

void Controller::print(bool printLoad) {
    m_window->clear();
    m_window->draw(*ResourcesManager::instance().getBackground());
    m_board.print();
    m_window->draw(m_p1Name);
    m_window->draw(m_p2Name);
    m_user->print();
    m_enemy->print();
    SoundFlip::instance().draw(*m_window);
    m_referee.print();
    if (printLoad) {
        m_window->draw(m_circle);
        float angleIncrement = 2 * M_PI / numLines;
        for (int i = 0; i < numLines; ++i) {
            float angle = i * angleIncrement;
            sf::CircleShape line(radius / 15.0f);
            line.setFillColor(sf::Color::White);
            line.setOrigin(line.getRadius(), line.getRadius());
            line.setPosition(std::cos(angle) * (radius - line.getRadius()) + m_circle.getPosition().x,
                             std::sin(angle) * (radius - line.getRadius()) + m_circle.getPosition().y);
            m_window->draw(line);
        }
//        m_window->draw(m_shuffleButton);
        m_window->draw(m_countdown);
    }
    m_window->display();
}


void Controller::checkCollision() {
    auto p1_vec = m_user->getAllWarriors();
    auto p2_vec = m_enemy->getAllWarriors();
    for (auto &p1: *p1_vec)
        for (auto &p2: *p2_vec)
            if (p1->getLocation() == p2->getLocation()) {
                m_user->setWarriorLocation(p1->getLocation());
                m_isFinishUserTurn = false;
                p2->getWeapon()->get()->fight(**p1->getWeapon());
                m_currentP1 = p1.get();
                m_currentP2 = p2.get();
                m_currentP1->setNeedToBeDraw(false);
                m_currentP2->setNeedToBeDraw(false);

            }
}

void Controller::handleAnimation() {
    static sf::Clock animateWeaponClock;
    auto time1 = animateWeaponClock.getElapsedTime().asSeconds();
    if ((time1 > 2 && !isMyTurn()) || m_animatingWeapon) {
        animateWeaponClock.restart();
        animateWeapons();
    }
    m_referee.animate((Turn_t) !isMyTurn());
    if (m_playHoleAniation) {
        animateHole();
    }
    if (!m_user->isAnimating() && !m_enemy->isAnimating()) return;
    static sf::Clock clock;
    auto time2 = clock.getElapsedTime().asSeconds();

    if (time2 > 0.025) { //0.025
        clock.restart().asSeconds();
        if (isMyTurn() && m_user->move()) {
            m_isFinishUserTurn = true;
        } else if (!isMyTurn() && m_enemy->move()) {
            // clear waiting events
            sf::Event event;
            while (m_window->pollEvent(event));
            m_turn = (Turn_t) myTurn;
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
    if (m_isFinishUserTurn && !EventLoop::instance().hasEvent()) {
        RoomState::instance().changeTurn();
        m_turn = (Turn_t) !myTurn;
        m_isFinishUserTurn = false;
    }
    while (EventLoop::instance().hasEvent()) {
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()) {
            case NeedToResetLocation: {
                auto warrior = m_user->getWarrior(m_user->getWarriorLocation());
                if (warrior == NULL) return;
                warrior->get()->resetLocation();
                break;
            }
            case FightRP: {
                updateLastMoveAndChangeTurn(!m_switchTurnAfterTie);
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BluePR : RedPR), 980,
                             84, 7, winP);
                m_switchTurnAfterTie = false;
                break;
            }
            case FightRS: {
                updateLastMoveAndChangeTurn(!m_switchTurnAfterTie);
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueRS : RedRS), 994,
                             93, 7, winR);
                m_switchTurnAfterTie = false;
                break;
            }
            case FightPS:
                updateLastMoveAndChangeTurn(!m_switchTurnAfterTie);
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 900,
                             96, 6, winS);
                m_switchTurnAfterTie = false;
                break;
            case FightRR:
                updateTieCase("tie R");
                animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3, tieR);
                break;
            case FightPP:
                updateTieCase("tie P");
                animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3, tieP);
                break;
            case FightSS:
                updateTieCase("tie S");
                animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3, tieS);
                break;
            case AttackingUndefined: {
                // attacker only
                updateLastMoveAndChangeTurn(true);
                break;
            }
            case HoleFall: {
                m_playHoleAniation = true;
                if (event.getWinner() == P1Won) m_winner = P1;
                else m_winner = P2;
                updateLastMoveAndChangeTurn(true);
                break;
            }
            case Won:{
                updateWin();
                AfterGameScreen(true,m_user->getPlayerModel(),m_enemy->getPlayerModel(),myTurn);
                exit(EXIT_SUCCESS);
                break;
            }
            case Lose:{
                AfterGameScreen(false,m_user->getPlayerModel(),m_enemy->getPlayerModel(),myTurn);
                exit(EXIT_SUCCESS);
                break;
            }
            default:
                break;
        }
        ResourcesManager::instance().playSound(
                event.getWinner() == P1Won ? WinFight : event.getWinner() == P2Won ? LoseFight : NUMBER_OF_SOUNDS - 1);
        if (event.getWinner() != Tie && event.getWinner() != NoneEvent) {
            m_currentP1->setNeedToBeDraw(true);
            m_currentP2->setNeedToBeDraw(true);
            m_currentP1->getWeapon()->get()->setVisible(true);
            m_currentP2->getWeapon()->get()->setVisible(true);
        }
    }
    m_user->checkDeletion();
    m_enemy->checkDeletion();
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
                if (!flagChoosed) {
                    if (m_user->setAsFlag(row, col)) {
                        userFlag = m_user->getWarrior(Location(row, col))->get();
                        flagChoosed = true;
                    }
                } else {
                    if (m_user->setAsHole(row, col)) {
                        exit = true;
                        userHole = m_user->getWarrior(Location(row, col))->get();
                    }
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

    std::pair<Location, Location> opponentFlagAndHole;
    sf::Clock clock;
    do {
        if (clock.getElapsedTime().asSeconds() < 1) continue;
        clock.restart();
        opponentFlagAndHole = RoomState::instance().getOpponentFlagAndHole();
    } while (opponentFlagAndHole.first == Location(-1, -1));

    m_turn = P1;

    Location flagLoc = myTurn == P1 ? opponentFlagAndHole.first
                                    : Location(BOARD_SIZE - opponentFlagAndHole.first.row - 1,
                                               BOARD_SIZE - opponentFlagAndHole.first.col - 1);
    Location holeLoc = myTurn == P1 ? opponentFlagAndHole.second
                                    : Location(BOARD_SIZE - opponentFlagAndHole.second.row - 1,
                                               BOARD_SIZE - opponentFlagAndHole.second.col - 1);

    m_enemy->setAsFlag(flagLoc.row, flagLoc.col);
    m_enemy->setAsHole(holeLoc.row, holeLoc.col);

    enemyFlag = m_enemy->getWarrior(flagLoc)->get();
    enemyHole = m_enemy->getWarrior(holeLoc)->get();

}

void Controller::updateLastMoveAndChangeTurn(bool changeTurn) {
    auto warrior = m_user->getWarrior(m_user->getWarriorLocation());
    RoomState::instance().setBoardCell(warrior->get()->getLocation(),
                                       m_user->getPlayerSymbol() + warrior->get()->getSymbol());
    RoomState::instance().setLastMove(warrior->get()->getPrevLocation(), warrior->get()->getLocation(),
                                      warrior->get()->getSymbol());
    if (changeTurn) {
        RoomState::instance().changeTurn();
        m_turn = (Turn_t) !myTurn;
    }
}

void Controller::updateTieCase(std::string msg) {
    // attacked only
    RoomState::instance().setLastMove(msg);
    RoomState::instance().changeTurn();
    m_turn = (Turn_t) !myTurn;

    auto warrior = m_user->getWarrior(m_user->getWarriorLocation());
    warrior->get()->setWeapon(Undefined_t);
    auto enemy = m_enemy->getWarrior(m_enemy->getWarriorLocation());
    enemy->get()->setWeapon(Undefined_t);
    m_switchTurnAfterTie = true;
}

void Controller::LoadingGame() {
    static sf::Clock timer;
    sf::Clock clock;
    int countdown = 3;
    bool animating = false;
    float scaleFactor = 1.0f;
    const int numSegments = 60; // Number of line segments

    int arr[3] = {0, 116, 232};
    auto p1_vec = m_user->getAllWarriors();
    for (auto &warrior: *p1_vec) {
        if (warrior->getLocation() == userHole->getLocation() ||
            warrior->getLocation() == userFlag->getLocation())
            continue;
        int randomNumber = std::rand() % 3;
        warrior->getWeapon()->get()->setWeaponIntRect(arr[randomNumber]);
    }

    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) { return false; },
            [this](auto click, auto exit) {
                SoundFlip::instance().checkIfContains(click);
                return false;
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto &exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this, &countdown, &clock, &animating, &scaleFactor](auto &exit) {

                sf::Time elapsed = clock.getElapsedTime();
                if (elapsed.asSeconds() >= 1.0f) {
                    countdown--;
                    clock.restart();
                    animating = true;
                    scaleFactor = 1.5f;
                    if (countdown < 1) {
                        exit = true;
                        auto p1_vec = m_user->getAllWarriors();
                        for (auto &warrior: *p1_vec) {
                            if (warrior->getLocation() == userHole->getLocation() ||
                                warrior->getLocation() == userFlag->getLocation())
                                continue;
                            warrior->getWeapon()->get()->removeWeaponTexture();
                        }
                        return;
                    }

                    int arr[3] = {58, 174, 290};
                    auto p1_vec = m_user->getAllWarriors();
                    for (auto &warrior: *p1_vec) {
                        if (warrior->getLocation() == userHole->getLocation() ||
                            warrior->getLocation() == userFlag->getLocation())
                            continue;
                        int randomNumber = std::rand() % 3;
                        warrior->getWeapon()->get()->setWeaponIntRect(arr[randomNumber]);
                    }
                }

                if (animating) {
                    m_countdown.setScale(scaleFactor, scaleFactor);
                    scaleFactor -= 0.05f;
                    if (scaleFactor <= 1.0f) {
                        animating = false;
                        m_countdown.setScale(1.0f, 1.0f);
                    }
                }

                m_countdown.setString(std::to_string(countdown));
                sf::FloatRect textBounds = m_countdown.getLocalBounds();
                m_countdown.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                      textBounds.top + textBounds.height / 2.0f);
                m_countdown.setPosition(m_circle.getPosition().x, m_circle.getPosition().y);
                float completion = std::min(1.0f, elapsed.asSeconds());
                numLines = static_cast<int>(numSegments * completion);

                print(true);
            }
    );

}

void Controller::handleTie() {
    std::string lastMove = RoomState::instance().getRoom().getLastMove();
    switch (lastMove[lastMove.size() - 1]) {
        case 'R':
            animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3, tieR);
            break;
        case 'P':
            animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3, tieP);
            break;
        case 'S':
            animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3, tieS);
            break;
    }

    auto warrior = m_user->getWarrior(m_user->getWarriorLocation());
    warrior->get()->setWeapon(Undefined_t);

    auto enemy = m_enemy->getWarrior(m_enemy->getWarriorLocation());
    enemy->get()->setWeapon(Undefined_t);
    m_turn = myTurn;
}

void Controller::animateWeapons() {
    static bool chose = false;
    if (!chose) {
        ChosenWarrior = m_user->pickRandomWarrior();
        if (ChosenWarrior != NULL && ChosenWarrior->getLocation() != userHole->getLocation() &&
            ChosenWarrior->getLocation() != userFlag->getLocation()) {
            m_animatingWeapon = true;
            ChosenWarrior->setTexture();
            chose = true;
        }
    } else {
        static sf::Clock clock;
        auto time = clock.getElapsedTime().asSeconds();
        if (time > 0.04) {
            clock.restart();
            if (ChosenWarrior->getWeapon()->get()->animateWeapon()) {
                chose = false;
                m_animatingWeapon = false;
                ChosenWarrior->setTexture(true);
            }

        }

//        for (auto &war: *m_enemy->getAllWarriors()) {
//            auto weapon = war->getWeapon()->get();
//            if (weapon->isVisible()) {
//                weapon->animateWeapon();
//            }
//        }
    }
}

void Controller::animateHole() {
    static sf::Clock clock;
    auto time = clock.getElapsedTime().asSeconds();
    if (time > 0.2) {
        clock.restart();
        if (m_winner == P1) {
            if (userHole->setHoleIntRect())
                m_playHoleAniation = false;
        } else {
            if (enemyHole->setHoleIntRect())
                m_playHoleAniation = false;
        }
    }
}

void Controller::updateWin() {
    RoomState::instance().setLastMove("Win");
    RoomState::instance().changeTurn();
    m_turn = (Turn_t) !myTurn;
}

