#include "Menu.h"

Menu::Menu() : m_window(WindowManager::instance().getWindow()) {
    ResourcesManager::instance().playBackgroundMusic();
    int starting_y = WINDOW_HEIGHT * 0.3;
    int starting_x = WINDOW_WIDTH / 2;
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_menuButtons[i] = TextClass(m_textNames[i], H2, sf::Vector2f(starting_x, starting_y)).getText();
        m_menuButtons[i].setOutlineThickness(0);
        starting_y += H2 * 2;
    }
    handleEvents();
}

void Menu::handleEvents() {
    print();

    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                handleHover(move);
                return false;
            },
            [this](auto click, auto exit) {
                SoundFlip::instance().checkIfContains(click);
                handleClick(&click);
                return false;
            },
            [this](auto key, auto exit) {
                handleKeyboard(key);
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this](auto exit) {
                lightButton();
                print();
            }
    );

}

void Menu::print() {
    m_window->clear();
    m_window->draw(m_background);
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
    if(event) {
        m_indicator = -1;
        for(int i = 0; i < MENU_BUTTONS; i++)
            if(m_menuButtons[i].getGlobalBounds().contains(event->x, event->y)){
                m_indicator = i;
            }
    }
    if (m_indicator >= 0 && m_indicator < MENU_BUTTONS) {
        switch (m_indicator) {
            case 0: {
                EnterNameScreen(Mode_t(0));
                break;
            }
            case 1: {
                EnterNameScreen(Mode_t(1));
                break;
            }
            case 2: {
                SettingsScreen settingsScreen = SettingsScreen(*m_window);
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
    if(type.code == sf::Keyboard::Enter)
        handleClick();
    if (type.code == sf::Keyboard::Down) {
        if (m_indicator < MENU_BUTTONS-1)
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
