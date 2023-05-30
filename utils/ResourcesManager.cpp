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
    m_texture[Warriors].setSmooth(true);
    m_texture[Rps].loadFromFile("weapons.png");
    m_texture[Rps].setSmooth(true);
    m_texture[Arrow].loadFromFile("arrow.png");
    m_texture[PaperPaper].loadFromFile("tieP.png");
    m_texture[PaperPaper].setSmooth(true);
    m_texture[RockRock].loadFromFile("tieR.png");
    m_texture[RockRock].setSmooth(true);
    m_texture[ScissorsScissors].loadFromFile("tieS.png");
    m_texture[ScissorsScissors].setSmooth(true);
    m_texture[BluePR].loadFromFile("bluePR.png");
    m_texture[BluePR].setSmooth(true);
    m_texture[BlueRS].loadFromFile("blueRS.png");
    m_texture[BlueRS].setSmooth(true);
    m_texture[BlueSP].loadFromFile("blueSP.png");
    m_texture[BlueSP].setSmooth(true);
    m_texture[RedPR].loadFromFile("redPR.png");
    m_texture[RedPR].setSmooth(true);
    m_texture[RedRS].loadFromFile("redRS.png");
    m_texture[RedRS].setSmooth(true);
    m_texture[RedSP].loadFromFile("redSP.png");
    m_texture[RedSP].setSmooth(true);
    m_texture[Referee].loadFromFile("indicator.png");
    m_texture[Referee].setSmooth(true);
    m_texture[Background].loadFromFile("background.png");

    m_background.setSize(sf::Vector2f (WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setFillColor(GREEN_COLOR);
    m_font.loadFromFile("AlfaSlabOne-Regular.ttf");

    for (int i = 0; i < NUMBER_OF_SOUNDS; i++) {
        m_sounds_buffs[i].loadFromFile(m_sound_file_names[i]);
        m_sounds[i].setBuffer(m_sounds_buffs[i]);
    }

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

void ResourcesManager::playSound(const int index) {
    if(index == NUMBER_OF_SOUNDS - 1){
        return;
    }
    m_sounds[index].setBuffer(m_sounds_buffs[index]);
    m_sounds[index].setLoop(false);
    m_sounds[index].setVolume(100);
    m_sounds[index].play();
}