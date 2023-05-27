#include "Menu.h"
#include "WindowManager.h"


Menu::Menu() : m_window(WindowManager::instance().getWindow()) {
    m_font = *ResourcesManager::instance().getFont();
    int starting_y = WINDOW_HEIGHT / 2 - RECT_SIZE;
    int starting_x = WINDOW_WIDTH / 2 - 30;
    m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setTexture(ResourcesManager::instance().getTexture(Background));
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_menuButtons[i].setFont(m_font);
        m_menuButtons[i].setCharacterSize(90);
        m_menuButtons[i].setFillColor(sf::Color(240, 255, 220));
        m_menuButtons[i].setString(m_textNames[i]);
        m_menuButtons[i].setOrigin(
                sf::Vector2f(m_menuButtons[i].getGlobalBounds().width / 2,
                             m_menuButtons[i].getGlobalBounds().height / 2));
        m_menuButtons[i].setPosition(sf::Vector2f(starting_x, starting_y));
        starting_y += m_menuButtons[i].getGlobalBounds().height + 70;
    }

    m_name.setFont(m_font);
    m_instruction.setFont(m_font);
    m_instruction.setCharacterSize(60);
    m_instruction.setString("Please Enter You Name");
    m_instruction.setPosition(sf::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2));
    m_name.setPosition(sf::Vector2f(m_instruction.getPosition().x + m_instruction.getGlobalBounds().width / 3,
                                    m_instruction.getPosition().y + m_instruction.getGlobalBounds().height + 40));

    handleEvents();

}

void Menu::handleEvents() {
    print();
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                handleClick(event.mouseButton);
            }
            handleHover();
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


void Menu::handleHover() {
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_menuButtons[i].getGlobalBounds().contains(
                m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)))) {
            m_menuButtons[i].setOutlineThickness(2);
            m_menuButtons[i].setOutlineColor(sf::Color::Black);
        } else {
            m_menuButtons[i].setFillColor(sf::Color(240, 255, 220));
            m_menuButtons[i].setOutlineThickness(0);
        }
    }
}

void Menu::handleClick(sf::Event::MouseButtonEvent &click) {
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_menuButtons[i].getGlobalBounds().contains(m_window->mapPixelToCoords({click.x, click.y}))) {
            switch (i) {
                case 0: {
                    getName();
//                    Controller controller;
                    break;
                }
                case 1: {
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

void Menu::getName() {
    std::string input;
    printNameInput();
    sf::Event event;
    while (m_window->waitEvent(event)) {
        if (event.type == sf::Event::TextEntered) {

            if (std::isprint(event.text.unicode))
                input += event.text.unicode;
            if (isspace(event.key.code))
                if (std::isprint(event.text.unicode))
                    input += event.text.unicode;

            m_name.setString(input);
        }
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Return)
                break;
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::BackSpace)
                if (!input.empty())
                    input.pop_back();

        printNameInput();
    }
    m_p1Name = input;

}

void Menu::printNameInput() {
    m_window->clear();
    m_window->draw(m_background);
    m_window->draw(m_instruction);
    m_window->draw(m_name);
    m_window->display();
}
