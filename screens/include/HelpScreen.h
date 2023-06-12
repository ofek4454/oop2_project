#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "ResourcesManager.h"
#include "WindowManager.h"

class HelpScreen{
public:
    HelpScreen();

private:
    int m_currentPage = 0;
    sf::Texture *m_pages;
    sf::RenderWindow *m_window;

    void run();
    void print();
};
