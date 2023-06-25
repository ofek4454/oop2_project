#pragma once
#include "SFML/Graphics.hpp"
#include "string"
#include "ResourcesManager.h"

class TextClass {
public:
    TextClass(const std::string& str, float size,const sf::Vector2f &pos,const sf::Color &color = sf::Color::White);
    sf::Text getText() const {return m_text;}
private:
    sf::Text m_text;
};

