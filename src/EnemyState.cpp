
#include "EnemyState.h"
#include "Rock.h"
EnemyState::EnemyState(const std::string& name,const std::string& id) : PlayerState(name,id) {}

void EnemyState::init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) {
    float x = matrix[0][0].getPosition().x;
    float y = matrix[0][0].getPosition().y - 30;

    int row = 0,col = 0;
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

void EnemyState::setFlagAndHole() {
    // TODO get from firebase

//    sf::RenderWindow *window = WindowManager::instance().getWindow();
//
//    while(window->isOpen()) {
//        sf::Event event;
//        while(window->waitEvent(event)) {
//            if(event.type == sf::Event::Closed) {
//                window->close();
//            }
//            if(event.type == sf::Event::MouseButtonReleased) {
//            }
//            handleHover(event.mouseMove);
//
//        }
//    }
}

void EnemyState::makeTurn() {
    // TODO play enemy
}



