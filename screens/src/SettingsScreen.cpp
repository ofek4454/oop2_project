#include <utility>

#include "../include/SettingsScreen.h"
#include "SoundFlip.h"

/**
 * create setting screen and init all the components on the screen.
 * @param window the window to show the screen in.
 */
SettingsScreen::SettingsScreen(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)){
    m_cursor.loadFromSystem(sf::Cursor::Hand);

    auto volume = SettingsManager::instance().getVolume();
    m_volume_text = TextClass("Volume: ",H2 ,sf::Vector2f(WINDOW_WIDTH/2 , WINDOW_HEIGHT*0.28f)).getText();

    m_volume_line.setSize(sf::Vector2f((WINDOW_WIDTH - (m_volume_text.getPosition().x + m_volume_text.getGlobalBounds().width))*0.5f ,5.f));
    m_volume_line.setFillColor(sf::Color::White);
    m_volume_line.setPosition(m_volume_text.getPosition().x+m_volume_text.getGlobalBounds().width*1.3f, m_volume_text.getPosition().y+(m_volume_text.getGlobalBounds().height/2.f)-5.f);

    auto width = (m_volume_line.getPosition().x + m_volume_line.getGlobalBounds().width)- m_volume_text.getPosition().x;
    m_volume_text.move(-(width/2.f),0.f);
    m_volume_line.move(-(width/2.f),0.f);

    m_volume_drag.setRadius(20.f);
    m_volume_drag.setPosition(m_volume_line.getPosition().x + ((m_volume_line.getGlobalBounds().width)* volume/100.f) ,m_volume_line.getPosition().y-m_volume_line.getSize().y);
    m_volume_drag.setOrigin(m_volume_drag.getRadius()/2.f,m_volume_drag.getRadius()/2.f);
    m_volume_drag.setFillColor(sf::Color::White);

    m_music_text = TextClass("Music :",H2,sf::Vector2f(m_volume_text.getPosition().x , m_volume_text.getPosition().y + (m_volume_text.getGlobalBounds().height*4.f))).getText();
    volume = SettingsManager::instance().getBGMVolume();

    m_music_line.setSize(m_volume_line.getSize());
    m_music_line.setFillColor(sf::Color::White);
    m_music_line.setPosition(m_volume_line.getPosition().x, m_music_text.getPosition().y+(m_music_text.getGlobalBounds().height/2.f)-5.f);

    m_music_drag.setRadius(20.f);
    m_music_drag.setPosition(m_music_line.getPosition().x + ((m_music_line.getGlobalBounds().width)* volume/100.f) ,m_music_line.getPosition().y-m_music_line.getSize().y);
    m_music_drag.setOrigin(m_music_drag.getRadius()/2.f,m_music_drag.getRadius()/2.f);
    m_music_drag.setFillColor(sf::Color::White);

    m_backBtn = TextClass("<-",H2,sf::Vector2f(WINDOW_WIDTH * 0.05f,WINDOW_WIDTH * 0.05f)).getText();

    m_MusicMenuTitle = TextClass("Music Menu",H2,sf::Vector2f(WINDOW_WIDTH * 0.5,m_music_text.getPosition().y + WINDOW_HEIGHT * 0.1)).getText();
    for(int i = 0;i < NUM_OF_SONGS;i++){
        if(i == 0)
            m_musicNames[i] = TextClass(m_numOfSongs[i],H3,sf::Vector2f(WINDOW_WIDTH*0.5,m_MusicMenuTitle.getPosition().y + m_MusicMenuTitle.getGlobalBounds().height + WINDOW_HEIGHT * 0.05)).getText();
        else
            m_musicNames[i] = TextClass(m_numOfSongs[i],H3,sf::Vector2f(WINDOW_WIDTH*0.5,m_musicNames[i-1].getPosition().y + m_musicNames[i-1].getGlobalBounds().height + WINDOW_HEIGHT * 0.05)).getText();

    }
}

/**
 * run the event loop of the screen.
 */
void SettingsScreen::run() {
    m_window->setActive(true);
    bool exit = false;
    while (m_window->isOpen() && !exit){
        eventHandler(exit);
        printScreen();
    }
}

/**
 * handle mouse click
 * @param clickevent event
 * @return screen need to be closed.
 */
bool SettingsScreen::handleClick(const sf::Event::MouseButtonEvent &clickevent) {
    if (m_volume_clicked) {
        m_volume_clicked = false;
    }
    else if(m_music_clicked)
        m_music_clicked = false;

    else if(m_backBtn.getGlobalBounds().contains(clickevent.x,clickevent.y)){
        m_window->setMouseCursor(m_originalCursor);
        return false;
    }

    for(int i = 0; i < NUM_OF_SONGS;i++){
        if(m_musicNames[i].getGlobalBounds().contains(clickevent.x,clickevent.y)){
            ResourcesManager::instance().setMusic(MusicMenu(i));
            ResourcesManager::instance().updateSounds();
        }
    }

    SoundFlip::instance().checkIfMouseContains(clickevent);

    return true;
}

/**
 * handle mouse movement
 * @param moveevent event
 */
void SettingsScreen::handleMouseMove(const sf::Event::MouseMoveEvent &moveevent) {
    if(m_volume_clicked){
        m_volume_drag.setPosition(moveevent.x, m_volume_drag.getPosition().y);
        if(m_volume_drag.getPosition().x < m_volume_line.getPosition().x)
            m_volume_drag.setPosition(m_volume_line.getPosition().x, m_volume_drag.getPosition().y);
        else if(m_volume_drag.getPosition().x > m_volume_line.getPosition().x+m_volume_line.getGlobalBounds().width)
            m_volume_drag.setPosition(m_volume_line.getPosition().x+m_volume_line.getGlobalBounds().width, m_volume_drag.getPosition().y);

        int vol = ((m_volume_drag.getPosition().x - m_volume_line.getPosition().x) /(m_volume_line.getGlobalBounds().width))*100;
        SettingsManager::instance().setVolume(vol);
    }
    else if(m_music_clicked){
        m_music_drag.setPosition(moveevent.x, m_music_drag.getPosition().y);
        if(m_music_drag.getPosition().x < m_music_line.getPosition().x)
            m_music_drag.setPosition(m_music_line.getPosition().x, m_music_drag.getPosition().y);
        else if(m_music_drag.getPosition().x > m_music_line.getPosition().x+m_music_line.getGlobalBounds().width)
            m_music_drag.setPosition(m_music_line.getPosition().x+m_music_line.getGlobalBounds().width, m_music_drag.getPosition().y);

        int vol = ((m_music_drag.getPosition().x - m_music_line.getPosition().x) /(m_music_line.getGlobalBounds().width))*100;
        SettingsManager::instance().setBGMusicVolume(vol);
        ResourcesManager::instance().updateSounds();
    }
}

/**
 * main event handler.
 * @param exit update if need to exit the screen.
 */
void SettingsScreen::eventHandler(bool &exit) {
    if (auto event = sf::Event{}; m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                SoundFlip::instance().checkIfKeyboard(event.key);
                if(event.key.code == sf::Keyboard::Escape)
                    exit = true;
                break;
            case sf::Event::MouseButtonReleased:
                exit = !handleClick(event.mouseButton);
                break;
            case sf::Event::MouseButtonPressed:
                if(m_MusicMenuTitle.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    m_musicPressed = !m_musicPressed;
                if(m_volume_drag.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                    m_volume_clicked = true;
                if(m_music_drag.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                    m_music_clicked = true;
                break;
            case sf::Event::MouseMoved:{
                handleHover(event.mouseMove);
                if(m_volume_clicked || m_music_clicked)
                    handleMouseMove(event.mouseMove);
                if(m_backBtn.getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y) || m_MusicMenuTitle.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                    m_window->setMouseCursor(m_cursor);
                else
                    m_window->setMouseCursor(m_originalCursor);
            }
                break;
            case sf::Event::Closed:
                m_window->close();
                break;
        }
    }
}

/**
 * print the screen to the window.
 */
void SettingsScreen::printScreen() {
    m_window->clear();
    auto background = sf::RectangleShape();
    background.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    background.setTexture(ResourcesManager::instance().getTexture(Background));

    m_window->draw(background);

    int vol = SettingsManager::instance().getVolume();
    std::string str = "volume: ";
    m_volume_text.setString(str + std::to_string(vol));

    vol = SettingsManager::instance().getBGMVolume();
    str = "music: ";
    m_music_text.setString(str + std::to_string(vol));

    m_window->draw(m_volume_line);
    m_window->draw(m_volume_drag);
    m_window->draw(m_volume_text);
    m_window->draw(m_backBtn);
    m_window->draw(m_music_text);
    m_window->draw(m_music_drag);
    m_window->draw(m_music_line);

    m_window->draw(m_MusicMenuTitle);
    if(m_musicPressed)
        for(auto musicTxt : m_musicNames)
            m_window->draw(musicTxt);

    SoundFlip::instance().draw(*m_window);

    m_window->display();

}

/**
 * save the settings when go out from the screen.
 */
SettingsScreen::~SettingsScreen() {
    SettingsManager::instance().save_settings();
}

void SettingsScreen::handleHover(sf::Event::MouseMoveEvent &event) {
    for(auto &musicTxt : m_musicNames)
        if(musicTxt.getGlobalBounds().contains(event.x, event.y)){
            musicTxt.setOutlineThickness(2);
            musicTxt.setOutlineColor(sf::Color::Black);
        }else
            musicTxt.setOutlineThickness(0);
}
