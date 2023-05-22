#include "Menu.h"
#include "WindowManager.h"
#include "Controller.h"

Menu::Menu() : m_window(WindowManager::instance().getWindow()){
    Controller controller;
    handleEvents();
}

void Menu::handleEvents() {
    while (m_window->isOpen()){
        sf::Event event;
        while (m_window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                m_window->close();
            }
        }
    }

}
