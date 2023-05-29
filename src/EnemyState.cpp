
#include "EnemyState.h"
#include "Rock.h"
EnemyState::EnemyState(const std::string& name,const std::string& id) : PlayerState(name,id) {}

void EnemyState::init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) {
    float x = matrix[0][0].getPosition().x;
    float y = matrix[4][0].getPosition().y - 30;

    int row = 4,col = 0;
    for(int i = 0; i < BOARD_SIZE*2; i++,col++) {
        if(i == BOARD_SIZE){
            row++;
            col = 0;
        }
        m_warriors.push_back(std::make_unique<Warrior>(sf::Vector2f(x, y),false, Location(row,col)));
        x+=RECT_SIZE;
        if(i== BOARD_SIZE - 1) {
            y += RECT_SIZE;
            x = matrix[0][0].getPosition().x;
        }
    }

}


bool EnemyState::doTurn(sf::Event::MouseButtonEvent *click) {
    return true;
}




