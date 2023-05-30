
#include "UserState.h"
#include "Rock.h"

UserState::UserState(PlayerModel &player) : PlayerState(player) {
    for (auto &spr: m_arrows) {
        spr.setTexture(*ResourcesManager::instance().getTexture(Arrow));
        spr.setScale(RECT_SIZE / 1024, RECT_SIZE / 1024);
        spr.setColor(sf::Color::Transparent);
    }
}

void UserState::init() {
    float x = BOARD_TOP_LEFT.left + RECT_SIZE/2;
    float y = BOARD_TOP_LEFT.top + RECT_SIZE*7 - 30 + RECT_SIZE/2;

    int row = 7, col = 0;
    for (int i = 0; i < BOARD_SIZE * 2; i++, col++) {
        if (i == BOARD_SIZE) {
            row--;
            col = 0;
        }
        m_warriors.push_back(std::make_unique<Warrior>(sf::Vector2f(x, y), true, Location(row, col)));
        x += RECT_SIZE;
        if (i == BOARD_SIZE - 1) {
            y -= RECT_SIZE;
            x = BOARD_TOP_LEFT.left + RECT_SIZE/2;
        }
    }
}

void UserState::hoverFlag(const int row, const int col) {
    for (auto &warrior: m_warriors)
        warrior->setTextureFlag(warrior->getLocation() == Location(row, col));
}

void UserState::hoverHole(const int row, const int col) {
    for (auto &warrior: m_warriors)
        warrior->setTextureHole(warrior->getLocation() == Location(row, col));
}

void UserState::doTurn(sf::Event::MouseButtonEvent *click) {
    if (m_playerChose) {
        m_direction = getDirection(sf::Vector2f(click->x, click->y));
        setArrows();
        m_playerChose = false;
        if (m_direction != Non_Direction){ // finish turn
            m_isAnimating = true;
        }
    }
    if (BOARD_FRAME.contains(click->x, click->y)) { // choose warrior
        int row = (click->y - BOARD_TOP_LEFT.top) / RECT_SIZE;
        int col = (click->x - BOARD_TOP_LEFT.left) / RECT_SIZE;
        auto bool_arr = checkAvailableLocations(Location(row, col));
        if (bool_arr) {
            m_selectedPlayerLocation = Location(row, col);
            setArrows(bool_arr, m_selectedPlayerLocation, true);
            m_playerChose = true;
        }
    }
}


void UserState::setArrows(bool *directions, Location location, bool set) {
    if (!set) {
        for (auto &spr: m_arrows)
            spr.setPosition(sf::Vector2f(-1000, -1000));
        return;
    }
    if (directions[Up]) {
        m_arrows[Up].setPosition(
                sf::Vector2f(BOARD_TOP_LEFT.left + location.col * RECT_SIZE, BOARD_TOP_LEFT.top + location.row * RECT_SIZE));
        m_arrows[Up].setRotation(-90);
        m_arrows[Up].setColor(sf::Color(255, 255, 255, 70));
    }
    if (directions[Down]) {
        m_arrows[Down].setPosition(
                sf::Vector2f(BOARD_TOP_LEFT.left + ((location.col + 1) * RECT_SIZE),
                             BOARD_TOP_LEFT.top + (location.row + 1) * RECT_SIZE));
        m_arrows[Down].setRotation(90);
        m_arrows[Down].setColor(sf::Color(255, 255, 255, 70));
    }
    if (directions[Right]) {
        m_arrows[Right].setPosition(
                sf::Vector2f(sf::Vector2f(BOARD_TOP_LEFT.left + (location.col + 1) * RECT_SIZE,
                                          BOARD_TOP_LEFT.top + location.row * RECT_SIZE)));
        m_arrows[Right].setRotation(0);
        m_arrows[Right].setColor(sf::Color(255, 255, 255, 70));
    }
    if (directions[Left]) {
        m_arrows[Left].setPosition(
                sf::Vector2f(BOARD_TOP_LEFT.left + location.col * RECT_SIZE,
                             BOARD_TOP_LEFT.top + (location.row + 1) * RECT_SIZE));
        m_arrows[Left].setRotation(180);
        m_arrows[Left].setColor(sf::Color(255, 255, 255, 70));
    }
}

Direction_t UserState::getDirection(const sf::Vector2f pos) const {
    Direction_t dir = Non_Direction;
    for (int i = 0; i < m_arrows.size(); i++) {
        if (m_arrows[i].getGlobalBounds().contains(pos)) {
            dir = Direction_t(i);
        }
    }
    return dir;
}

void UserState::print() {
    auto window = WindowManager::instance().getWindow();
    for (auto &warrior: m_warriors)
        warrior->draw();

    for (auto &arrow: m_arrows) {
        window->draw(arrow);
    }
}
