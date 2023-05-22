#include "Warrior.h"
#include "cstdlib"

Warrior::Warrior(const sf::Vector2f pos, const bool isMine,Location location) : m_weapon(std::make_unique<Undefined>(isMine)),
                                                                                 m_location(location){
    auto texture = ResourcesManager::instance().getWarriorTexture(Warriors);
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(sf::Vector2f(pos.x,pos.y + 30));
    m_sprite.setTextureRect(isMine ? sf::IntRect(0, 100, 160, 140) : sf::IntRect(0, 856, 160, 140));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_sprite.setScale(0.8,0.8);

    if (isMine) {
        m_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 5, m_sprite.getPosition().y - 20));
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
    if(isHighlighted){
        m_sprite.setScale(0.9,0.9);
    }
    else{
        m_sprite.setScale(0.8, 0.8);
    }
}
