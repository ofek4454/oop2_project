#pragma once
#include "SFML/Graphics.hpp"
#include "SettingsManager.h"
#include "TextClass.h"
#include "WindowManager.h"

/**
 * Settings class that handles the setting window display
 */
class SettingsScreen{
public:
    // C-Tor & D-Tor
    SettingsScreen(std::shared_ptr<sf::RenderWindow> window);
    ~SettingsScreen();
    void run();

private:
    // members
    std::shared_ptr<sf::RenderWindow> m_window;
    sf::Cursor m_cursor;
    sf::Cursor m_originalCursor;
    sf::Text m_volume_text, m_music_text;
    sf::Text m_MusicMenuTitle;
    sf::Text m_musicNames[NUM_OF_SONGS];
    std::string m_numOfSongs[NUM_OF_SONGS] = {"Classic","Eyal Golan - City of Namal","Omer Adam & David Broza - Sigaliot","Osher Cohen - Acordim In the Nights"};
    sf::CircleShape m_volume_drag;
    sf::RectangleShape m_volume_line;
    sf::CircleShape m_music_drag;
    sf::RectangleShape m_music_line;
    sf::Text m_backBtn;

    bool m_musicPressed = false;
    bool m_volume_clicked = false;
    bool m_music_clicked = false;

    // private functions
    void handleHover(sf::Event::MouseMoveEvent &event);
    bool handleClick(const sf::Event::MouseButtonEvent &clickevent);
    void handleMouseMove(const sf::Event::MouseMoveEvent &moveevent);
    void eventHandler(bool &exit);
    void printScreen();
};