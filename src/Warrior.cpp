#include "Warrior.h"
#include "cstdlib"

Warrior::Warrior(const sf::Vector2f pos, const bool isMine, Location location) : m_weapon(
        std::make_unique<Undefined>(isMine)),
                                                                                 m_location(location) {
    auto texture = ResourcesManager::instance().getWarriorTexture(Warriors);
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    m_sprite.setTextureRect(isMine ? sf::IntRect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT) : sf::IntRect(0, IMAGE_HEIGHT * 3, IMAGE_WIDTH, IMAGE_HEIGHT));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_sprite.setScale(0.8, 0.8);

    if (isMine) {
        m_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 5, m_sprite.getPosition().y ));
    }
}

sf::FloatRect Warrior::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

void Warrior::draw() {
    auto window = WindowManager::instance().getWindow();
    window->draw(m_sprite);
}

void Warrior::setSpriteLocation(const sf::Vector2f &offset) {
    m_sprite.move(offset);
    m_weapon->moveWeapon(offset);
}

void Warrior::setHighlighted(bool isHighlighted) {
    if (isHighlighted) {
        m_sprite.setScale(0.9, 0.9);
    } else {
        m_sprite.setScale(0.8, 0.8);
    }
}

void Warrior::setIntRect(int counter) {
    int arr[6] = {0, IMAGE_WIDTH, IMAGE_WIDTH * 2, IMAGE_WIDTH * 2, IMAGE_WIDTH,0};
    m_sprite.setTextureRect(sf::IntRect(arr[counter], 0, IMAGE_WIDTH, IMAGE_HEIGHT));
}



void Warrior::setLocation(Direction direction) {
    switch (direction) {
        case Direction::Up:
            m_location = Location(m_location.row - 1, m_location.col);
            break;
        case Direction::Down:
            m_location = Location(m_location.row + 1, m_location.col);
            break;
        case Direction::Left:
            m_location = Location(m_location.row, m_location.col - 1);
            break;
        case Direction::Right:
            m_location = Location(m_location.row, m_location.col + 1);
            break;
        case Direction::Non_Direction:
            break;
    }
}
