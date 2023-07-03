#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SettingsManager.h"
#include "Consts.h"
enum MusicMenu{
    Classic,
    NamalCity,
    Sigaliot,
    Acordim,
};
class ResourcesManager {
public:
    static ResourcesManager &instance();

    ResourcesManager(const ResourcesManager &other) = delete;
    ResourcesManager operator=(const ResourcesManager &other) = delete;

    sf::Texture *getTexture(Textures_t);
    sf::RectangleShape *getBackground();
    sf::Font *getFont();
    void playSound(int index);
    void updateSounds();
    void playBackgroundMusic();
    void setMusic(MusicMenu music);
    void switchSong(int i) {
        setMusic(MusicMenu((selectMusic + i) % NUM_OF_SONGS));}
    sf::Texture *getSoundButton(int loc);
    sf::Texture* getHelpScreenPages();
    sf::Image* getLogo();
    std::string getMusicPlaying() const;
private:
    ResourcesManager();
    enum MusicMenu selectMusic = Classic;
    sf::Sound m_sounds[NUMBER_OF_SOUNDS];
    sf::SoundBuffer m_sounds_buffs[NUMBER_OF_SOUNDS];
    sf::Texture m_texture[NUM_OF_TEXTURES];
    sf::Texture m_helpScreenPages[NUM_OF_HELP_SCREEN_PAGES];
    sf::RectangleShape m_background;
    sf::Music m_backgroundMusic[NUM_OF_SONGS];
    sf::Font m_font;
    std::string m_sound_file_names[NUMBER_OF_SOUNDS - 1] = {"tieP.wav", "tieR.wav","tieS.wav","winP.wav","winR.wav","winS.wav",
                                                        "blueJump.wav","blueTurn.wav","redJump.wav","redTurn.wav","WinFight.wav"
                                                        ,"Losefight.wav","Jumpsound.wav","gong.wav","win.wav","lost.wav"};
    std::string m_soundstring[2] = {"MusicButton.png","FXButton.png"};
    sf::Texture m_soundButton[2];
    sf::Image m_logo;

};
