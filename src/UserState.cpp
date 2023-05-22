//
// Created by Bar Kobi on 20/05/2023.
//

#include "UserState.h"
#include "Rock.h"
UserState::UserState() : PlayerState(){}

void UserState::init(const std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> &matrix) {
    float x = matrix[BOARD_SIZE-1][0].getPosition().x;
    float y = matrix[BOARD_SIZE-1][0].getPosition().y - 30;

    for(int i = 0; i < BOARD_SIZE*2; i++) {
//        auto warrior = Warrior(sf::Vector2f(x, y),true);
        m_warriors.push_back(Warrior(sf::Vector2f(x, y),true));
        x+=matrix[0][0].getGlobalBounds().width;
        if(i== BOARD_SIZE - 1) {
            y -= matrix[0][0].getGlobalBounds().height;
            x = matrix[BOARD_SIZE-1][0].getPosition().x;
        }
    }

}

void UserState::setFlagAndHole() {
    sf::RenderWindow *window = WindowManager::instance().getWindow();

    while(window->isOpen()) {
        sf::Event event;
        while(window->waitEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window->close();
            }
            if(event.type == sf::Event::MouseButtonReleased) {
            }
            handleHover(event.mouseMove);

        }
    }
}
