//
// Created by Bar Kobi on 20/05/2023.
//

#include "ResourcesManager.h"

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager resource;
    return resource;
}

ResourcesManager::ResourcesManager() {
    m_backgroundMusic[Classic].openFromFile("BackGroundMusic.wav");
    m_backgroundMusic[NamalCity].openFromFile("eyalgolanbackgroundmusic.wav");
    m_backgroundMusic[Sigaliot].openFromFile("sigaliot.wav");
    m_backgroundMusic[Acordim].openFromFile("acordim.wav");
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
    m_texture[ScissorsFlip].loadFromFile("ScissorsFlipping.png");
    m_texture[PaperFlip].loadFromFile("PaperFlipping.png");
    m_texture[RockFlip].loadFromFile("RockFlipping.png");
    m_texture[ThrowPlayer].loadFromFile("throwAnimationPlayer.png");
    m_texture[RefereeDeclareWinning].loadFromFile("end.png");
    m_texture[WinningJump].loadFromFile("winner.png");
    m_texture[Logo].loadFromFile("Logo.png");
    m_texture[Logo].setSmooth(true);
    m_texture[UndefinedWar].loadFromFile("tieU.png");
    m_texture[AngryEmoji].loadFromFile("angry.png");
    m_texture[CryEmoji].loadFromFile("cry.png");
    m_texture[FingerEmoji].loadFromFile("finger.png");
    m_texture[LaughEmoji].loadFromFile("laugh.png");
    m_texture[ScammerEmoji].loadFromFile("scammer.png");
    m_texture[SleepEmoji].loadFromFile("sleep.png");
    m_texture[ChatBubble].loadFromFile("bubble.png");
    m_texture[ChatMenu].loadFromFile("chat.png");
    m_texture[PaperUndefined].loadFromFile("papervsund.png");
    m_texture[RockUndefined].loadFromFile("rockvsund.png");
    m_texture[ScissorsUndefined].loadFromFile("scivsund.png");
    m_texture[UndefinedPaper].loadFromFile("undvspaper.png");
    m_texture[UndefinedRock].loadFromFile("undvsrock.png");
    m_texture[UndefinedScissors].loadFromFile("undvssci.png");
    m_texture[GameSeconds].loadFromFile("seconds.png");
    m_texture[ScrollSprite].loadFromFile("scroll.png");
    m_texture[StopPlay].loadFromFile("stopPlayButton.png");
    m_texture[NextSong].loadFromFile("nextSong.png");
    m_texture[PrevSong].loadFromFile("prevSong.png");




    m_helpScreenPages[0].loadFromFile("Help-Page1.png");
    m_helpScreenPages[1].loadFromFile("Help-Page2.png");
    m_helpScreenPages[2].loadFromFile("Help-Page3.png");
    m_helpScreenPages[3].loadFromFile("Help-Page4.png");

    m_background.setSize(sf::Vector2f (WINDOW_WIDTH, WINDOW_HEIGHT));
    m_background.setFillColor(BLUE_COLOR);
    m_font.loadFromFile("AlfaSlabOne-Regular.ttf");

    for (int i = 0; i < NUMBER_OF_SOUNDS - 1; i++) {
        m_sounds_buffs[i].loadFromFile(m_sound_file_names[i]);
        m_sounds[i].setBuffer(m_sounds_buffs[i]);
    }
    for(int i = 0; i < 2;i++){
        m_soundButton[i].loadFromFile(m_soundstring[i]);
        m_soundButton[i].setSmooth(true);
    }

    m_logo.loadFromFile("Logo.png");
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
    if(!SettingsManager::instance().getMusicSwitch())
        return;

    m_backgroundMusic[selectMusic].setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic[selectMusic].setLoop(true);
    m_backgroundMusic[selectMusic].play();
}


void ResourcesManager::updateSounds() {
    if(!SettingsManager::instance().getMusicSwitch()){
        m_backgroundMusic[selectMusic].stop();
        return;
    }

    if(m_backgroundMusic[selectMusic].getStatus() != sf::Music::Status::Playing)
        m_backgroundMusic[selectMusic].play();

    m_backgroundMusic[selectMusic].setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic[selectMusic].setLoop(true);

}

sf::Texture *ResourcesManager::getSoundButton(const int loc) {
    return &m_soundButton[loc];
}

sf::Texture *ResourcesManager::getHelpScreenPages() {
    return m_helpScreenPages;
}

sf::Image *ResourcesManager::getLogo() {
    return &m_logo;
}

void ResourcesManager::setMusic(MusicMenu music) {
    if((int)music == -1)
        music = MusicMenu(NUM_OF_SONGS - 1);
    if(music != selectMusic){
        m_backgroundMusic[selectMusic].stop();
        selectMusic = music;}
}

std::string ResourcesManager::getMusicPlaying() const {
    switch (selectMusic) {
        case Acordim:
            return "Osher Cohen - Acordim in the Nights";
            break;
        case NamalCity:
            return "Eyal Golan - City Of Namal";
            break;
        case Classic:
            return "Classic Game Music";
            break;
        case Sigaliot:
            return "Omer Adam & David Broza - Sigaliot";
        default:
            return "";
    }
}
