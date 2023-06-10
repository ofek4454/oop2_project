#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "PlayerModel.h"
#include "ResourcesManager.h"
#include "WindowManager.h"

class AfterGameScreen {
public:
    AfterGameScreen(bool isMeWon, PlayerModel userModel,PlayerModel enemyModel,Turn_t myTurn);

private:
    void playLosingAnimation();
    void print();
    void handleHover(sf::Event::MouseMoveEvent &event);
    void handleClick(sf::Event::MouseButtonEvent &event);
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
    PlayerModel m_userModel;
    PlayerModel m_enemyModel;
    sf::Text m_rematchText;
    sf::IntRect m_jumpingRect;
    sf::IntRect m_refRect;
    Turn_t m_myServerTurn;

};
