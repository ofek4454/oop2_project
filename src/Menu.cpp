#include "Menu.h"

void wrapperFunction(SettingsScreen* obj) {
    obj->run();
}

Menu::Menu() : m_window(WindowManager::instance().getWindow()) {
    ResourcesManager::instance().playBackgroundMusic();
    float starting_y = WINDOW_HEIGHT * 0.35f;
    float starting_x = WINDOW_WIDTH / 2.f;
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    m_noRooms = TextClass("No Rooms Available",H2,sf::Vector2f(WINDOW_WIDTH * 0.5,WINDOW_HEIGHT * 0.95),sf::Color::Red).getText();
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_menuButtons[i] = TextClass(m_textNames[i], H2, sf::Vector2f(starting_x, starting_y)).getText();
        m_menuButtons[i].setOutlineThickness(0);
        starting_y += H2 * 2;
    }
    m_roomsAmount = TextClass("Rooms: 0", H3,sf::Vector2f (m_menuButtons[1].getPosition().x + m_menuButtons[1].getGlobalBounds().width,m_menuButtons[1].getPosition().y + H3*0.2)).getText();
    getAmountOfAvailableRooms();
    handleEvents();
}

void Menu::handleEvents() {
    print();
    sf::Clock roomsClock;
    int movingIndicator = 0;
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                handleHover(move);
                return false;
            },
            [this](auto click, auto exit) {
                SoundFlip::instance().checkIfMouseContains(click);
                handleClick(&click);
                return false;
            },
            [this](auto key, auto exit) {
                SoundFlip::instance().checkIfKeyboard(key);
                handleKeyboard(key);
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this, &roomsClock,&movingIndicator](auto exit) {
                if(m_moving && m_movingAnimation.getElapsedTime().asSeconds() > 0.01){
                    m_movingAnimation.restart();
                    m_roomsAmount.move(sf::Vector2f(moveArr[movingIndicator],0));
                    movingIndicator++;
                    if(movingIndicator == 20){
                        m_moving = false;
                        m_delay = true;
                        movingIndicator = 0;
                    }
                }
                if (roomsClock.getElapsedTime().asSeconds() > 2) {
                    roomsClock.restart();
                    getAmountOfAvailableRooms();
                }
                lightButton();
                print();
            }
    );

}

void Menu::print() {
    m_window->clear();
    m_window->draw(m_background);
    if(m_indicator == 1){
        m_window->draw(m_roomsAmount);
    }
    if(m_moving || m_delay && m_movingAnimation.getElapsedTime().asSeconds() < 1 )
        m_window->draw(m_noRooms);
    else{
        m_delay = false;
    }
    SoundFlip::instance().draw(*m_window);

    for (const auto &btn: m_menuButtons)
        m_window->draw(btn);

    m_window->display();
}

void Menu::handleHover(sf::Event::MouseMoveEvent &event) {
    bool hoverd = false;
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_menuButtons[i].getGlobalBounds().contains(event.x, event.y)) {
            hoverd = true;
            m_indicator = i;
        }
    }
    if (!hoverd)
        m_indicator = -1;
}

void Menu::handleClick(sf::Event::MouseButtonEvent *event) {
    if (event) {
        m_indicator = -1;
        for (int i = 0; i < MENU_BUTTONS; i++)
            if (m_menuButtons[i].getGlobalBounds().contains(event->x, event->y)) {
                m_indicator = i;
            }
    }
    if (m_indicator >= 0 && m_indicator < MENU_BUTTONS) {
        switch (m_indicator) {
            case 0: {
                auto nameScreen = EnterNameScreen(Mode_t(0));
                break;
            }
            case 1: {
                if(m_roomsSize > 0)
                    auto nameScreen = EnterNameScreen(Mode_t(1));
                else
                    m_moving = true;
                break;
            }
            case 2: {
                SettingsScreen settingsScreen(m_window);
                settingsScreen.run();
                break;
            }
            case 3: {
                HelpScreen();
                break;
            }
            case 4: {
                m_window->close();
                break;
            }
            default:
                break;
        }
    }
}

void Menu::handleKeyboard(sf::Event::KeyEvent &type) {
    if (type.code == sf::Keyboard::Enter)
        handleClick();
    if (type.code == sf::Keyboard::Down) {
        if (m_indicator < MENU_BUTTONS - 1)
            m_indicator++;
    }
    if (type.code == sf::Keyboard::Up) {
        if (m_indicator > 0)
            m_indicator--;
    }
}

void Menu::lightButton() {
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_indicator == i)
            m_menuButtons[i].setOutlineThickness(2);
        else
            m_menuButtons[i].setOutlineThickness(0);

    }
}

void Menu::getAmountOfAvailableRooms() {
    auto room = RoomService::getAvailableRooms();
    if (m_roomsSize != room.size()) {
        m_roomsSize = room.size();
        m_roomsAmount.setString("Rooms: " + std::to_string(m_roomsSize));
    }
}
