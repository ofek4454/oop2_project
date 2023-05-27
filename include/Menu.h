#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "EnemyState.h"
#include "UserState.h"

class Menu{
public:
    Menu();
private:
    void handleEvents();
    void print();
    void handleHover();
    void handleClick(sf::Event::MouseButtonEvent &click);
    void printNameInput();
    sf::Text m_menuButtons[MENU_BUTTONS];
    sf::Font m_font;

    sf::Text m_name;
    sf::Text m_instruction;
    std::string m_textNames[MENU_BUTTONS] = {"Create Room","Join Room","Settings","Help","Exit"};
    sf::RenderWindow *m_window;
    sf::RectangleShape m_background;

    std::string m_p1Name;
    std::string m_p2Name = "zona";

    std::unique_ptr<PlayerState> m_p1;
    std::unique_ptr<PlayerState> m_p2;


    void getName(bool isP1);
};