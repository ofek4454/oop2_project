
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
                                                      : std::to_string(BOARD_SIZE -1 - row) + std::to_string(BOARD_SIZE-1-col);
        m_warriors[warriorId] = std::make_unique<Warrior>(warriorId, sf::Vector2f(x, y), false, Location(row, col));
        x += RECT_SIZE;
        if (i == BOARD_SIZE - 1) {
            y += RECT_SIZE;
            x = BOARD_TOP_LEFT.left + RECT_SIZE / 2;
        }
    }
}


void EnemyState::doTurn(sf::Event::MouseButtonEvent *click) {
    std::string last_move = RoomState::instance().getRoom().getLastMove();
    if (last_move.empty()) {
        std::cout << "is empty\n";
        return;
    }
    m_isAnimating = true;
    std::cout << "is animating enemy\n";
    std::stringstream ss(last_move);

    ss >> m_selectedWarriorId;
    auto location = extractLocation(ss.str());

    auto warrior = getWarrior();
    if (warrior == NULL) {
        std::cout << "warrior not found\n" << std::endl;
        return;
    }

    if (warrior->get()->getLocation().row + 1 == location.row)
        m_direction = Down;
    else if (warrior->get()->getLocation().row - 1 == location.row)
        m_direction = Up;
    else if (warrior->get()->getLocation().col - 1 == location.col)
        m_direction = Left;
    else if (warrior->get()->getLocation().col + 1 == location.col)
        m_direction = Right;
    else {
        m_direction = Non_Direction;
    }

    if (last_move[last_move.size() - 1] != warrior->get()->getSymbol()[0]) {

        switch (last_move[last_move.size() - 1]) {
            case 'R':
                warrior->get()->setWeapon(Rock_t, false);
                break;
            case 'S':
                warrior->get()->setWeapon(Scissors_t, false);
                break;
            case 'P':
                warrior->get()->setWeapon(Paper_t, false);
                break;
            case 'U': // NOT HAPPEN
                warrior->get()->setWeapon(Undefined_t);
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
        std::cout << "null here\n";
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
        warrior->get()->setLocation(m_direction);
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
        loc = Location(BOARD_SIZE-1-std::atoi(&str[3]), BOARD_SIZE-1-std::atoi(&str[5]));
    else
        loc = Location(std::atoi(&str[3]), std::atoi(&str[5]));
    return loc;
}