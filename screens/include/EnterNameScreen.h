#pragma once

#include "string"
#include "SFML/Graphics.hpp"
#include "ResourcesManager.h"
#include "WindowManager.h"
#include "UserService.h"
#include "RoomState.h"
#include "Controller.h"
#include "WaitingRoom.h"
#include "TextClass.h"
#include "SoundFlip.h"

enum Mode_t{
    Create,
    Join,
};

class EnterNameScreen{
public:
    EnterNameScreen(Mode_t mode);

private:
    Mode_t m_mode;
    std::string m_name;
    sf::RectangleShape m_background;
    sf::Text m_title;
    sf::Text m_nameText;
    sf::Text m_quitText;
    sf::Sprite m_timeMenu;
    sf::Text m_Navigation[2];
    std::shared_ptr<sf::RenderWindow> m_window;
    float m_rect[3] = {238, 510, 780};
    int indicator = 0;
    int gameTime = 30;
    void init();
    void handleEvents();
    void print();
    void setIndicatorTextAndTime();
    void clickHandler(auto click);
};