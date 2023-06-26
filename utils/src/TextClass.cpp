//
// Created by Bar Kobi on 16/06/2023.
//

#include "TextClass.h"

TextClass::TextClass(const std::string& str, float size, const sf::Vector2f &pos, const sf::Color &color) {
    m_text.setFont(*ResourcesManager::instance().getFont());
    m_text.setString(str);
    m_text.setCharacterSize(size);
    m_text.setFillColor(color);
    m_text.setPosition(pos);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_text.setOutlineThickness(1);
    m_text.setOutlineColor(sf::Color::Black);
}
