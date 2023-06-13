//
// Created by Ofek Gorgi on 13/06/2023.
//

#include "ErrorScreen.h"

ErrorScreen::ErrorScreen(std::string error_msg) {

    auto window = WindowManager::instance().getWindow();
    window->clear();

    sf::Text text(error_msg, *ResourcesManager::instance().getFont(), H1);
    text.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Red);
    text.setOutlineThickness(1);

    window->draw(*ResourcesManager::instance().getBackground());
    window->draw(text);
    window->display();

    WindowManager::instance().eventHandler(
            [](auto move, auto exit) { return false; },
            [](auto click, auto &exit) { return false; },
            [this](auto key, auto &exit) {
                if(key.code == sf::Keyboard::Escape)
                    exit = true;
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [](auto &exit) {}
    );
}
