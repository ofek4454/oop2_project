#include "Menu.h"
#include "EnterNameScreen.h"

Menu::Menu() : m_window(WindowManager::instance().getWindow()) {
    int starting_y = WINDOW_HEIGHT* 0.3;
    int starting_x = WINDOW_WIDTH / 2;
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_menuButtons[i].setFont(*ResourcesManager::instance().getFont());
        m_menuButtons[i].setCharacterSize(WINDOW_HEIGHT*0.075);
        m_menuButtons[i].setFillColor(sf::Color::White);
        m_menuButtons[i].setString(m_textNames[i]);
        m_menuButtons[i].setOrigin(m_menuButtons[i].getGlobalBounds().width / 2,
                                   m_menuButtons[i].getGlobalBounds().height / 2);
        m_menuButtons[i].setPosition(sf::Vector2f(starting_x, starting_y));
        starting_y += m_menuButtons[i].getGlobalBounds().height * 2;
    }

    handleEvents();

}

void Menu::handleEvents() {
    print();
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window->close();
            if (event.type == sf::Event::MouseButtonReleased)
                handleClick(event.mouseButton);
            if (event.type == sf::Event::MouseMoved)
                handleHover(event.mouseMove);
        }
        print();
    }

}

void Menu::print() {
    m_window->clear();
    m_window->draw(m_background);
    for (auto &btn: m_menuButtons) {
        m_window->draw(btn);
    }
    m_window->display();
}


void Menu::handleHover(sf::Event::MouseMoveEvent &event) {
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_menuButtons[i].getGlobalBounds().contains(event.x, event.y)) {
            m_menuButtons[i].setOutlineThickness(2);
            m_menuButtons[i].setOutlineColor(sf::Color::Black);
        } else
            m_menuButtons[i].setOutlineThickness(0);
    }
}

void Menu::handleClick(sf::Event::MouseButtonEvent &click) {
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_menuButtons[i].getGlobalBounds().contains(m_window->mapPixelToCoords({click.x, click.y}))) {
            switch (i) {
                case 0: {
                    EnterNameScreen(Mode_t(0));
                    break;
                }
                case 1: {
                    EnterNameScreen(Mode_t(1));
                    break;
                }
                case 2: {

                }
                case 3: {

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
}
