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

enum Cursor_t{
    OriginalCursor,
    ClickCursor,
    TrashCursor,
};
class Controller {
public:
    // C-Tor
    Controller(PlayerModel p1, PlayerModel p2, bool isMeP1) ;
    // D-Tor
    ~Controller();
    // function
    void run();

private:
    // private members
    sf::RenderWindow *m_window;
    sf::Texture m_fightTexture;
    sf::Text m_p1Name, m_p2Name;
    sf::Text m_backButton;
    sf::Text m_LoadingText;
    sf::Sprite m_chatBubble;
    sf::Sprite m_emojis[6];
    sf::Sprite m_chatIcon;
    sf::Sprite m_enemyEmoji;
    sf::Sprite m_lastFrameWar;
    sf::Texture m_tempBackgroundTexture;
    sf::Sprite m_tempBackground;
    sf::Sprite m_pickedEmojiSprite;
    sf::Cursor m_cursor;
    sf::Cursor m_deleteCursor;
    sf::Cursor m_originalCursor;
    sf::CircleShape m_circleIndicator;
    // Board
    Board m_board;
    GameBar m_gameBar;
    // Players
    std::unique_ptr<UserState> m_user;
    std::unique_ptr<EnemyState> m_enemy;
    Warrior* m_currentP1 = nullptr;
    Warrior* m_currentP2 = nullptr;
    Referee m_referee;
    Warrior* userHole;
    Warrior* enemyHole;
    Warrior* userFlag;
    Warrior* ChosenWarrior = NULL;
    TimeCounting m_timeCounting;

    // booleans
    Turn_t m_turn = P1;
    const Turn_t myTurn;
    bool m_switchPlayerByKey = false; // false = mouse true = keyboard
    Location m_indicator;
    bool m_isFinishUserTurn = false;
    bool m_playHoleAnimation = false;
    bool m_winner;
    bool m_switchTurn = false;
    bool m_animatingWeapon = false;
    bool m_meAttacked = false;
    bool m_collision = false;
    bool m_gameDone = false;
    bool m_distruct = false;
    bool m_isChatPressed = false;
    bool m_attackingUndefined = false;
    Emojis m_emojiPicked = NonEmoji_t;
    Cursor_t m_currentCursor = OriginalCursor;

    // private functions:
    void LoadingGame();
    void handleKeyboard(sf::Event::KeyEvent &type);
    void incPlayer();
    void initGame();
    void print(bool printLoad = false,bool fight = false);
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
    void enemyTurn(bool &exit);
    void setSpritesAndTxts();
    void handleClick(sf::Event::MouseButtonEvent &click);
    bool isMyTurn() const{
        return m_turn == myTurn;
    }
    sf::Clock m_chatClock;
};


