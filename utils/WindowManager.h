#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"

class WindowManager{
public:
    static WindowManager& instance() {static WindowManager window; return window;}
    sf::RenderWindow *getWindow() {return &m_window;}

private:
    sf::RenderWindow m_window;
    WindowManager() : m_window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
                               "Even juk", sf::Style::Close | sf::Style::Titlebar){}
};