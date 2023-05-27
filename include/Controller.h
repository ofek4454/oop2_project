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

private:
    void print();
    void run();
    void clickHandler(sf::Event::MouseButtonEvent& event);
    void handleEvents();
    void initNames();

    sf::RenderWindow *m_window;
    sf::Texture m_fightTexture;
    sf::Text m_p1Name, m_p2Name;
    Board m_board;
    std::unique_ptr<PlayerState> m_p1;
    std::unique_ptr<PlayerState> m_p2;
    Turn_t m_turn = P1;

    Direction_t m_direction;
    bool m_isMoving = false;
    bool m_isAnimating = false;
    Location m_flagLocation;
    Location m_selectedPlayerLocation;
    void checkCollision();
    void handleHover(sf::Event::MouseMoveEvent &event);
    void handlemoveAnimation();
    void handleAnimation();
    void initFlagAndHole();
    void animateFight(sf::Texture *fightTexture, const int width,const int height, const int frames);
};


