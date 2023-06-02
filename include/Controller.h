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
    Controller(std::unique_ptr<PlayerState>* p1,std::unique_ptr<PlayerState>* p2, bool isMeP1) ;
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
    std::unique_ptr<PlayerState> m_user;
    std::unique_ptr<PlayerState> m_enemy;
    Turn_t m_turn = P1;
    sf::Sprite m_referee;
    float m_refereeRect;
    bool m_switchingTurn = false;
    Warrior* m_currentP1 = nullptr;
    Warrior* m_currentP2 = nullptr;
    const bool m_serverTurn;
    bool playerFinished = false;


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

    bool isMyTurn(){
        auto turn = RoomState::instance().getTurn();
        std::cout << "room turn: " << turn << " real my turn: " << m_serverTurn << std::endl;
        if(turn == m_serverTurn)
            return true;

        return false;

    }
};


