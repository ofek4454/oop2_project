#pragma once
#include "EventLoop.h"
#include "sstream"
#include "Consts.h"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "TimeCounting.h"

/**
 * Game bar class responsible for showing and updating stats ahout the game
 */
class GameBar{
public:
    // C-Tor
    GameBar();
    // Functions
    void updateGameBar(int userWarriors, int enemyWarriors);
    void drawStats();
    void resetClock(bool myTurn);
    void setClock(int time);
private:
    // members
    sf::RenderWindow *m_window;
    sf::Clock m_gameTimer;
    TimeCounting m_timer;
    sf::Text m_statsText[2];
    sf::Sprite m_sprites[2];
};
