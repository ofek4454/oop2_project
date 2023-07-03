#include "WindowManager.h"


void WindowManager::eventHandler(std::function<bool(sf::Event::MouseMoveEvent, bool &exit)> moveHandler,
                                 std::function<bool(sf::Event::MouseButtonEvent ,bool &exit)> clickHandler,
                                 std::function<bool(sf::Event::KeyEvent, bool &exit)> keyPressedHandler,
                                 std::function<bool(sf::Event::TextEvent, bool &exit)> typeHandler,
                                 std::function<bool(int offset, bool &exit)> scrollHandler,
                                 std::function<void(bool &exit)> afterFunction) {

    bool exit = false;
    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (clickHandler(event.mouseButton, exit)) continue;
            } else if (event.type == sf::Event::MouseMoved) {
                if (moveHandler(event.mouseMove, exit)) continue;
            } else if (event.type == sf::Event::KeyPressed) {
                if (keyPressedHandler(event.key, exit)) continue;
            } else if (event.type == sf::Event::TextEntered) {
                if (typeHandler(event.text, exit))continue;
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                if (scrollHandler(event.mouseWheelScroll.delta * 3, exit)) continue;
            }
        }
        if (exit) return;
        afterFunction(exit);

    }
}

