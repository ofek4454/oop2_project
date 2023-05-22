#pragma once

#include "Board.h"
#include "WindowManager.h"
#include "EnemyState.h"
#include "UserState.h"
#include "iostream"



class Controller {
public:
    Controller() ;

private:
    void print();
    void eventsHandler();
    void clickHandler(sf::Event::MouseButtonEvent event);

    sf::RenderWindow *m_window;
    Board m_board;
    std::unique_ptr<PlayerState> m_p1;
    std::unique_ptr<PlayerState> m_p2;

};


