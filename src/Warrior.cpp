#include "Warrior.h"
#include "Flag.h"
#include "Hole.h"
#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"
#include "Weapon.h"
#include "RoomState.h"

Warrior::Warrior(const std::string id,const sf::Vector2f pos, const bool isMine, Location location)
        : m_id(id), m_weapon(std::make_unique<Undefined>()), m_location(location){

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
    m_initialTexture = *m_sprite.getTexture();
    m_shadow.setColor(sf::Color(0, 0, 0, 30)); // Set shadow color and transparency
    m_shadow.setScale(0.7, 0.35);
    m_shadow.setPosition(m_sprite.getPosition().x - RECT_SIZE / 2 - 30, m_sprite.getPosition().y - RECT_SIZE / 2 + 50);
    m_shadow.setTextureRect(sf::IntRect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT));

    if (isMine){
        m_throwTexture = *ResourcesManager::instance().getTexture(ThrowPlayer);
        m_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * 0.125, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height * 0.125));
    }
    else
        m_weapon->setVisible(false);

    m_weapon->setOwner(this);
}

void Warrior::draw() {
    auto window = WindowManager::instance().getWindow();
    if (m_needToBeDraw) {
        window->draw(m_shadow);
        window->draw(m_sprite);
        if(m_weapon->isVisible()){
            m_weapon->draw();
        }
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

void Warrior::setMovingIntRect(int counter,bool isEnemy) {
    if (isEnemy) {
        m_sprite.setTextureRect(sf::IntRect(MOVING_ANIMATION_ARR[counter], IMAGE_HEIGHT * 3, IMAGE_WIDTH, IMAGE_HEIGHT));
    }else{
        m_sprite.setTextureRect(sf::IntRect(MOVING_ANIMATION_ARR[counter], 0, IMAGE_WIDTH, IMAGE_HEIGHT));
    }
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
    m_weapon->setSpriteLoc(sf::Vector2f (m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * 0.125, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height * 0.125));
}

void Warrior::setTextureFlag(bool isHighlighted) {
    if (!m_canMove) return;
    if (isHighlighted) {
        m_sprite.setTextureRect(sf::IntRect(0, IMAGE_HEIGHT * 4, IMAGE_WIDTH, IMAGE_HEIGHT));
        m_weapon.get()->setSpriteLoc(sf::Vector2f(-100, -100));
    } else {
        m_sprite.setTextureRect(m_initialIntRect);
        m_weapon.get()->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * 0.125, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height * 0.125));
    }

}

void Warrior::setTextureHole(bool isHighlighted) {
    static sf::Texture m_hole = *ResourcesManager::instance().getTexture(Trap);
    if (!m_canMove) return;
    if (isHighlighted) {
        m_sprite.setTexture(m_hole);
        m_weapon.get()->setSpriteLoc(sf::Vector2f(-100, -100));
    } else {
        m_sprite.setTexture(m_initialTexture);
        m_sprite.setTextureRect(m_initialIntRect);
        m_weapon.get()->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * 0.125, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height * 0.15));
    }
}

bool Warrior::setAsFlag() {
    if (!m_canMove) return false;
    std::unique_ptr<Weapon> flag = std::make_unique<Flag>();
    m_weapon = std::move(flag);
    if(m_isMine){
        m_sprite.setTextureRect(sf::IntRect(0, IMAGE_HEIGHT * 4, IMAGE_WIDTH, IMAGE_HEIGHT));
        m_initialIntRect = m_sprite.getTextureRect();
    }
    m_canMove = false;
    return true;
}

bool Warrior::setAsHole() {
    static sf::Texture m_hole = *ResourcesManager::instance().getTexture(Trap);
    if (!m_canMove) return false;
    std::unique_ptr<Weapon> hole = std::make_unique<Hole>();
    m_weapon = std::move(hole);
    if(m_isMine){
        m_sprite.setTexture(m_hole);
        m_sprite.setTextureRect(sf::IntRect(0,0,IMAGE_WIDTH, IMAGE_HEIGHT));
    }
    m_canMove = false;
    return true;
}

void Warrior::setWeapon(Weapons_t weapon,bool visible) {

    std::unique_ptr<Weapon> new_weapon;
    switch (weapon) {
        case Rock_t: {
            new_weapon = std::make_unique<Rock>(visible);
            break;
        }
        case Paper_t: {
            new_weapon = std::make_unique<Paper>(visible);
            break;
        }
        case Scissors_t: {
            new_weapon = std::make_unique<Scissors>(visible);
            break;
        }
        case Undefined_t: {
            new_weapon = std::make_unique<Undefined>();
            break;
        }
        default:
            break;
    }
    new_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * 0.125, m_sprite.getPosition().y - m_sprite.getGlobalBounds().height * 0.15));
    new_weapon->setOwner(this);
    m_weapon = std::move(new_weapon);
}

void Warrior::lose() {
    m_needToDelete = true;
}

bool Warrior::setHoleIntRect() {
    static int rect = 0;
    static bool set = false;
    rect += IMAGE_WIDTH;
    if(!m_isMine && !set){
        static sf::Texture m_hole = *ResourcesManager::instance().getTexture(Trap);
        set = true;
        m_sprite.setTexture(m_hole);
        m_sprite.setTextureRect(sf::IntRect(0,0,IMAGE_WIDTH, IMAGE_HEIGHT));
    }
    m_sprite.setTextureRect(sf::IntRect(rect,0,IMAGE_WIDTH,IMAGE_HEIGHT));
    if(rect == IMAGE_WIDTH * 3){
        if(m_isMine)
            m_sprite.setTextureRect(sf::IntRect(0,0,IMAGE_WIDTH,IMAGE_HEIGHT));
        else{
            auto texture = ResourcesManager::instance().getTexture(Warriors);
            m_sprite.setTexture(*texture);
            m_sprite.setTextureRect(sf::IntRect(0, IMAGE_HEIGHT * 3, IMAGE_WIDTH,
                        IMAGE_HEIGHT));
            set = false;
        }
        rect = 0;
        return true;
    }
    return false;
}

void Warrior::setTexture(bool reset) {
    if (reset) {
        m_sprite.setTexture(m_initialTexture);
        m_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - m_sprite.getGlobalBounds().width * 0.125,
                                            m_sprite.getPosition().y - m_sprite.getGlobalBounds().height * 0.125));
        return;
    } else {
        m_sprite.setTexture(m_throwTexture);
        m_sprite.setTextureRect(sf::IntRect(2,0,IMAGE_WIDTH,IMAGE_HEIGHT));
        m_sprite.setScale(RECT_SIZE / IMAGE_WIDTH, RECT_SIZE / IMAGE_WIDTH);
    }
}