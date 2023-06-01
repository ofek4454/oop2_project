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
    PlayerModel p;
    sf::Text m_text;
    sf::RectangleShape m_background;
    sf::RenderWindow &m_window;
    std::unordered_map<std::string,std::string> availableRooms;
    std::vector<sf::RectangleShape> m_buttons;
    std::vector<sf::Text> m_texts;

    void print(int offset = 0);
    void init();
    void chooseRoom();
    void clickHandler(sf::Event::MouseButtonEvent &click,bool &exit);

};
