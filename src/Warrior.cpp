#include "Warrior.h"
#include "cstdlib"

Warrior::Warrior(const sf::Vector2f &pos, const bool isMine) : m_weapon(std::make_unique<Undefined>(isMine)){
    auto texture = ResourcesManager::instance().getWarriorTexture(Warriors);
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(pos);
    m_sprite.setTextureRect(isMine ? sf::IntRect(0, 0, 160, 252) : sf::IntRect(0, 756, 160, 252));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_sprite.setScale(0.8, 0.8);

    if (isMine) {
        m_weapon->setSpriteLoc(sf::Vector2f(m_sprite.getPosition().x - 5, m_sprite.getPosition().y + 10));
    }
}

sf::FloatRect Warrior::getGlobalBounds() const {
    return m_sprite.getGlobalBounds();
}

void Warrior::draw() {
    auto window = WindowManager::instance().getWindow();
    window->draw(m_sprite);
}
