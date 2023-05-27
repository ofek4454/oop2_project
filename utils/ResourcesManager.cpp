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
    m_texture[PaperPaper].loadFromFile("tieP.png");
    m_texture[RockRock].loadFromFile("tieR.png");
    m_texture[ScissorsScissors].loadFromFile("tieS.png");
    m_texture[BluePR].loadFromFile("bluePR.png");
    m_texture[BlueRS].loadFromFile("blueRS.png");
    m_texture[BlueSP].loadFromFile("blueSP.png");
    m_texture[RedPR].loadFromFile("redPR.png");
    m_texture[RedRS].loadFromFile("redRS.png");
    m_texture[RedSP].loadFromFile("redSP.png");
    m_texture[Background].loadFromFile("background.png");

    m_background.setSize(sf::Vector2f (WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setFillColor(sf::Color(181, 221, 94));
    m_font.loadFromFile("AlfaSlabOne-Regular.ttf");

}

sf::Texture *ResourcesManager::getTexture(Textures_t texture) {
    return &m_texture[texture];
}

sf::RectangleShape *ResourcesManager::getBackground() {
    return &m_background;
}

sf::Font *ResourcesManager::getFont() {
    return &m_font;
}
