//
// Created by Bar Kobi on 20/05/2023.
//

#include "ResourcesManager.h"

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager resource;
    return resource;
}


ResourcesManager::ResourcesManager() {
    m_backgroundMusic.openFromFile("BackGroundMusic.wav");
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
    m_texture[RefereeTexture].loadFromFile("indicator.png");
    m_texture[RefereeTexture].setSmooth(true);
    m_texture[Background].loadFromFile("background.png");
    m_texture[ExitButton].loadFromFile("exit.png");
    m_texture[RoomButton].loadFromFile("button.png");
    m_texture[Trap].loadFromFile("Hole.png");
    m_texture[Trap].setSmooth(true);
    m_texture[ShuffleButton].loadFromFile("shuffleButton.png");
    m_texture[ScissorsFlip].loadFromFile("ScissorsFlipping.png");
    m_texture[PaperFlip].loadFromFile("PaperFlipping.png");
    m_texture[RockFlip].loadFromFile("RockFlipping.png");
    m_texture[ThrowPlayer].loadFromFile("throwAnimationPlayer.png");
    m_texture[RefereeDeclareWinning].loadFromFile("end.png");
    m_texture[WinningJump].loadFromFile("winner.png");





    m_background.setSize(sf::Vector2f (WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setFillColor(GREEN_COLOR);
    m_font.loadFromFile("AlfaSlabOne-Regular.ttf");

    for (int i = 0; i < NUMBER_OF_SOUNDS - 1; i++) {
        m_sounds_buffs[i].loadFromFile(m_sound_file_names[i]);
        m_sounds[i].setBuffer(m_sounds_buffs[i]);
    }
    for(int i = 0; i < 2;i++){
        m_soundButton[i].loadFromFile(m_soundstring[i]);
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
    if(!SettingsManager::instance().getFXSwitch())
        return;
    m_sounds[index].setBuffer(m_sounds_buffs[index]);
    m_sounds[index].setLoop(false);
    m_sounds[index].setVolume(SettingsManager::instance().getVolume());
    m_sounds[index].play();
}

void ResourcesManager::playBackgroundMusic() {
    return;
    if(!SettingsManager::instance().getMusicSwitch())
        return;

    m_backgroundMusic.setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.play();
}


void ResourcesManager::updateSounds() {
    if(!SettingsManager::instance().getMusicSwitch()){
        m_backgroundMusic.stop();
        return;
    }

    if(m_backgroundMusic.getStatus() != sf::Music::Status::Playing)
        m_backgroundMusic.play();

    m_backgroundMusic.setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic.setLoop(true);

}

sf::Texture *ResourcesManager::getSoundButton(const int loc) {
    return &m_soundButton[loc];
}

void ResourcesManager::pauseBackgroundMusic() {
    m_backgroundMusic.pause();
}

/**
 * is the background music currently playing.
 */
bool ResourcesManager::isBGMusicPlaying() {
    return m_backgroundMusic.getStatus() == sf::Music::Playing;
}
