#include "Warrior.h"
#include "Flag.h"
#include "Hole.h"
#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"
#include "Weapon.h"

Warrior::Warrior(const sf::Vector2f pos, const bool isMine, Location location)
        : m_weapon(std::make_unique<Undefined>(isMine)), m_location(location), m_isMine(isMine) {

    auto texture = ResourcesManager::instance().getTexture(Warriors);
    m_sprite.setTexture(*texture);
    m_shadow.setTexture(*texture);
    m_sprite.setPosition(sf::Vector2f(pos.x, pos.y));
    m_sprite.setTextureRect(
            isMine ? sf::IntRect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT) : sf::IntRect(0, IMAGE_HEIGHT * 3, IMAGE_WIDTH,
                                                                                IMAGE_HEIGHT));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    //TODO set relative size
    m_sprite.setScale(RECT_SIZE / IMAGE_WIDTH, RECT_SIZE / IMAGE_WIDTH);
    m_initialIntRect = m_sprite.getTextureRect();
    m_shadow.setColor(sf::Color(0, 0, 0, 30)); // Set shadow color and transparency
    m_shadow.setScale(0.7, 0.35);
    m_shadow.setPosition(m_sprite.getPosition().x - RECT_SIZE / 2 - 30, m_sprite.getPosition().y - RECT_SIZE / 2 + 50);
    m_shadow.setTextureRect(sf::IntRect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT));

    if (isMine)
        m_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 10, m_sprite.getPosition().y));
    else
        m_weapon->setSpriteLoc(sf::Vector2f(-1000, -1000));

    m_weapon->setOwner(this);
}

void Warrior::draw() {
    auto window = WindowManager::instance().getWindow();
    if (m_needToBeDraw) {
        window->draw(m_shadow);
        window->draw(m_sprite);
        m_weapon->draw();
    }
}

void Warrior::setSpriteLocation(const sf::Vector2f &offset, const sf::Vector2f &shadowoffset) {
    m_sprite.move(offset);
    m_shadow.move(shadowoffset);
    m_weapon->moveWeapon(offset);
}

void Warrior::setHighlighted(bool isHighlighted) {
    if (isHighlighted) {
        m_sprite.setScale(0.75, 0.75);
    } else {
        m_sprite.setScale(RECT_SIZE / IMAGE_WIDTH, RECT_SIZE / IMAGE_WIDTH);
    }
}

void Warrior::setIntRect(int counter) {
    m_sprite.setTextureRect(sf::IntRect(MOVING_ANIMATION_ARR[counter], 0, IMAGE_WIDTH, IMAGE_HEIGHT));
}


void Warrior::setLocation(Direction_t direction) {
    switch (direction) {
        case Direction_t::Up:
            m_location = Location(m_location.row - 1, m_location.col);
            break;
        case Direction_t::Down:
            m_location = Location(m_location.row + 1, m_location.col);
            break;
        case Direction_t::Left:
            m_location = Location(m_location.row, m_location.col - 1);
            break;
        case Direction_t::Right:
            m_location = Location(m_location.row, m_location.col + 1);
            break;
        case Direction_t::Non_Direction:
            break;
    }
    m_shadow.setPosition(m_sprite.getPosition().x - RECT_SIZE / 2 - 30, m_sprite.getPosition().y - RECT_SIZE / 2 + 50);
}

void Warrior::setTextureFlag(bool isHighlighted) {
    if (!m_canMove) return;
    if (isHighlighted) {
        m_sprite.setTextureRect(sf::IntRect(0, IMAGE_HEIGHT * 4, IMAGE_WIDTH, IMAGE_HEIGHT));
        m_weapon.get()->setSpriteLoc(sf::Vector2f(-100, -100));
    } else {
        m_sprite.setTextureRect(m_initialIntRect);
        m_weapon.get()->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 10, m_sprite.getPosition().y));
    }

}

void Warrior::setTextureHole(bool isHighlighted) {
    if (!m_canMove) return;
    if (isHighlighted) {
        m_sprite.setTextureRect(sf::IntRect(IMAGE_WIDTH * 2, IMAGE_HEIGHT * 4, IMAGE_WIDTH, IMAGE_HEIGHT));
        m_weapon.get()->setSpriteLoc(sf::Vector2f(-100, -100));
    } else {
        m_sprite.setTextureRect(m_initialIntRect);
        m_weapon.get()->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 10, m_sprite.getPosition().y));
    }
}

bool Warrior::setAsFlag() {
    if (!m_canMove) return false;
    std::unique_ptr<Weapon> flag = std::make_unique<Flag>();
    m_weapon = std::move(flag);
    m_sprite.setTextureRect(sf::IntRect(0, IMAGE_HEIGHT * 4, IMAGE_WIDTH, IMAGE_HEIGHT));
    m_initialIntRect = m_sprite.getTextureRect();
    m_canMove = false;
    return true;
}

bool Warrior::setAsHole() {
    if (!m_canMove) return false;
    std::unique_ptr<Weapon> hole = std::make_unique<Hole>();
    m_weapon = std::move(hole);
    m_sprite.setTextureRect(sf::IntRect(IMAGE_WIDTH * 2, IMAGE_HEIGHT * 4, IMAGE_WIDTH, IMAGE_HEIGHT));
    m_initialIntRect = m_sprite.getTextureRect();
    m_canMove = false;
    return true;
}

void Warrior::setWeapon(Weapons_t weapon) {
    std::unique_ptr<Weapon> new_weapon;

    switch (weapon) {
        case Rock_t: {
            new_weapon = std::make_unique<Rock>();
            break;
        }
        case Paper_t: {
            new_weapon = std::make_unique<Paper>();
            break;
        }
        case Scissors_t: {
            new_weapon = std::make_unique<Scissors>();
            break;
        }
        case Undefined_t:
            new_weapon = std::make_unique<Undefined>(m_isMine);

        default:
            break;
    }
    new_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 5, m_sprite.getPosition().y + 10));
    new_weapon->setOwner(this);
    m_weapon = std::move(new_weapon);
}

void Warrior::lose() {
    m_needToDelete = true;
}
