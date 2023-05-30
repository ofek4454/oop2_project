
#include "EnemyState.h"
#include "Rock.h"
EnemyState::EnemyState(PlayerModel &player) : PlayerState(player) {}

void EnemyState::init() {
    float x = BOARD_TOP_LEFT.left + RECT_SIZE/2;
    float y = BOARD_TOP_LEFT.top - 30 + (RECT_SIZE/2 * 9);

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
            x = BOARD_TOP_LEFT.left + RECT_SIZE/2;
        }
    }
}


void EnemyState::doTurn(sf::Event::MouseButtonEvent *click) {
    sf::sleep(sf::seconds(0.5));
    m_isAnimating = true;
}




