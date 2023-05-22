#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"

class Menu{
public:
    Menu();
private:
    void handleEvents();
    sf::RenderWindow *m_window;
};