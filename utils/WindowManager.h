#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include <functional>

class WindowManager {
public:
    static WindowManager &instance() {
        static WindowManager window;
        return window;
    }

    sf::RenderWindow *getWindow() { return &m_window; }

    void eventHandler(std::function<bool(sf::Event::MouseMoveEvent, bool exit)> moveHandler,
                      std::function<bool(sf::Event::MouseButtonEvent, bool &exit)> clickHandler,
                      std::function<bool(sf::Event::KeyEvent, bool &exit)> keyPressedHandler,
                      std::function<bool(sf::Event::TextEvent, bool &exit)> typeHandler,
                      std::function<void(bool &exit)> afterFunction);

private:
    sf::RenderWindow m_window;

    WindowManager() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                               "Even juk", sf::Style::Close | sf::Style::Titlebar) {}
};

