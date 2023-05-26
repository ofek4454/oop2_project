#pragma once

#include "SFML/Graphics.hpp"
#include "Consts.h"

class ResourcesManager {
public:
    static ResourcesManager &instance();

    sf::Texture *getTexture(Textures_t);
    sf::RectangleShape *getBackground();
    sf::Font *getFont();
private:
    ResourcesManager();
    sf::Texture m_texture[NUM_OF_TEXTURES];
    sf::RectangleShape m_background;
    sf::Font m_font;
};
