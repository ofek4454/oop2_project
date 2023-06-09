#pragma once

#include "Board.h"
#include "WindowManager.h"
#include "EnemyState.h"
#include "UserState.h"
#include "iostream"
#include "EventLoop.h"
#include "Referee.h"


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
    sf::Text m_countdown;
    sf::CircleShape m_circle;
    sf::Cursor m_cursor;
    sf::Cursor m_originalCursor;
//    sf::RectangleShape m_shuffleButton;
    // Board
    Board m_board;

    // Players
    std::unique_ptr<PlayerState> m_user;
    std::unique_ptr<PlayerState> m_enemy;
    Warrior* m_currentP1 = nullptr;
    Warrior* m_currentP2 = nullptr;
    Referee m_referee;
    Warrior *userHole;
    Warrior *enemyHole;
    Warrior *userFlag;
    Warrior *enemyFlag;

    // booleans
    Turn_t m_turn = P1;
    const Turn_t myTurn;
    bool m_isFinishUserTurn = false;
    bool m_playHoleAniation = false;
    bool m_winner;
    bool m_switchTurnAfterTie = false;

    // numbers
    int numLines;
    float radius = 100.0f;


    // private functions:
    void LoadingGame();
    void initGame();
    void print(bool printLoad = false);
    void handleEvents();
    void initNames();
    void checkCollision();
    void handleHover(sf::Event::MouseMoveEvent &click);
    void handleAnimation();
    void animateFight(sf::Texture *fightTexture, const int width,const int height, const int frames, Sounds_t soundToPlay = NoSound);
    void updateLastMoveAndChangeTurn(bool changeTurn);
    void updateTieCase(std::string msg);
    void handleClick(sf::Event::MouseButtonEvent *click);
    void handleTie();

    bool isMyTurn() const{
        return m_turn == myTurn;
    }
};


