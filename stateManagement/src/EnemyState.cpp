
#include "EnemyState.h"
#include "Rock.h"
#include "RoomState.h"
#include "sstream"

EnemyState::EnemyState(PlayerModel &player) : PlayerState(player) {}

void EnemyState::init() {
    float x = BOARD_TOP_LEFT.left + RECT_SIZE / 2;
    float y = BOARD_TOP_LEFT.top - 30 + RECT_SIZE / 2;

    int row = 0, col = 0;
    for (int i = 0; i < BOARD_SIZE * 2; i++, col++) {
        if (i == BOARD_SIZE) {
            row++;
            col = 0;
        }
        m_warriors.push_back(std::make_unique<Warrior>(sf::Vector2f(x, y), false, Location(row, col)));
        x += RECT_SIZE;
        if (i == BOARD_SIZE - 1) {
            y += RECT_SIZE;
            x = BOARD_TOP_LEFT.left + RECT_SIZE / 2;
        }
    }
}


void EnemyState::doTurn(sf::Event::MouseButtonEvent *click) {
    static bool enteredOnce = false;
    EventLoop::instance().addEvent(Event(NeedToResetLocation));

    if (enteredOnce) {
        enteredOnce = false;
        return;
    }
    m_isAnimating = true;


    std::string last_move = RoomState::instance().getRoom().getLastMove();
    if(last_move == "tie"){
        auto warrior = getWarrior(m_selectedPlayerLocation);
        warrior->get()->setWeapon(Undefined_t);
        EventLoop::instance().addEvent(Event(NeedToResetLocation));
        EventLoop::instance().addEvent(Event(TieEvent));
        m_direction = Non_Direction;
        return;
    }
    auto locations = extractNumbers(last_move);

    m_selectedPlayerLocation = Location(locations[0], locations[1]);
    m_newLocation = Location(locations[2], locations[3]);

    if (m_selectedPlayerLocation.row + 1 == m_newLocation.row)
        m_direction = Down;
    else if (m_selectedPlayerLocation.row - 1 == m_newLocation.row)
        m_direction = Up;
    else if (m_selectedPlayerLocation.col - 1 == m_newLocation.col)
        m_direction = Left;
    else if (m_selectedPlayerLocation.col + 1 == m_newLocation.col)
        m_direction = Right;
    else {
        m_direction = Non_Direction;
    }


    auto warrior = getWarrior(m_selectedPlayerLocation);
    if (warrior == NULL) {
        return;
    }

    if(last_move[last_move.size() - 1] != warrior->get()->getSymbol()[0]) {
        enteredOnce = true;
        switch (last_move[last_move.size() - 1]) {
            case 'R':
                warrior->get()->setWeapon(Rock_t,false);
                break;
            case 'S':
                warrior->get()->setWeapon(Scissors_t,false);
                break;
            case 'P':
                warrior->get()->setWeapon(Paper_t,false);
                break;
            case 'U':
                warrior->get()->setWeapon(Undefined_t);
                EventLoop::instance().addEvent(Event(TieEvent));
                break;
        }
    }
}

bool EnemyState::move() {
    static int imageCounter = 0;
    static float shadowOffsetX = -1;
    static int shadowOffsetY = 4;
    auto warrior = getWarrior(m_selectedPlayerLocation);
    if (warrior == NULL) {
        m_isAnimating = false;
        return true;
    }
    if (m_direction == Up)
        warrior->get()->setSpriteLocation(sf::Vector2f(0, -m_pixelOffset), sf::Vector2f(shadowOffsetX, shadowOffsetY));
    else if (m_direction == Down)
        warrior->get()->setSpriteLocation(sf::Vector2f(0, m_pixelOffset),
                                          sf::Vector2f(sf::Vector2f(shadowOffsetX * 0.5, -shadowOffsetY * 0.8)));
    else if (m_direction == Left)
        warrior->get()->setSpriteLocation(sf::Vector2f(-m_pixelOffset, 0),
                                          sf::Vector2f(sf::Vector2f(-shadowOffsetX, 0)));
    else if (m_direction == Right)
        warrior->get()->setSpriteLocation(sf::Vector2f(m_pixelOffset, 0), sf::Vector2f(sf::Vector2f(shadowOffsetX, 0)));
    else {
        m_isAnimating = false;
        return true;
    }


    warrior->get()->setMovingIntRect(imageCounter, true);
    imageCounter++;
    if (imageCounter == IMAGE_COUNT) {
        shadowOffsetX = -1;
        shadowOffsetY = 4;
        imageCounter = 0;
        warrior->get()->setLocation(m_direction);
        m_isAnimating = false;
        m_selectedPlayerLocation = m_newLocation;
        return true;
    }
    if (imageCounter == 3) {
        ResourcesManager::instance().playSound(redJump);
    }
    if (imageCounter == 12) {
        shadowOffsetX = 3.7;
        shadowOffsetY = -12;
    }
    return false;

}

std::vector<int> EnemyState::extractNumbers(const std::string &str) {
    std::vector<int> numbers;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c)) {
            if (m_playerSymbol == "1")
                numbers.push_back(BOARD_SIZE - std::atoi(&c) - 1);
            else
                numbers.push_back(std::atoi(&c));
        }
    }
    return numbers;
}