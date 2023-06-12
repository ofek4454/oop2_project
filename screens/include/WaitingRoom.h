#include "SFML/Graphics.hpp"
#include "PlayerState.h"
#include "RoomState.h"
#include "UserService.h"
#include "EnemyState.h"
#include "UserState.h"
#include "Controller.h"

class WaitingRoom{
public:
    WaitingRoom(PlayerModel player);

private:
    PlayerModel p;
    sf::Text m_text;
    sf::RectangleShape m_background;
    sf::RenderWindow &m_window;

    void init();
    void waitForOpponent();
};