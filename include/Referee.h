#include "SFML/Graphics.hpp"
#include "ResourcesManager.h"
#include "WindowManager.h"

class Referee {
public:
    Referee(Turn_t turn);

    void animate(Turn_t turn);
    void print();
    void setTurn(Turn_t turn) { m_turn = turn; }
private:
    sf::Sprite m_sprite;
    float m_rect;
    sf::RenderWindow *m_window;
    Turn_t m_turn;

};
