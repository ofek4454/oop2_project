#pragma once

#include "Board.h"
#include "WindowManager.h"
#include "EnemyState.h"
#include "UserState.h"
#include "iostream"
#include "EventLoop.h"

class Controller {
public:
    Controller(std::unique_ptr<PlayerState>* p1,std::unique_ptr<PlayerState>* p2) ;
    ~Controller() = default;
    void run();

private:
    void print();
    void handleEvents();
    void initNames();

    sf::RenderWindow *m_window;
    sf::Texture m_fightTexture;
    sf::Text m_p1Name, m_p2Name;
    Board m_board;
    std::unique_ptr<PlayerState> m_p1;
    std::unique_ptr<PlayerState> m_p2;
    Turn_t m_turn = P1;

    void checkCollision();
    void handleHover(sf::Event::MouseMoveEvent &click);
    void handlemoveAnimation();
    void handleAnimation();
    void initFlagAndHole();
    void animateFight(sf::Texture *fightTexture, const int width,const int height, const int frames);
};


