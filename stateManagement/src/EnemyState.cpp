
#include "EnemyState.h"
#include "Rock.h"
#include "RoomState.h"
#include "sstream"

EnemyState::EnemyState(PlayerModel &player) : PlayerState(player) {}

void EnemyState::init() {
    float x = BOARD_TOP_LEFT.left + RECT_SIZE/2;
    float y = BOARD_TOP_LEFT.top - 30 + RECT_SIZE/2;

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
            x = BOARD_TOP_LEFT.left + RECT_SIZE/2;
        }
    }
}


void EnemyState::doTurn(sf::Event::MouseButtonEvent *click) {
    m_isAnimating = true;
    std::string last_move = RoomState::instance().getLastMove();
    auto locations = extractNumbers(last_move);
    m_selectedPlayerLocation = Location(locations[0], locations[1]);
    m_newLocation = Location(locations[2],locations[3]);
    if(m_selectedPlayerLocation.row + 1 == m_newLocation.row){
        m_direction = Down;
    }
}

bool EnemyState::move() {
    static int imageCounter = 0;
    static float shadowOffsetX = -1;
    static int shadowOffsetY = 4;
    auto warrior = getWarrior(m_selectedPlayerLocation);
    if(warrior == NULL)
        return false;
    if (m_direction == Down){
        std::cout << "moving down";
        warrior->get()->setSpriteLocation(sf::Vector2f(0, m_pixelOffset),sf::Vector2f(sf::Vector2f(shadowOffsetX * 0.5, -shadowOffsetY * 0.8)));
    }

    warrior->get()->setIntRect(imageCounter,true);
    imageCounter++;
    if(imageCounter == IMAGE_COUNT){
        shadowOffsetX = -1;
        shadowOffsetY = 4;
        imageCounter = 0;
        warrior->get()->setLocation(m_direction);
        return true;
    }
    if(imageCounter == 3){
        ResourcesManager::instance().playSound(redJump);
    }
    if(imageCounter == 12){
        shadowOffsetX = 3.7;
        shadowOffsetY = -12;
    }
    return false;

}




std::vector<int> EnemyState::extractNumbers(const std::string& str) {
    std::vector<int> numbers;
    for(int i = 0;i < str.size();i++){
        char c = str[i];
        if(isdigit(c)){
            numbers.push_back(std::atoi(&c));
        }
    }
    return numbers;
}