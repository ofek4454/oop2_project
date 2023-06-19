//
// Created by Bar Kobi on 20/05/2023.
//

#include "Controller.h"
#include "SoundFlip.h"
#include "RoomState.h"
#include "exception"

Controller::Controller(PlayerModel p1, PlayerModel p2, bool isMeP1) : m_window(
        WindowManager::instance().getWindow()), m_user(std::make_unique<UserState>(p1)),
                                                                      m_enemy(std::make_unique<EnemyState>(p2)),
                                                                      myTurn(isMeP1 ? P1 : P2),
                                                                      m_referee(isMeP1 ? P1 : P2) {

    m_circleIndicator.setRadius(RECT_SIZE*0.4);
//    m_circleIndicator.setFillColor(sf::Color(BLUE_COLOR.r,BLUE_COLOR.g,BLUE_COLOR.b*0.7,150));
    m_circleIndicator.setFillColor(GRAY_COLOR);
    m_circleIndicator.setOrigin(RECT_SIZE *0.4,RECT_SIZE *0.4);
    m_circleIndicator.setPosition(-2*RECT_SIZE,-2*RECT_SIZE);
    m_originalCursor.loadFromSystem(sf::Cursor::Arrow);
    m_cursor.loadFromSystem(sf::Cursor::Hand);
    m_backButton = TextClass("<-", H2, sf::Vector2f(WINDOW_WIDTH * 0.05,
                                                    WINDOW_HEIGHT * 0.04)).getText();
    m_user->setPlayerSymbol(isMeP1 ? "1" : "2");
    m_enemy->setPlayerSymbol(!isMeP1 ? "1" : "2");
    m_user->init();
    m_enemy->init();
    run();
}

void Controller::run() {
    initGame();
    if (m_distruct || !m_window->isOpen())
        return;
    LoadingGame();
    if (myTurn == P1) {
        sf::Event event;
        while (m_window->pollEvent(event));
    }
    m_gameBar.resetClock(myTurn == P1);

    print();
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                if (isMyTurn() && !m_user->isAnimating()) {
                    handleHover(move);
                    incPlayer();
                }
                else return true;
                return false;
            },
            [this](auto click, auto &exit) {
                SoundFlip::instance().checkIfContains(click);
                if (m_backButton.getGlobalBounds().contains(click.x, click.y))
                    exit = true;
                if (isMyTurn() && !m_user->isAnimating()) {
                    m_user->doTurn(&click);
                    if (m_user->isAnimating())
                        m_indicator = Location(-1, -1);
                } else return true;
                return false;
            },
            [this](auto key, auto exit) {
                if (isMyTurn() && !m_user->isAnimating()) {
                    handleKeyboard(key);
                    incPlayer();
                }
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this](auto &exit) {

                if (!isMyTurn() && !m_enemy->isAnimating()) {
                    enemyTurn(exit);
                    if (exit) return;
                }

                handleAnimation();
                if (isMyTurn()) {
                    checkCollision();
                    handleEvents();
                }
                if (!m_collision)
                    m_gameBar.updateGameBar(m_user->getAllWarriors()->size(), m_enemy->getAllWarriors()->size());
                print();
                if (m_gameDone) exit = true;
            }
    );
}

void Controller::print(bool printLoad) {
    m_window->clear();
    m_window->draw(*ResourcesManager::instance().getBackground());
    m_board.print();
    m_window->draw(m_circleIndicator);
    m_window->draw(m_backButton);
    m_window->draw(m_p1Name);
    m_window->draw(m_p2Name);
    m_user->print();
    m_enemy->print();
    SoundFlip::instance().draw(*m_window);
    m_referee.print();
    if (printLoad)
        m_timeCounting.print();
    else
        m_gameBar.drawStats();
    m_window->display();
}

void Controller::checkCollision() {
    m_collision = false;
    std::string weapon_of_p2;
    auto p1_vec = m_user->getAllWarriors();
    auto p2_vec = m_enemy->getAllWarriors();
    for (auto &p1: *p1_vec)
        for (auto &p2: *p2_vec)
            if (p1.second->getLocation() == p2.second->getLocation()) {
                if ((p1.second->getSymbol() == "U" && p2.second->getSymbol() != "H") ||
                    (p1.second->getSymbol() == "U" && p2.second->getSymbol() != "F"))
                    animateFight(ResourcesManager::instance().getTexture(UndefinedWar), 453, 63, 3, NoSound);
                m_user->setSelectedWarriorId(p1.second->getId());
                m_enemy->setSelectedWarriorId(p2.second->getId());
                m_collision = true;
                weapon_of_p2 = p2.second->getSymbol();
                m_isFinishUserTurn = false;
                p2.second->getWeapon()->fight(*p1.second->getWeapon());
                m_currentP1 = p1.second.get();
                m_currentP2 = p2.second.get();
                m_currentP1->setNeedToBeDraw(false);
                m_currentP2->setNeedToBeDraw(false);

            }
    if ((!m_collision && m_meAttacked) || (m_meAttacked && weapon_of_p2 == "U"))
        m_meAttacked = false;

}

void Controller::handleAnimation() {
    static sf::Clock animateWeaponClock;
    auto time1 = animateWeaponClock.getElapsedTime().asSeconds();
    if ((time1 > 4 && !isMyTurn()) || (m_animatingWeapon && ChosenWarrior->getWeapon())) {
        animateWeaponClock.restart();
        animateWeapons();
    }
    m_referee.animate((Turn_t) !isMyTurn());
    if (m_playHoleAnimation) {
        animateHole();
    }
    if (!m_user->isAnimating() && !m_enemy->isAnimating()) return;
    static sf::Clock clock;
    auto time2 = clock.getElapsedTime().asSeconds();

    if (time2 > 0.025) { //0.025
        clock.restart().asSeconds();
        if (isMyTurn() && m_user->move()) {
            m_meAttacked = true;
            m_indicator = Location(-1, -1);
            m_isFinishUserTurn = true;
        } else if (!isMyTurn() && m_enemy->move()) {
            m_meAttacked = false;
            // clear waiting events
            sf::Event event;
            while (m_window->pollEvent(event));
            m_turn = (Turn_t) myTurn;
            m_gameBar.resetClock(true);
            if (m_switchTurn) {
                m_switchTurn = false;
                RoomState::instance().changeTurn();
                m_turn = (Turn_t) !myTurn;
                m_gameBar.resetClock(false);
                m_indicator = Location(4, 0);
            }
        }
    }
}

void Controller::handleHover(sf::Event::MouseMoveEvent &event) {
    bool hoverd = false;
    if (m_backButton.getGlobalBounds().contains(event.x, event.y))
        m_window->setMouseCursor(m_cursor);
    else
        m_window->setMouseCursor(m_originalCursor);
    if (BOARD_FRAME.contains(event.x, event.y)) {
        hoverd = true;
        m_switchPlayerByKey = false;
        sf::FloatRect rect_pos = BOARD_TOP_LEFT;
        int row = (event.y - rect_pos.top) / RECT_SIZE;
        int col = (event.x - rect_pos.left) / RECT_SIZE;
        m_indicator = Location(row, col);
    }

    if (!hoverd && !m_switchPlayerByKey)
        m_indicator = Location(-1, -1);

}

void Controller::handleEvents() {
    if (m_isFinishUserTurn && !EventLoop::instance().hasEvent()) {
        RoomState::instance().changeTurn();
        m_turn = (Turn_t) !myTurn;
        m_gameBar.resetClock(false);
        m_isFinishUserTurn = false;
    }
    while (EventLoop::instance().hasEvent() && !m_gameDone) {
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()) {
            case FightRP: {
                updateLastMoveAndChangeTurn();
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BluePR : RedPR), 980,
                             84, 7, winP);
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            }
            case FightRS: {
                updateLastMoveAndChangeTurn();
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueRS : RedRS), 994,
                             93, 7, winR);
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            }
            case FightPS:
                updateLastMoveAndChangeTurn();
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 900,
                             96, 6, winS);
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            case FightRR:
                animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3, tieR);
                updateTieCase("tie R");
                break;
            case FightPP:
                animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3, tieP);
                updateTieCase("tie P");
                break;
            case FightSS:
                updateTieCase("tie S");
                animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3, tieS);
                break;
            case AttackingUndefined: {
                // attacker only
                updateLastMoveAndChangeTurn();
                break;
            }
            case HoleFall: {
                m_playHoleAnimation = true;
                if (event.getWinner() == P1Won) m_winner = myTurn;
                else m_winner = !myTurn;
                updateLastMoveAndChangeTurn();
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            }
            case Won: {
                updateLastMoveAndChangeTurn();
                AfterGameScreen(true, m_user->getPlayerModel(), m_enemy->getPlayerModel(), myTurn);
                m_gameDone = true;
                break;
            }
            case Lose: {
                AfterGameScreen(false, m_user->getPlayerModel(), m_enemy->getPlayerModel(), myTurn);
                m_gameDone = true;
                break;
            }
            case TimeOver: {
                m_user->setArrows();
                updateLastMoveAndChangeTurn(true);
                break;
            }
            default:
                break;
        }
        ResourcesManager::instance().playSound(
                event.getWinner() == P1Won ? WinFight : event.getWinner() == P2Won ? LoseFight : NUMBER_OF_SOUNDS - 1);
        if (event.getWinner() != Tie && event.getWinner() != NoneEvent) {
            m_collision = false;
            m_currentP1->setNeedToBeDraw(true);
            m_currentP2->setNeedToBeDraw(true);
            m_currentP1->getWeapon()->setVisible(true);
            m_currentP2->getWeapon()->setVisible(true);
        }
    }
    m_user->checkDeletion();
    m_enemy->checkDeletion();
}

void Controller::animateFight(sf::Texture *fightTexture, const int width, const int height, const int frames,
                              Sounds_t soundToPlay) {
    print();
    ResourcesManager::instance().playSound(JumpFight);
    float frameWidth = width / frames;
    float frame = 0;
    int currentFrameCounter = 0;
    std::vector<float> arr(frames * 8);
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
    m_p2Name.setFillColor(sf::Color(195, 0, 0));
    m_p1Name.setString(m_user->getPlayerModel().m_name);
    m_p2Name.setString(m_enemy->getPlayerModel().m_name);
    m_p1Name.setOrigin(m_p1Name.getGlobalBounds().width / 2, m_p1Name.getGlobalBounds().height / 2);
    m_p2Name.setOrigin(m_p2Name.getGlobalBounds().width / 2, m_p2Name.getGlobalBounds().height / 2);
    m_p1Name.setPosition(BOARD_TOP_LEFT.left + BOARD_FRAME.width / 2,
                         BOARD_TOP_LEFT.top + BOARD_FRAME.height +
                         m_p1Name.getGlobalBounds().height);
    m_p2Name.setPosition(BOARD_TOP_LEFT.left + BOARD_FRAME.width / 2,
                         BOARD_TOP_LEFT.top - m_p2Name.getGlobalBounds().height * 1.5);
}

void Controller::initGame() {
    bool flagChoosed = false;
    initNames();
    WindowManager::instance().eventHandler(
            [this, &flagChoosed](auto move, auto exit) {
                if (m_backButton.getGlobalBounds().contains(move.x, move.y))
                    m_window->setMouseCursor(m_cursor);
                else
                    m_window->setMouseCursor(m_originalCursor);
                if (!BOARD_FRAME.contains(move.x, move.y)) return true;
                sf::FloatRect rect_pos = BOARD_TOP_LEFT;
                int row = (move.y - rect_pos.top) / rect_pos.height;
                int col = (move.x - rect_pos.left) / rect_pos.width;
                if (!flagChoosed) m_user->hoverFlag(row, col);
                else m_user->hoverHole(row, col);
                return false;
            },
            [this, &flagChoosed](auto click, auto &exit) {
                SoundFlip::instance().checkIfContains(click);
                if (m_backButton.getGlobalBounds().contains(click.x, click.y)) {
                    m_distruct = true;
                    exit = true;
                }
                if (!BOARD_FRAME.contains(click.x, click.y)) return true;
                sf::FloatRect rect_pos = BOARD_TOP_LEFT;
                int row = (click.y - rect_pos.top) / rect_pos.height;
                int col = (click.x - rect_pos.left) / rect_pos.width;
                if (row < BOARD_SIZE - 4) return true;
                if (!flagChoosed) {
                    if (m_user->setAsFlag(row, col)) {
                        userFlag = m_user->getWarrior(Location(row, col));
                        flagChoosed = true;
                    }
                } else {
                    if (m_user->setAsHole(row, col)) {
                        exit = true;
                        userHole = m_user->getWarrior(Location(row, col));
                    }
                }

                return false;
            },
            [](auto key, auto exit) { return false; },
            [](auto type, auto &exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this](auto exit) {
                print(true);
            }
    );
    RoomState::instance().uploadFlagAndHole();

    sf::Text t("Waiting for opponent", *ResourcesManager::instance().getFont(), H2);
    t.setPosition(BOARD_FRAME.left + (BOARD_FRAME.width - RECT_SIZE) / 2,
                  BOARD_FRAME.top + (BOARD_FRAME.height - RECT_SIZE) / 2);
    t.setOrigin(t.getGlobalBounds().width / 2, t.getGlobalBounds().height / 2);
    t.setFillColor(sf::Color::White);
    t.setOutlineThickness(2);
    t.setOutlineColor(GRAY_COLOR);

    m_window->draw(t);
    m_window->display();

    std::pair<Location, Location> opponentFlagAndHole;
    sf::Clock clock;
    if (!m_window->isOpen() || m_distruct)
        return;
    do {
        if (clock.getElapsedTime().asSeconds() < 1) continue;
        clock.restart();
        opponentFlagAndHole = RoomState::instance().getOpponentFlagAndHole();
        if (opponentFlagAndHole.first == Location(-2, -2)) {
            m_window->clear();
            m_window->draw(*ResourcesManager::instance().getBackground());
            m_p2Name.setString("User Has Been Logged Out");
            m_window->draw(m_p2Name);
            m_window->display();
            sf::sleep(sf::seconds(1.5));
            m_distruct = true;
            break;
        }
    } while (opponentFlagAndHole.first == Location(-1, -1) && opponentFlagAndHole.second == Location(-1, -1));

    m_turn = P1;

    Location flagLoc = myTurn == P1 ? opponentFlagAndHole.first
                                    : Location(ROWS - opponentFlagAndHole.first.row - 1,
                                               BOARD_SIZE - opponentFlagAndHole.first.col - 1);
    Location holeLoc = myTurn == P1 ? opponentFlagAndHole.second
                                    : Location(ROWS - opponentFlagAndHole.second.row - 1,
                                               BOARD_SIZE - opponentFlagAndHole.second.col - 1);

    m_enemy->setAsFlag(flagLoc.row, flagLoc.col);
    m_enemy->setAsHole(holeLoc.row, holeLoc.col);

    enemyHole = m_enemy->getWarrior(holeLoc);

}

void Controller::updateLastMoveAndChangeTurn(bool timesUp) {
    auto warrior = m_user->getWarrior();
    if (!timesUp) {
        RoomState::instance().setBoardCell(warrior->getLocation(),
                                           m_user->getPlayerSymbol() + warrior->getSymbol());
        RoomState::instance().setLastMove(warrior->getId(), warrior->getLocation(),
                                          warrior->getSymbol());
    } else {
        RoomState::instance().setLastMoveMsg("TimeUp");
    }
    RoomState::instance().changeTurn();
    m_turn = (Turn_t) !myTurn;
    m_gameBar.resetClock(false);
}

void Controller::updateTieCase(std::string msg) {
    // attacked only
    RoomState::instance().setLastMoveTie(msg, m_user->getWarrior()->getLocation(), m_user->getWarrior()->getId());
    RoomState::instance().changeTurn();
    m_turn = (Turn_t) !myTurn;
    m_gameBar.resetClock(false);

    auto warrior = m_user->getWarrior();
    warrior->setWeapon(Undefined_t);

    auto enemy = m_enemy->getWarrior();
    enemy->setWeapon(Undefined_t);
}

void Controller::handleTie() {
    std::string lastMove = RoomState::instance().getRoom().getLastMove();
    switch (lastMove[lastMove.size() - 7]) {
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
    std::string id = lastMove.substr(6, 2);

    int row = myTurn == P1 ? std::atoi(&lastMove[lastMove.size() - 3])
                           : ROWS - 1 - std::atoi(&lastMove[lastMove.size() - 3]);

    int col = myTurn == P1 ? std::atoi(&lastMove[lastMove.size() - 1])
                           : BOARD_SIZE - 1 - std::atoi(&lastMove[lastMove.size() - 1]);

    auto war = m_enemy->getWarrior(id);
    war->setLocation(Location(row, col));
    m_enemy->setSelectedWarriorId(war->getId());
    auto warrior = m_user->getWarrior();
    warrior->setWeapon(Undefined_t);

    auto enemy = m_enemy->getWarrior();
    enemy->setWeapon(Undefined_t);

    m_turn = myTurn;
    m_gameBar.resetClock(true);
}

void Controller::LoadingGame() {
    sf::Clock clock;
    m_timeCounting.setCount(3);
    int arr[3] = {WEP_HEIGHT, WEP_HEIGHT * 3, WEP_HEIGHT * 5};
    auto p1_vec = m_user->getAllWarriors();
    for (auto &warrior: *p1_vec) {
        if (warrior.second->getLocation() == userHole->getLocation() ||
            warrior.second->getLocation() == userFlag->getLocation())
            continue;
        int randomNumber = std::rand() % 3;
        warrior.second->getWeapon()->setWeaponIntRect(arr[randomNumber]);
        warrior.second->getWeapon()->setVisible(true);
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
            [this, &clock, &arr](auto &exit) {
                m_timeCounting.updateCount();
                sf::Time elapsed = clock.getElapsedTime();
                if (elapsed.asSeconds() >= 1.0f) {
                    clock.restart();
                    auto p1_vec = m_user->getAllWarriors();
                    for (auto &warrior: *p1_vec) {
                        if (warrior.second->getLocation() == userHole->getLocation() ||
                            warrior.second->getLocation() == userFlag->getLocation())
                            continue;
                        int randomNumber = std::rand() % 3;
                        warrior.second->getWeapon()->setWeaponIntRect(arr[randomNumber]);
                    }
                }
                if (EventLoop::instance().hasEvent() &&
                    EventLoop::instance().popEvent().getEventType() == TimeOver) {
                    exit = true;
                    auto p1_vec = m_user->getAllWarriors();
                    for (auto &warrior: *p1_vec) {
                        if (warrior.second->getLocation() == userHole->getLocation() ||
                            warrior.second->getLocation() == userFlag->getLocation())
                            continue;
                        warrior.second->getWeapon()->removeWeaponTexture();
                    }
                    return;
                }
                print(true);
            }
    );

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
            if (ChosenWarrior->getWeapon() == NULL) { // check if weapon null
                chose = false;
                m_animatingWeapon = false;
            }
            if (ChosenWarrior->getWeapon()->animateWeapon()) {
                chose = false;
                m_animatingWeapon = false;
                ChosenWarrior->setTexture(true);
            }

        }
    }
}

void Controller::animateHole() {
    static sf::Clock clock;
    auto time = clock.getElapsedTime().asSeconds();
    if (time > 0.5) {
        clock.restart();
        if (m_winner == myTurn) {
            if (userHole->setHoleIntRect(true))
                m_playHoleAnimation = false;
        } else {
            if (enemyHole->setHoleIntRect(false))
                m_playHoleAnimation = false;
        }
    }
}

void Controller::enemyTurn(bool &exit) {
    static sf::Clock clock;
    if (clock.getElapsedTime().asSeconds() > 0.2) {
        clock.restart().asSeconds();
        if (RoomState::instance().getTurn() == myTurn) {
            if (RoomState::instance().getRoom().getLastMove().starts_with("TimeUp")) {
                m_turn = myTurn;
                m_gameBar.resetClock(true);
            } else if (RoomState::instance().getRoom().getLastMove().starts_with("tie")) {
                // attacker only
                handleTie();
            } else if (RoomState::instance().getRoom().getLastMove().starts_with("Logout")) {
                m_window->clear();
                m_window->draw(*ResourcesManager::instance().getBackground());
                m_p2Name.setString("User Has Been Logged Out");
                m_window->draw(m_p2Name);
                m_window->display();
                sf::sleep(sf::seconds(1.5));
                exit = true;
            } else {
                m_enemy->doTurn();
            }
        }
    }
}

Controller::~Controller() {
    RoomState::instance().setLastMoveMsg("Logout");
    RoomState::instance().changeTurn();
    RoomState::instance().upload();
}

void Controller::handleKeyboard(sf::Event::KeyEvent &type) {
    if (type.code == sf::Keyboard::Enter) {
        m_user->doTurn(NULL, &type, m_indicator);
        m_indicator = Location(-1, -1);
    }
    if (type.code == sf::Keyboard::Right) {
        if (m_user->m_playerChose) {
            m_user->doTurn(NULL, &type, m_indicator);
        } else {
            if (m_indicator.col < BOARD_SIZE - 1) {
                m_switchPlayerByKey = true;
                m_indicator.col++;
            }
        }
    }
    if (type.code == sf::Keyboard::Left) {
        if (m_user->m_playerChose) {
            m_user->doTurn(NULL, &type, m_indicator);
        } else {
            if (m_indicator.col > 0) {
                m_switchPlayerByKey = true;
                m_indicator.col--;
            }
        }
    }
    if (type.code == sf::Keyboard::Up) {
        if (m_user->m_playerChose) {
            m_user->doTurn(NULL, &type, m_indicator);
        } else {
            if (m_indicator.row > 0) {
                m_switchPlayerByKey = true;
                m_indicator.row--;
            }
        }

    }
    if (type.code == sf::Keyboard::Down) {
        if (m_user->m_playerChose) {
            m_user->doTurn(NULL, &type, m_indicator);
        } else {
            if (m_indicator.row < ROWS - 1) {
                m_switchPlayerByKey = true;
                m_indicator.row++;
            }
        }
    }
}

void Controller::incPlayer() {
    m_user->handleHover(m_indicator.row, m_indicator.col);
    if(m_indicator != Location(-1,-1))
        m_circleIndicator.setPosition(m_board.getRectPosition(m_indicator));
    else
        m_circleIndicator.setPosition(-2*RECT_SIZE,-2*RECT_SIZE);
}