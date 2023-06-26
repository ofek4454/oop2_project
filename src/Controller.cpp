#include "Controller.h"
#include "SoundFlip.h"
#include "RoomState.h"
#include "exception"

Controller::Controller(PlayerModel p1, PlayerModel p2, bool isMeP1) : m_window(
        WindowManager::instance().getWindow()), m_user(std::make_unique<UserState>(p1)),
                                                                      m_enemy(std::make_unique<EnemyState>(p2)),
                                                                      myTurn(isMeP1 ? P1 : P2),
                                                                      m_referee(isMeP1 ? P1 : P2) {


    m_user->setPlayerSymbol(isMeP1 ? "1" : "2");
    m_enemy->setPlayerSymbol(!isMeP1 ? "1" : "2");
    m_user->init();
    m_enemy->init();
    m_indicator = Location(4, 0);
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
                } else return true;
                return false;
            },
            [this](auto click, auto &exit) {
                handleClick(click);
                if (m_backButton.getGlobalBounds().contains(click.x, click.y))
                    exit = true;
                if (isMyTurn() && !m_user->isAnimating()) {
                    m_user->doTurn(&click);
                    if (m_user->isAnimating())
                        m_indicator = Location(-1, -1);
                    incPlayer();
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
                if (m_enemy->getEmoji() != NonEmoji_t && m_chatClock.getElapsedTime().asSeconds() > 4) {
                    m_enemy->setEmoji(NonEmoji_t);
                    m_emojiPicked = NonEmoji_t;
                }

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

void Controller::print(bool printLoad, bool fight) {
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
    if (printLoad) {
        m_window->draw(m_LoadingText);
        m_timeCounting.print();
    } else
        m_gameBar.drawStats();

    m_window->draw(m_chatIcon);
    if (m_isChatPressed) {
        for (auto &menuEmoji: m_emojis)
            m_window->draw(menuEmoji);
    }
    if (m_emojiPicked != NonEmoji_t)
        m_window->draw(m_pickedEmojiSprite);
    if (m_enemy->getEmoji() != NonEmoji_t) {
        m_window->draw(m_chatBubble);
        m_window->draw(m_enemyEmoji);
    }
    if (fight) {
        m_tempBackgroundTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
        m_tempBackgroundTexture.update(*m_window);
    }
    if (m_attackingUndefined)
        m_window->draw(m_lastFrameWar);

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
                m_enemy->getWarrior()->setLocation(p1.second->getLocation());
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
    if (ChosenWarrior && ChosenWarrior->getWeapon() != NULL && ((time1 > 4 && !isMyTurn()) || m_animatingWeapon)) {
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
                auto warrior = m_user->getWarrior();
                if (warrior != NULL) {
                    RoomState::instance().setLastMove(warrior->getId(), warrior->getLocation(),
                                                      warrior->getSymbol());
                }
                RoomState::instance().changeTurn();
                m_turn = (Turn_t) !myTurn;
                m_gameBar.resetClock(false);
            }
            m_indicator = Location(m_user->getFirstWarrior()->getLocation().row,
                                   m_user->getFirstWarrior()->getLocation().col);
            m_emojiPicked = NonEmoji_t;
        }
    }
}

void Controller::handleHover(sf::Event::MouseMoveEvent &event) {
    if (m_emojiPicked != NonEmoji_t && m_pickedEmojiSprite.getGlobalBounds().contains(event.x, event.y)) {
        m_currentCursor = TrashCursor;
        m_window->setMouseCursor(m_deleteCursor);
    } else {
        if (m_currentCursor != ClickCursor) {
            m_currentCursor = OriginalCursor;
            m_window->setMouseCursor(m_originalCursor);
        }
    }

    if (m_backButton.getGlobalBounds().contains(event.x, event.y)) {
        m_currentCursor = ClickCursor;
        m_window->setMouseCursor(m_cursor);
    } else {
        if (m_currentCursor != TrashCursor) {
            m_currentCursor = OriginalCursor;
            m_window->setMouseCursor(m_originalCursor);
        }
    }

    bool hoverd = false;
    if (BOARD_TOP_LEFT.contains(event.x, event.y)) {
        hoverd = true;
        m_switchPlayerByKey = false;
        sf::FloatRect rect_pos = BOARD_TOP_LEFT;
        int row = (event.y - rect_pos.top) / RECT_SIZE;
        int col = (event.x - rect_pos.left) / RECT_SIZE;
        m_indicator = Location(row, col);
    }

    for (int i = 0; i < 6; i++) {
        if (m_emojis[i].getGlobalBounds().contains(event.x, event.y))
            m_emojis[i].setScale((RECT_SIZE / 600.f) * 0.6f, (RECT_SIZE / 600.f) * 0.6f);
        else
            m_emojis[i].setScale((RECT_SIZE / 600.f) * 0.5f, (RECT_SIZE / 600.f) * 0.5f);

    }

    if (!hoverd && !m_switchPlayerByKey)
        m_indicator = Location(-1, -1);

}

void Controller::handleEvents() {
    if (m_isFinishUserTurn && !EventLoop::instance().hasEvent()) {
        RoomState::instance().setLastEmoji(m_emojiPicked);
        RoomState::instance().changeTurn();
        m_turn = (Turn_t) !myTurn;
        m_gameBar.resetClock(false);
        m_isFinishUserTurn = false;
    }
    while (EventLoop::instance().hasEvent() && !m_gameDone) {
        auto event = EventLoop::instance().popEvent();
        switch (event.getEventType()) {
            case FightRP: {
                m_attackingUndefined = false;
                updateLastMoveAndChangeTurn();
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BluePR : RedPR), 980,
                             84, 7, winP);
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            }
            case FightRS: {
                m_attackingUndefined = false;
                updateLastMoveAndChangeTurn();
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueRS : RedRS), 994,
                             93, 7, winR);
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            }
            case FightPS:
                m_attackingUndefined = false;
                updateLastMoveAndChangeTurn();
                animateFight(ResourcesManager::instance().getTexture(event.getWinner() == P1Won ? BlueSP : RedSP), 900,
                             96, 6, winS);
                if (m_meAttacked)
                    m_switchTurn = true;
                break;
            case FightRR:
                m_attackingUndefined = false;
                animateFight(ResourcesManager::instance().getTexture(RockRock), 327, 53, 3, tieR);
                updateTieCase("tie R");
                break;
            case FightPP:
                m_attackingUndefined = false;
                animateFight(ResourcesManager::instance().getTexture(PaperPaper), 453, 63, 3, tieP);
                updateTieCase("tie P");
                break;
            case FightSS:
                m_attackingUndefined = false;
                updateTieCase("tie S");
                animateFight(ResourcesManager::instance().getTexture(ScissorsScissors), 306, 59, 3, tieS);
                break;
            case AttackingUndefined: {
                m_attackingUndefined = true;
                // attacker only
                updateLastMoveAndChangeTurn();
                auto wep = m_user->getWarrior()->getWeapon()->getSymbol();
                switch (wep[0]) {
                    case 'S': {
                        animateFight(ResourcesManager::instance().getTexture(ScissorsUndefined), 453, 63, 3, NoSound);
                        break;
                    }
                    case 'R': {
                        animateFight(ResourcesManager::instance().getTexture(RockUndefined), 453, 63, 3, NoSound);
                        break;
                    }
                    case 'P': {
                        animateFight(ResourcesManager::instance().getTexture(PaperUndefined), 453, 63, 3, NoSound);
                        break;
                    }
                }
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
                auto afterScreen = AfterGameScreen(true, m_user->getPlayerModel(), m_enemy->getPlayerModel(), myTurn);
                m_gameDone = true;
                break;
            }
            case Lose: {
                auto afterScreen = AfterGameScreen(false, m_user->getPlayerModel(), m_enemy->getPlayerModel(), myTurn);
                m_gameDone = true;
                break;
            }
            case TimeOver: {
                if (m_user->isAnimating())
                    return;
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

void Controller::animateFight(sf::Texture *fightTexture, int width, int height, int frames,
                              Sounds_t soundToPlay) {
    print(false, true);
    ResourcesManager::instance().playSound(JumpFight);
    float frameWidth = (float)width / frames;
    float frame = 0;
    int currentFrameCounter = 0;
    std::vector<float> arr(frames * 8);
    for (int i = 0; i < frames * 8; i++) {
        if (i % 8 == 0 && i != 0)
            frame += frameWidth;
        arr[i] = frame;
    }
    sf::Clock fightAnimationClock;


    m_tempBackground.setTexture(m_tempBackgroundTexture);
    sf::Sprite fightSprite(*fightTexture);

    fightSprite.setPosition(BOARD_FRAME.left + BOARD_FRAME.width / 2.f - RECT_SIZE / 2.f,
                            BOARD_FRAME.top + BOARD_FRAME.height / 2.f - RECT_SIZE / 2.f);
    fightSprite.setOrigin(frameWidth / 2.f, height);
    fightSprite.setScale(BOARD_FRAME.width*0.5f/ frameWidth, BOARD_FRAME.width * 0.5f / frameWidth); // 2.2,2.2 FIXME
    if (m_attackingUndefined) {
        m_lastFrameWar.setTexture(*fightTexture);
        m_lastFrameWar.setTextureRect(sf::IntRect(arr[frames * 7], 0, frameWidth, height));
        m_lastFrameWar.setPosition(BOARD_FRAME.left + BOARD_FRAME.width / 2.f - RECT_SIZE / 2.f,
                                   BOARD_FRAME.top + BOARD_FRAME.height / 2.f - RECT_SIZE / 2.f);
        m_lastFrameWar.setOrigin(frameWidth / 2.f, height);
        m_lastFrameWar.setScale(BOARD_FRAME.width * 0.5f / frameWidth, BOARD_FRAME.width * 0.5f / frameWidth);
    }
    while (currentFrameCounter < frames * 8) {
        fightSprite.setTextureRect(sf::IntRect(arr[currentFrameCounter], 0, frameWidth, height));
        m_window->clear();
        m_window->draw(m_tempBackground);
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
    m_window->draw(m_tempBackground);
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
                         H3);
    m_p2Name.setPosition(BOARD_TOP_LEFT.left + BOARD_FRAME.width / 2,
                         BOARD_TOP_LEFT.top - H3 * 1.5);
}

void Controller::initGame() {
    bool flagChoosed = false;
    initNames();
    setSpritesAndTxts();
    WindowManager::instance().eventHandler(
            [this, &flagChoosed](auto move, auto exit) {
                if (m_backButton.getGlobalBounds().contains(move.x, move.y))
                    m_window->setMouseCursor(m_cursor);
                else
                    m_window->setMouseCursor(m_originalCursor);
                if (!BOARD_TOP_LEFT.contains(move.x, move.y)) return true;
                sf::FloatRect rect_pos = BOARD_TOP_LEFT;
                int row = (move.y - rect_pos.top) / RECT_SIZE;
                int col = (move.x - rect_pos.left) / RECT_SIZE;
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
                if (!BOARD_TOP_LEFT.contains(click.x, click.y)) return true;
                sf::FloatRect rect_pos = BOARD_TOP_LEFT;
                int row = (click.y - rect_pos.top) / RECT_SIZE;
                int col = (click.x - rect_pos.left) / RECT_SIZE;
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

    m_LoadingText = TextClass("Waiting For Opponent..", H2,
                              sf::Vector2f(BOARD_FRAME.left + (BOARD_FRAME.width - RECT_SIZE) / 2,
                                           BOARD_FRAME.top + (BOARD_FRAME.height - RECT_SIZE) / 2)).getText();
    print(true);

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
        RoomState::instance().setLastEmoji(m_emojiPicked);
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
    m_enemy->setSelectedWarriorId(id);
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
    ResourcesManager::instance().playSound(Gong);
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
            } else {
                m_enemy->doTurn();
                if (m_enemy->getEmoji() != NonEmoji_t) {
                    m_chatClock.restart();
                    m_enemyEmoji.setTexture(*m_emojis[m_enemy->getEmoji()].getTexture());
                }
            }
        }
    }
}

Controller::~Controller() {
    if(!m_gameDone)
        RoomState::instance().logout();
}

void Controller::handleKeyboard(sf::Event::KeyEvent &type) {
    if (type.code == sf::Keyboard::Enter) {
        m_user->doTurn(NULL, &type, m_indicator);
        if (m_user->isAnimating())
            m_indicator = Location(-1, -1);
    }
    if (type.code == sf::Keyboard::Right) {
        if (m_user->m_playerChose) {
            m_user->doTurn(NULL, &type, m_indicator);
            m_indicator = Location(-1, -1);
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
            m_indicator = Location(-1, -1);
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
            m_indicator = Location(-1, -1);
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
            m_indicator = Location(-1, -1);
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
    if (m_indicator.row == -1 || m_indicator.col == -1)
        m_circleIndicator.setPosition(-1000, -1000);
    else
        m_circleIndicator.setPosition(m_board.getRectPosition(m_indicator));

}

void Controller::setSpritesAndTxts() {
    m_chatIcon.setTexture(*ResourcesManager::instance().getTexture(ChatMenu));
    m_chatIcon.setScale((RECT_SIZE / m_chatIcon.getGlobalBounds().width) * 0.9,
                        (RECT_SIZE / m_chatIcon.getGlobalBounds().height) * 0.9);
    m_chatIcon.setPosition(WINDOW_WIDTH * 0.027, WINDOW_HEIGHT * 0.85);
    m_emojis[Cry_t].setTexture(*ResourcesManager::instance().getTexture(CryEmoji));
    m_emojis[Laugh_t].setTexture(*ResourcesManager::instance().getTexture(LaughEmoji));
    m_emojis[Angry_t].setTexture(*ResourcesManager::instance().getTexture(AngryEmoji));
    m_emojis[Sleep_t].setTexture(*ResourcesManager::instance().getTexture(SleepEmoji));
    m_emojis[Finger_t].setTexture(*ResourcesManager::instance().getTexture(FingerEmoji));
    m_emojis[Scammer_t].setTexture(*ResourcesManager::instance().getTexture(ScammerEmoji));

    float y = m_chatIcon.getPosition().y - m_chatIcon.getGlobalBounds().height * 0.8;
    for (int i = 0; i < 6; i++) {
        m_emojis[i].setScale((RECT_SIZE / 600) * 0.5, (RECT_SIZE / 600) * 0.5);
        m_emojis[i].setOrigin(m_emojis[i].getGlobalBounds().width / 2, m_emojis[i].getGlobalBounds().height / 2);
        m_emojis[i].setPosition(m_chatIcon.getPosition().x + m_emojis[i].getGlobalBounds().width / 4, y);
        y -= m_emojis[i].getGlobalBounds().height * 1.6;
    }
    m_circleIndicator.setRadius(RECT_SIZE * 0.4);
    m_circleIndicator.setFillColor(sf::Color(10, 10, 10, 100));
    m_circleIndicator.setOrigin(RECT_SIZE * 0.4, RECT_SIZE * 0.4);
    m_circleIndicator.setPosition(-RECT_SIZE * RECT_SIZE, -RECT_SIZE * RECT_SIZE);
    m_originalCursor.loadFromSystem(sf::Cursor::Arrow);
    m_cursor.loadFromSystem(sf::Cursor::Hand);
    m_deleteCursor.loadFromSystem(sf::Cursor::NotAllowed);
    m_backButton = TextClass("<-", H2, sf::Vector2f(WINDOW_WIDTH * 0.05,
                                                    WINDOW_HEIGHT * 0.04)).getText();
    m_LoadingText = TextClass("Choose Your Own Flag and Hole", H2,
                              sf::Vector2f(BOARD_FRAME.left + (BOARD_FRAME.width - RECT_SIZE) / 2,
                                           BOARD_FRAME.top + (BOARD_FRAME.height - RECT_SIZE) / 2)).getText();
    m_LoadingText.setOutlineThickness(2);
    m_chatBubble.setTexture(*ResourcesManager::instance().getTexture(ChatBubble));
    m_chatBubble.setPosition(m_p2Name.getPosition().x + m_p2Name.getGlobalBounds().width + RECT_SIZE * 0.4,
                             m_p2Name.getPosition().y);// + m_p2Name.getGlobalBounds().width/2 );
    m_chatBubble.setOrigin(m_chatBubble.getGlobalBounds().width / 2, m_chatBubble.getGlobalBounds().height / 2);
    m_chatBubble.setScale(-(m_emojis[Cry_t].getGlobalBounds().width / (m_chatBubble.getGlobalBounds().width * 0.475)),
                          -(m_emojis[Cry_t].getGlobalBounds().height / (m_chatBubble.getGlobalBounds().height * 0.475)));
    m_chatBubble.setRotation(-45);

    m_enemyEmoji.setScale((RECT_SIZE / 600) * 0.5, (RECT_SIZE / 600) * 0.5);
    m_enemyEmoji.setOrigin(m_enemyEmoji.getGlobalBounds().width / 2, m_enemyEmoji.getGlobalBounds().height / 2);
    m_enemyEmoji.setPosition(m_chatBubble.getPosition().x - m_chatBubble.getGlobalBounds().width * 0.07,
                             m_chatBubble.getPosition().y - m_chatBubble.getGlobalBounds().height * 0.22);

    m_pickedEmojiSprite.setScale((RECT_SIZE / 600.f) * 0.5, (RECT_SIZE / 600) * 0.5);
    m_pickedEmojiSprite.setPosition(m_p1Name.getGlobalBounds().width * 0.8 + m_p1Name.getPosition().x,
                                    m_p1Name.getPosition().y - m_p1Name.getGlobalBounds().height / 2);
}

void Controller::handleClick(sf::Event::MouseButtonEvent &click) {
    if (m_emojiPicked != NonEmoji_t && m_pickedEmojiSprite.getGlobalBounds().contains(click.x, click.y)) {
        m_currentCursor = OriginalCursor;
        m_emojiPicked = NonEmoji_t;
    }

    SoundFlip::instance().checkIfContains(click);
    if (!m_isChatPressed && isMyTurn() && m_chatIcon.getGlobalBounds().contains(click.x, click.y)) {
        m_isChatPressed = !m_isFinishUserTurn;
        return;
    }

    if (m_isChatPressed && isMyTurn()) {
        bool isPressed = false;
        for (int i = 0; i < 6; i++) {
            if (m_emojis[i].getGlobalBounds().contains(click.x, click.y)) {
                isPressed = true;
                m_pickedEmojiSprite.setTexture(*m_emojis[i].getTexture());
                m_emojiPicked = Emojis(i);
                m_isChatPressed = false;
            }
        }
        if (!isPressed)
            m_isChatPressed = false;
    }
}
