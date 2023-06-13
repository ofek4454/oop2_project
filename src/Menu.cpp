#include "Menu.h"

Menu::Menu() : m_window(WindowManager::instance().getWindow()) {
    ResourcesManager::instance().playBackgroundMusic();
    int starting_y = WINDOW_HEIGHT * 0.3;
    int starting_x = WINDOW_WIDTH / 2;
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_menuButtons[i].setFont(*ResourcesManager::instance().getFont());
        m_menuButtons[i].setCharacterSize(H2);
        m_menuButtons[i].setFillColor(sf::Color::White);
        m_menuButtons[i].setOutlineColor(sf::Color::Black);
        m_menuButtons[i].setOutlineThickness(0);
        m_menuButtons[i].setString(m_textNames[i]);
        m_menuButtons[i].setOrigin(m_menuButtons[i].getGlobalBounds().width / 2,
                                   m_menuButtons[i].getGlobalBounds().height / 2);
        m_menuButtons[i].setPosition(sf::Vector2f(starting_x, starting_y));
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
                handleClick(click);
                return false;
            },
            [](auto key, auto exit) {return false;},
            [](auto type, auto exit) {return false;},
            [](auto offset,auto exit){return false;},
            [this](auto exit) {
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
    for (auto & btn : m_menuButtons) {
        if (btn.getGlobalBounds().contains(event.x, event.y))
            btn.setOutlineThickness(2);
        else
            btn.setOutlineThickness(0);
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
}
