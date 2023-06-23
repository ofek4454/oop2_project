#include "SFML/Graphics.hpp"
#include "ResourcesManager.h"

sf::Text& createText(const std::string& str,const int size,const sf::Vector2f &pos,const sf::Color &color = sf::Color::White){
    auto text = sf::Text();
    text.setFont(*ResourcesManager::instance().getFont());
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(pos);
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    return text;
}

sf::Sprite& createSprite(const sf::Vector2f &pos,const sf::Vector2f &scale,const sf::Texture* texture){
    auto sprite = sf::Sprite();
    sprite.setTexture(*texture);
    sprite.setPosition(pos);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    return sprite;
}

sf::CircleShape& createCircle(const int radius,const sf::Vector2f &pos,const sf::Color &color){
    auto circle = sf::CircleShape();
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setPosition(pos);
    return circle;
}