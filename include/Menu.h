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
    void getAmountOfAvailableRooms();
    void print();
    void handleHover(sf::Event::MouseMoveEvent &event);
    void handleClick(sf::Event::MouseButtonEvent *click = NULL);
    sf::Text m_menuButtons[MENU_BUTTONS];
    int m_roomsSize = 0;
    bool m_moving = false;
    sf::Clock m_movingAnimation;
    int moveArr[20] = {15,30,0,-30,-15,-15,-30,0,30,15,
                       15,30,0,-30,-15,-15,-30,0,30,15};
    sf::Text m_roomsAmount;
    sf::Text m_noRooms;
    bool m_delay = false;
    int m_indicator = 0;
    std::string m_textNames[MENU_BUTTONS] = {"Create Room","Join Room","Settings","Help","Exit"};
    std::shared_ptr<sf::RenderWindow> m_window;
    sf::RectangleShape m_background;
    void lightButton();
    void handleKeyboard(sf::Event::KeyEvent &type);
};