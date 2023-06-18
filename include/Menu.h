#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "WindowManager.h"
#include "Controller.h"
#include "../screens/include/SettingsScreen.h"
#include "SoundFlip.h"
#include "EnterNameScreen.h"
#include "HelpScreen.h"

class Menu{
public:
    Menu();
private:
    void handleEvents();
    void print();
    void handleHover(sf::Event::MouseMoveEvent &event);
    void handleClick();
    sf::Text m_menuButtons[MENU_BUTTONS];
    int m_indicator = 0;
    bool m_hoverChangedBy = false; // false = Moue true =  keyboard
    std::string m_textNames[MENU_BUTTONS] = {"Create Room","Join Room","Settings","Help","Exit"};
    sf::RenderWindow *m_window;
    sf::RectangleShape m_background;
    void lightButton();
    void handleKeyboard(sf::Event::KeyEvent &type);
};