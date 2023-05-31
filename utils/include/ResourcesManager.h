#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SettingsManager.h"
#include "Consts.h"

class ResourcesManager {
public:
    static ResourcesManager &instance();

    sf::Texture *getTexture(Textures_t);
    sf::RectangleShape *getBackground();
    sf::Font *getFont();
    void playSound(const int index);
    void updateSounds();
    void playBackgroundMusic();
    void pauseBackgroundMusic();
    bool isBGMusicPlaying();
    sf::Texture *getSoundButton(const int loc);

private:
    ResourcesManager();
    sf::Sound m_sounds[NUMBER_OF_SOUNDS];
    sf::SoundBuffer m_sounds_buffs[NUMBER_OF_SOUNDS];
    sf::Texture m_texture[NUM_OF_TEXTURES];
    sf::RectangleShape m_background;
    sf::Music m_backgroundMusic;
    sf::Font m_font;
    std::string m_sound_file_names[NUMBER_OF_SOUNDS - 1] = {"tieP.wav", "tieR.wav","tieS.wav","winP.wav","winR.wav","winS.wav",
                                                        "blueJump.wav","blueTurn.wav","redJump.wav","redTurn.wav","WinFight.wav"
                                                        ,"Losefight.wav","Jumpsound.wav","Generatingweapon.wav","Chooseweapon.wav"};
    std::string m_soundstring[2] = {"MusicButton.png","FXButton.png"};
    sf::Texture m_soundButton[2];


};
