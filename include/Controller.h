#pragma once

#include "Board.h"
#include "WindowManager.h"
#include "EnemyState.h"
#include "UserState.h"

class Controller {
public:
    Controller() ;

private:
    void print();
    void eventsHandler();
    sf::RenderWindow *m_window;
    Board m_board;
    std::unique_ptr<PlayerState> m_enemy;
    std::unique_ptr<PlayerState> m_user;

    sf::Vector2f m_playerChosen;
};


