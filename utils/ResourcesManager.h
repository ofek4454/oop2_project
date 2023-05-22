#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"

class ResourcesManager {
public:
    static ResourcesManager &instance();

    sf::Texture *getWarriorTexture(Textures);
    sf::RectangleShape *getBackground();
private:
    ResourcesManager();
    sf::Texture m_texture[NUM_OF_TEXTURES];
    sf::RectangleShape m_background;
};
