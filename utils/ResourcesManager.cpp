//
// Created by Bar Kobi on 20/05/2023.
//

#include "ResourcesManager.h"

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager resource;
    return resource;
}


ResourcesManager::ResourcesManager() {
    m_texture[Warriors].loadFromFile("warriors2.png");
    m_texture[Rps].loadFromFile("weapons.png");
    m_texture[Arrow].loadFromFile("arrow.png");
    m_background.setSize(sf::Vector2f (WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setFillColor(sf::Color(181, 221, 94));

}

sf::Texture *ResourcesManager::getWarriorTexture(Textures texture) {
    return &m_texture[texture];
}

sf::RectangleShape *ResourcesManager::getBackground() {
    return &m_background;
}
