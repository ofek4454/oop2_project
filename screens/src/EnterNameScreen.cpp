//
// Created by Ofek Gorgi on 27/05/2023.
//

#include "../include/EnterNameScreen.h"
#include "../include/AvailableRooms.h"
#include "ErrorScreen.h"
#include "GameException.h"

EnterNameScreen::EnterNameScreen(Mode_t mode) : m_mode(mode) , m_window(WindowManager::instance().getWindow()) , m_name(""){
    init();
    handleEvents();
}

void EnterNameScreen::init() {
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_title = TextClass("Enter you name:",H3,sf::Vector2f (WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.4)).getText();
    m_nameText = TextClass("",H2,sf::Vector2f (WINDOW_WIDTH*0.5, m_title.getPosition().y + m_title.getGlobalBounds().height*2)).getText();
}

void EnterNameScreen::handleEvents() {
    print();

    WindowManager::instance().eventHandler(
            [](auto move, auto exit) {return false;},
            [](auto click, auto exit) {return false;},
            [this](auto key, auto &exit) {
                if(key.code == sf::Keyboard::Escape){ exit = true; }
                if(key.code == sf::Keyboard::Enter){
                    if(m_name.empty()) return true;

                    try{
                        auto user = UserService::createUser(m_name);

                        if(m_mode == Create){
                            RoomState::instance().createRoom(user);
                            WaitingRoom(PlayerModel(user));
                            exit = true;
                        } else {
                            AvailableRooms(PlayerModel(user));
                            exit = true;
                        }
                    }catch(HttpException &e) {
                        std::cerr << e.what() << std::endl;
                        ErrorScreen(e.what());
                        exit = true;
                    } catch(GameException &e) {
                        std::cerr << e.what() << std::endl;
                        ErrorScreen(e.what());
                        exit = true;
                    } catch (json::exception &e) {
                        std::cerr << e.what() << std::endl;
                        ErrorScreen(e.what());
                        exit = true;
                    }catch (...){
                        std::cerr << "Unknown exception was caught!" << std::endl;
                        ErrorScreen("Unknown exception was caught!");
                        exit = true;
                    }
                }
                if(key.code == sf::Keyboard::BackSpace){
                    if (!m_name.empty()){
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
                if (m_name.size() < 20)
                    m_name += type.unicode;
                m_nameText.setString(m_name);
                print();
                return false;
            },
            [](auto offset,auto exit){return false;},
            [this](auto exit) {}
    );
}

void EnterNameScreen::print() {
    m_nameText.setOrigin(m_nameText.getGlobalBounds().width/2,m_nameText.getGlobalBounds().height/2);
    m_window->clear();
    m_window->draw(m_background);
    m_window->draw(m_title);
    m_window->draw(m_nameText);
    m_window->display();
}
