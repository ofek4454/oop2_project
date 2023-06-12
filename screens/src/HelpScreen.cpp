
#include "HelpScreen.h"

HelpScreen::HelpScreen() : m_window(WindowManager::instance().getWindow()),
                           m_pages(ResourcesManager::instance().getHelpScreenPages()) {
    run();
}

void HelpScreen::run() {
    print();
    WindowManager::instance().eventHandler(
            [](auto move, auto exit) { return false; },
            [](auto click, auto &exit) {
                return false;
            },
            [this](auto key, auto &exit) {
                if(key.code == sf::Keyboard::Escape){
                    exit = true;
                }
                if(key.code == sf::Keyboard::Right){
                    if(m_currentPage < NUM_OF_HELP_SCREEN_PAGES-1){
                        m_currentPage++;
                        print();
                    }
                }
                if(key.code == sf::Keyboard::Left){
                    if(m_currentPage > 0){
                        m_currentPage--;
                        print();
                    }
                }
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [](auto &exit) {}
    );
}

void HelpScreen::print() {
    sf::RectangleShape page(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    page.setPosition(0,0);
    page.setTexture(&m_pages[m_currentPage]);
    m_window->clear();
    m_window->draw(page);
    m_window->display();
}
