#pragma once

#include "SFML/Graphics.hpp"
#include "PlayerModel.h"
#include "RoomState.h"
#include "UserService.h"
#include "EnemyState.h"
#include "UserState.h"
#include "Controller.h"
#include "unordered_map"

class AvailableRooms{
public:
    AvailableRooms(PlayerModel player);

private:
    sf::Clock animationClock;
    int m_rect = 0;
    bool m_animation = false;
    PlayerModel p;
    PlayerModel enemy;
    sf::Text m_text;
    sf::Text m_loadingText;
    sf::RectangleShape m_background;
    sf::RenderWindow &m_window;
    std::unordered_map<std::string,std::string> availableRooms;
    std::vector<sf::RectangleShape> m_buttons;
    std::vector<sf::Text> m_texts;
    sf::Cursor m_originalCursor;
    sf::Cursor m_clickable;
    int m_offset = 0;
    sf::Sprite m_scrollSprite;
    sf::Vector2f m_originalScale;

    void print(int offset = 0);
    void animation();
    void init();
    void chooseRoom();
    void clickHandler(sf::Event::MouseButtonEvent &click, bool &exit);
    void hoverHandler(sf::Event::MouseMoveEvent &move);
};