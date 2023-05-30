#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "WindowManager.h"
#include "Controller.h"
#include "SettingsScreen.h"
#include "SoundFlip.h"

class Menu{
public:
    Menu();
private:
    void handleEvents();
    void print();
    void handleHover(sf::Event::MouseMoveEvent &event);
    void handleClick(sf::Event::MouseButtonEvent &click);
    sf::Text m_menuButtons[MENU_BUTTONS];

    std::string m_textNames[MENU_BUTTONS] = {"Create Room","Join Room","Settings","Help","Exit"};
    sf::RenderWindow *m_window;
    sf::RectangleShape m_background;

};