//
// Created by Ofek Gorgi on 27/05/2023.
//

#include "../include/EnterNameScreen.h"
#include "../include/AvailableRooms.h"
#include "ErrorScreen.h"
#include "GameException.h"

EnterNameScreen::EnterNameScreen(Mode_t mode) : m_mode(mode), m_window(WindowManager::instance().getWindow()),
                                                m_name("") {
    init();
    handleEvents();
}

void EnterNameScreen::init() {
    m_quitText = TextClass("Press ESC to quit",H2,sf::Vector2f(WINDOW_WIDTH * 0.5,WINDOW_HEIGHT * 0.95)).getText();
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_title = TextClass("Enter you name:", H3, sf::Vector2f(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.4)).getText();
    if (m_mode == Create) {
        m_timeMenu.setTexture(*ResourcesManager::instance().getTexture(GameSeconds));
        m_timeMenu.setTextureRect(sf::IntRect(m_rect[indicator], 0, 256, 256));
        m_timeMenu.setPosition(
                sf::Vector2f(WINDOW_WIDTH * 0.5 - m_timeMenu.getGlobalBounds().width / 2, WINDOW_HEIGHT * 0.7));
        m_Navigation[0] = TextClass("<", H1, sf::Vector2f(m_timeMenu.getPosition().x - WINDOW_WIDTH * 0.1,
                                                          m_timeMenu.getPosition().y +
                                                          m_timeMenu.getGlobalBounds().height / 2)).getText();
        m_Navigation[1] = TextClass(">", H1, sf::Vector2f(
                m_timeMenu.getPosition().x + m_timeMenu.getGlobalBounds().width + WINDOW_WIDTH * 0.1,
                m_timeMenu.getPosition().y + m_timeMenu.getGlobalBounds().height / 2)).getText();
    }
    m_nameText = TextClass("", H2, sf::Vector2f(WINDOW_WIDTH * 0.5, m_title.getPosition().y +
                                                                    m_title.getGlobalBounds().height *
                                                                    2)).getText();
}

void EnterNameScreen::handleEvents() {
    print();
    auto originalScale = m_Navigation[0].getScale();
    WindowManager::instance().eventHandler(
            [this, &originalScale](auto move, auto exit) {
                for (auto &nav: m_Navigation) {
                    if (nav.getGlobalBounds().contains(move.x, move.y))
                        nav.setScale(1.2, 1.2);
                    else
                        nav.setScale(originalScale);
                }
                return false;
            },
            [this](auto click, auto exit) {
                SoundFlip::instance().checkIfMouseContains(click);
                if (m_mode == Create)
                    clickHandler(click);
                return false;
            },
            [this](auto key, auto &exit) {
                SoundFlip::instance().checkIfKeyboard(key);
                if (key.code == sf::Keyboard::Left) {
                    if (indicator > 0)
                        indicator--;
                    setIndicatorTextAndTime();
                }
                if (key.code == sf::Keyboard::Right) {
                    if (indicator < 2)
                        indicator++;
                    setIndicatorTextAndTime();
                }
                if (key.code == sf::Keyboard::Escape) { exit = true; }
                if (key.code == sf::Keyboard::Enter) {
                    if (m_name.empty()) return true;

                    try {
                        auto user = UserService::createUser(m_name);

                        if (m_mode == Create) {
                            RoomState::instance().createRoom(user, gameTime);
                            WaitingRoom(PlayerModel(user));
                            exit = true;
                        } else {
                            AvailableRooms(PlayerModel(user));
                            exit = true;
                        }
                    } catch (HttpException &e) {
                        std::cerr << e.what() << std::endl;
                        ErrorScreen(e.what());
                        exit = true;
                    } catch (GameException &e) {
                        std::cerr << e.what() << std::endl;
                        ErrorScreen(e.what());
                        exit = true;
                    } catch (json::exception &e) {
                        std::cerr << e.what() << std::endl;
                        ErrorScreen(e.what());
                        exit = true;
                    } catch (...) {
                        std::cerr << "Unknown exception was caught!" << std::endl;
                        ErrorScreen("Unknown exception was caught!");
                        exit = true;
                    }
                }
                if (key.code == sf::Keyboard::BackSpace) {
                    if (!m_name.empty()) {
                        m_name.pop_back();
                        m_nameText.setString(m_name);
                        print();
                    }
                    return true;
                }
                return false;
            },
            [this](auto type, auto exit) {
                if (!std::isalnum(type.unicode) && type.unicode != ' ')
                    return true;
                if (m_name.size() < 12)
                    m_name += type.unicode;
                m_nameText.setString(m_name);
                return false;
            },
            [](auto offset, auto exit) { return false; },
            [this](auto exit) {
                print();
            }
    );
}

void EnterNameScreen::print() {
    m_nameText.setOrigin(m_nameText.getGlobalBounds().width / 2, m_nameText.getGlobalBounds().height / 2);
    m_window->clear();
    m_window->draw(m_background);
    SoundFlip::instance().draw(*m_window);
    m_window->draw(m_quitText);
    m_window->draw(m_title);
    m_window->draw(m_nameText);
    if (m_mode == Create) {
        m_window->draw(m_timeMenu);
        m_window->draw(m_Navigation[0]);
        m_window->draw(m_Navigation[1]);
    }
    m_window->display();
}

void EnterNameScreen::clickHandler(auto click) {
    if (m_Navigation[0].getGlobalBounds().contains(click.x, click.y))
        if (indicator > 0)
            indicator--;
    if (m_Navigation[1].getGlobalBounds().contains(click.x, click.y))
        if (indicator < 2)
            indicator++;

    setIndicatorTextAndTime();
}

void EnterNameScreen::setIndicatorTextAndTime() {
    if (indicator == 0)
        gameTime = 30;
    else if (indicator == 1)
        gameTime = 45;
    else
        gameTime = 60;

    m_timeMenu.setTextureRect(sf::IntRect(m_rect[indicator], 0, 256, 256));
}
