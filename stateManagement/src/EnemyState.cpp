
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
        std::string warriorId = m_playerSymbol == "2" ? std::to_string(row) + std::to_string(col)
                                                      : std::to_string(ROWS -1 - row) + std::to_string(BOARD_SIZE-1-col);
        m_warriors[warriorId] = std::make_unique<Warrior>(warriorId, sf::Vector2f(x, y), false, Location(row, col));
        x += RECT_SIZE;
        if (i == BOARD_SIZE - 1) {
            y += RECT_SIZE;
            x = BOARD_TOP_LEFT.left + RECT_SIZE / 2;
        }
    }
}


void EnemyState::doTurn(sf::Event::MouseButtonEvent *click,sf::Event::KeyEvent *key,Location indicator) {
    std::string last_move = RoomState::instance().getRoom().getLastMove();
    if (last_move.empty()) {
        return;
    }
    m_isAnimating = true;
    std::stringstream ss(last_move);

    ss >> m_selectedWarriorId;
    auto location = extractLocation(ss.str());

    auto warrior = getWarrior();
    if (warrior == NULL) return;

    if (warrior->getLocation().row + 1 == location.row)
        m_direction = Down;
    else if (warrior->getLocation().row - 1 == location.row)
        m_direction = Up;
    else if (warrior->getLocation().col - 1 == location.col)
        m_direction = Left;
    else if (warrior->getLocation().col + 1 == location.col)
        m_direction = Right;
    else {
        m_direction = Non_Direction;
    }

    m_emoji = RoomState::instance().getLastEmoji();

    if (last_move[last_move.size() - 1] != warrior->getSymbol()[0]) {

        switch (last_move[last_move.size() - 1]) {
            case 'R':
                warrior->setWeapon(Rock_t, false);
                break;
            case 'S':
                warrior->setWeapon(Scissors_t, false);
                break;
            case 'P':
                warrior->setWeapon(Paper_t, false);
                break;
            case 'U': // NOT HAPPEN
                warrior->setWeapon(Undefined_t);
                break;
        }
    }
}

bool EnemyState::move() {
    static int imageCounter = 0;
    static float shadowOffsetX = -1;
    static int shadowOffsetY = 4;
    auto warrior = getWarrior();
    if (warrior == NULL) {
        m_isAnimating = false;
        return true;
    }
    if (m_direction == Up)
        warrior->setSpriteLocation(sf::Vector2f(0, -m_pixelOffset), sf::Vector2f(shadowOffsetX, shadowOffsetY));
    else if (m_direction == Down)
        warrior->setSpriteLocation(sf::Vector2f(0, m_pixelOffset),
                                          sf::Vector2f(sf::Vector2f(shadowOffsetX * 0.5, -shadowOffsetY * 0.8)));
    else if (m_direction == Left)
        warrior->setSpriteLocation(sf::Vector2f(-m_pixelOffset, 0),
                                          sf::Vector2f(sf::Vector2f(-shadowOffsetX, 0)));
    else if (m_direction == Right)
        warrior->setSpriteLocation(sf::Vector2f(m_pixelOffset, 0), sf::Vector2f(sf::Vector2f(shadowOffsetX, 0)));
    else {
        m_isAnimating = false;
        warrior->setLocation(m_direction);
        return true;
    }

    warrior->setMovingIntRect(imageCounter, true);
    imageCounter++;
    if (imageCounter == IMAGE_COUNT) {
        shadowOffsetX = -1;
        shadowOffsetY = 4;
        imageCounter = 0;
        warrior->setLocation(m_direction);
        m_isAnimating = false;
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

Location EnemyState::extractLocation(const std::string &str) {
    Location loc;
    if(m_playerSymbol == "1")
        loc = Location(ROWS-1-std::atoi(&str[3]), BOARD_SIZE-1-std::atoi(&str[5]));
    else
        loc = Location(std::atoi(&str[3]), std::atoi(&str[5]));
    return loc;
}