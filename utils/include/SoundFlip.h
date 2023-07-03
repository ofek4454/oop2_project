#pragma once

#include "SettingsManager.h"
#include "ResourcesManager.h"

// enum for sound buttons
enum Sound_buttons_t{
    MUSIC,
    SOUND
};

/**
 * Singleton class for the sound switches.
 */
class SoundFlip {
public:
    // Functions
    static SoundFlip& instance();

    SoundFlip(const SoundFlip &other) = delete;
    SoundFlip operator=(const SoundFlip &other) = delete;

    void draw(sf::RenderWindow &window);
    void checkIfMouseContains(const sf::Event::MouseButtonEvent& event);
    void checkIfKeyboard(const sf::Event::KeyEvent &event);
private:
    // private C-Tor
    SoundFlip();
    // members
    sf::CircleShape m_soundButtons[2];
    int m_fxClicked = 0,m_musicClicked = 0;
};


