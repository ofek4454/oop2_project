#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "PlayerModel.h"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "EventLoop.h"
#include "RoomState.h"
#include "TextClass.h"

class AfterGameScreen {
public:
    AfterGameScreen(bool isMeWon, PlayerModel userModel,PlayerModel enemyModel,Turn_t myTurn);

private:
    void playLosingAnimation();
    void print();
    void handleHover(sf::Event::MouseMoveEvent &event);
    void handleClick(sf::Event::MouseButtonEvent &event,bool &exit);
    void changeRefereeTextureRect();
    void changeJumpingTextureRect();
    sf::RenderWindow* m_window;
    sf::Text m_text;
    sf::RectangleShape m_background;
    sf::Sprite m_refereeFlag;
    sf::Sprite m_playerJump;
    sf::Cursor m_originalCursor;
    sf::Cursor m_clickable;
    bool m_isMeWinner;
    bool m_waitingForOpponent = false;
    PlayerModel m_userModel;
    PlayerModel m_enemyModel;
    sf::Text m_rematchText;
    sf::Text m_yesNoTexts[2];
    sf::IntRect m_jumpingRect;
    sf::IntRect m_refRect;
    Turn_t m_myServerTurn;

    void checkOpponentsResponse(bool &exit);
};
