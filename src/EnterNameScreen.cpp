//
// Created by Ofek Gorgi on 27/05/2023.
//

#include "EnterNameScreen.h"
#include "Controller.h"

EnterNameScreen::EnterNameScreen(Mode_t mode) : m_mode(mode) , m_window(WindowManager::instance().getWindow()) , m_name(""){
    init();
    handleEvents();
}

void EnterNameScreen::init() {
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_title.setFont(*ResourcesManager::instance().getFont());
    m_title.setString("Enter you name:");
    m_title.setCharacterSize(WINDOW_HEIGHT*0.06);
    m_title.setPosition(WINDOW_WIDTH*0.5, WINDOW_HEIGHT*0.4);
    m_title.setOrigin(m_title.getGlobalBounds().width/2,m_title.getGlobalBounds().height/2);
    m_nameText.setFont(*ResourcesManager::instance().getFont());
    m_nameText.setString("");
    m_nameText.setCharacterSize(WINDOW_HEIGHT*0.075);
    m_nameText.setPosition(WINDOW_WIDTH*0.5, m_title.getPosition().y + m_title.getGlobalBounds().height*2);
}

void EnterNameScreen::handleEvents() {
    print();
    while(m_window->isOpen()){
        sf::Event event;
        while (m_window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                m_window->close();
            if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter){
                std::unique_ptr<PlayerState> p1;
                std::unique_ptr<PlayerState> p2;
                if(m_mode == Create){
                    // TODO Create room
                    p1 = std::make_unique<UserState>(m_name,"uid");
                    p2 = std::make_unique<EnemyState>("enemy", "uid");
                } else {
                    // TODO Join room
                    p2 = std::make_unique<UserState>(m_name,"uid");
                    p1 = std::make_unique<EnemyState>("enemy", "uid");
                }
                Controller(&p1,&p2);
            }
            if(event.type == event.KeyPressed && event.key.code == sf::Keyboard::BackSpace){
                if (!m_name.empty()){
                    m_name.pop_back();
                    m_nameText.setString(m_name);
                    print();
                }
                continue;
            }
            if (event.type == sf::Event::TextEntered){
                if (event.text.unicode == '\b')
                    continue;
                if (m_name.size() < 20)
                    m_name += event.text.unicode;
                m_nameText.setString(m_name);
                print();
            }
        }
    }
}

void EnterNameScreen::print() {
    m_nameText.setOrigin(m_nameText.getGlobalBounds().width/2,m_nameText.getGlobalBounds().height/2);

    m_window->clear();
    m_window->draw(m_background);
    m_window->draw(m_title);
    m_window->draw(m_nameText);
    m_window->display();
}
