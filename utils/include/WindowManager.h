#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "ResourcesManager.h"
#include <functional>

class WindowManager {
public:
    static WindowManager &instance() {
        static WindowManager window;
        return window;
    }

    WindowManager(const WindowManager &other) = delete;
    WindowManager operator=(const WindowManager &other) = delete;

    sf::RenderWindow *getWindow() { return &m_window; }

    void eventHandler(std::function<bool(sf::Event::MouseMoveEvent, bool &exit)> moveHandler,
                      std::function<bool(sf::Event::MouseButtonEvent, bool &exit)> clickHandler,
                      std::function<bool(sf::Event::KeyEvent, bool &exit)> keyPressedHandler,
                      std::function<bool(sf::Event::TextEvent, bool &exit)> typeHandler,
                      std::function<bool(int offset, bool &exit)> scrollHandler,
                      std::function<void(bool &exit)> afterFunction);

private:
    sf::RenderWindow m_window;

    WindowManager() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                               "Even juk", sf::Style::Close | sf::Style::Titlebar) {

        sf::Image image = (*ResourcesManager::instance().getLogo());
        m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

        m_window.setFramerateLimit(60);
    }
};

