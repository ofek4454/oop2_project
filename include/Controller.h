#pragma once

#include "Board.h"
#include "WindowManager.h"
#include "EnemyState.h"
#include "UserState.h"
#include "iostream"
#include "EventLoop.h"
#include "Referee.h"
#include "AfterGameScreen.h"
#include "GameBar.h"
#include "TimeCounting.h"


class Controller {
public:
    // C-Tor
    Controller(PlayerModel p1, PlayerModel p2, bool isMeP1) ;
    // D-Tor
    ~Controller() = default;
    // function
    void run();

private:
    // private members
    sf::RenderWindow *m_window;
    sf::Texture m_fightTexture;
    sf::Text m_p1Name, m_p2Name;
    sf::Cursor m_cursor;
    sf::Cursor m_originalCursor;
    // Board
    Board m_board;
    GameBar m_gameBar;
    // Players
    std::unique_ptr<PlayerState> m_user;
    std::unique_ptr<PlayerState> m_enemy;
    Warrior* m_currentP1 = nullptr;
    Warrior* m_currentP2 = nullptr;
    Referee m_referee;
    Warrior* userHole;
    Warrior* enemyHole;
    Warrior* userFlag;
    Warrior* ChosenWarrior;
    TimeCounting m_timeCounting;

    // booleans
    Turn_t m_turn = P1;
    const Turn_t myTurn;
    bool m_isFinishUserTurn = false;
    bool m_playHoleAnimation = false;
    bool m_winner;
    bool m_switchTurn = false;
    bool m_animatingWeapon = false;
    bool m_meAttacked = false;
    bool m_collision = false;
    bool m_gameDone = false;

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
    void updateLastMoveAndChangeTurn(bool timesUp = false);
    void updateTieCase(std::string msg);
    void handleTie();
    void animateWeapons();
    void animateHole();
    void enemyTurn();

    bool isMyTurn() const{
        return m_turn == myTurn;
    }
};


