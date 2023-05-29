#pragma once

#include "Board.h"
#include "WindowManager.h"
#include "EnemyState.h"
#include "UserState.h"
#include "iostream"
#include "EventLoop.h"

class Controller {
public:
    // C-Tor
    Controller(std::unique_ptr<PlayerState>* p1,std::unique_ptr<PlayerState>* p2,Turn_t turn = P1) ;
    // D-Tor
    ~Controller() = default;
    // function
    void run();

private:
    // private members
    sf::RenderWindow *m_window;
    sf::Texture m_fightTexture;
    sf::Text m_p1Name, m_p2Name;
    Board m_board;
    std::unique_ptr<PlayerState> m_p1;
    std::unique_ptr<PlayerState> m_p2;
    Turn_t m_turn;
    sf::Sprite m_referee;
    float m_refereeRect;
    bool m_switchingTurn = false;

    const bool m_isMeP1;


    // private functions:
    void changeTurnAnimation();
    void initGame();
    void print();
    void handleEvents();
    void initNames();
    void checkCollision();
    void handleHover(sf::Event::MouseMoveEvent &click);
    void handleAnimation();
    void animateFight(sf::Texture *fightTexture, const int width,const int height, const int frames, Sounds_t soundToPlay = NoSound);
};


