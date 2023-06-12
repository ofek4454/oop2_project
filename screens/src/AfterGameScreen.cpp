//
// Created by Bar Kobi on 09/06/2023.
//

#include "AfterGameScreen.h"
#include "SoundFlip.h"

AfterGameScreen::AfterGameScreen(bool isMeWon, PlayerModel userModel,PlayerModel enemyModel,Turn_t myTurn) : m_isMeWinner(isMeWon), m_userModel(userModel),
                                                                                                             m_enemyModel(enemyModel),m_myServerTurn(myTurn), m_window(
        WindowManager::instance().getWindow()) {
    m_background = *ResourcesManager::instance().getBackground();
    m_playerJump.setTexture(*ResourcesManager::instance().getTexture(WinningJump));
    if(m_isMeWinner)
        m_playerJump.setTextureRect(sf::IntRect(0, 0, 70, 90));
    else
        m_playerJump.setTextureRect(sf::IntRect(0, 90, 70, 90));
    m_playerJump.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.7,WINDOW_HEIGHT * 0.45));
    m_refereeFlag.setTexture(*ResourcesManager::instance().getTexture(RefereeDeclareWinning));
    if(m_isMeWinner)
        m_refereeFlag.setTextureRect(sf::IntRect(0, 0, 200, 125));
    else
        m_refereeFlag.setTextureRect(sf::IntRect(0, 125, 200, 125));
    m_refereeFlag.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.3,WINDOW_HEIGHT * 0.4));
    std::string text = "";
    text = "The Winner Is: ";
    if(isMeWon)
        text += userModel.m_name + "!";
    else
        text += enemyModel.m_name + "!";

    m_text.setFont(*ResourcesManager::instance().getFont());
    m_text.setString(text);
    m_text.setCharacterSize(50);
    m_text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - m_text.getGlobalBounds().width / 2, WINDOW_HEIGHT * 0.2));
    m_text.setOutlineThickness(2);
    m_text.setOutlineColor(sf::Color::Black);
    m_rematchText.setFont(*ResourcesManager::instance().getFont());
    m_rematchText.setString("Rematch?");
    m_rematchText.setCharacterSize(30);
    m_rematchText.setOrigin(sf::Vector2f(m_rematchText.getGlobalBounds().width / 2, m_rematchText.getGlobalBounds().height / 2));
    m_rematchText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - m_rematchText.getGlobalBounds().width / 2, WINDOW_HEIGHT * 0.8));
    m_rematchText.setOutlineThickness(2);
    m_rematchText.setOutlineColor(sf::Color::Black);
    m_originalCursor.loadFromSystem(sf::Cursor::Arrow);
    m_clickable.loadFromSystem(sf::Cursor::Hand);
    m_jumpingRect = m_playerJump.getTextureRect();
    m_refRect = m_refereeFlag.getTextureRect();
    m_playerJump.setScale(1.5f,1.5f);
    m_refereeFlag.setScale(1.5f,1.5f);

    playLosingAnimation();

}

void AfterGameScreen::playLosingAnimation() {
    sf::Clock refAnimationClock,jumpingClock;
    print();
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                handleHover(move);
                return false; },
            [](auto click, auto &exit) {
                return false;
            },
            [this](auto key, auto &exit) {
                if(key.code == sf::Keyboard::Escape){
                    exit = true;
                }
                return false;
            },
            [](auto type, auto exit) { return false; },
            [this](auto offset, auto exit) {
                return false;
            },
            [this,&refAnimationClock,&jumpingClock](auto &exit) {
                auto time = refAnimationClock.getElapsedTime().asSeconds();
                if(time > 0.3){
                    refAnimationClock.restart().asSeconds();
                    changeRefereeTextureRect();
                }
                auto time2 = jumpingClock.getElapsedTime().asSeconds();
                if(time2 > 0.1){
                    jumpingClock.restart().asSeconds();
                    changeJumpingTextureRect();
                }
                print();
            }
    );

}

void AfterGameScreen::print() {
    m_window->clear();
    m_window->draw(m_background);
    SoundFlip::instance().draw(*m_window);
    m_window->draw(m_refereeFlag);
    m_window->draw(m_playerJump);
    m_window->draw(m_text);
    m_window->draw(m_rematchText);
    m_window->display();
}

void AfterGameScreen::handleHover(sf::Event::MouseMoveEvent &event) {
    if(m_rematchText.getGlobalBounds().contains(event.x,event.y)){
        m_rematchText.setScale(1.1,1.1);
        m_window->setMouseCursor(m_clickable);
    }
    else{
        m_rematchText.setScale(1,1);
        m_window->setMouseCursor(m_originalCursor);
    }
}

void AfterGameScreen::handleClick(sf::Event::MouseButtonEvent &event) {
    if(m_rematchText.getGlobalBounds().contains(event.x,event.y)) {
        //TODO handle rematch
    }
}

void AfterGameScreen::changeRefereeTextureRect() {
    static bool end = false;
    if(!end){
        m_refRect.left = 200;
        m_refereeFlag.setTextureRect(m_refRect);
        end = true;
    }
    else{
        m_refRect.left = 0;
        m_refereeFlag.setTextureRect(m_refRect);
        end = false;
    }
}

void AfterGameScreen::changeJumpingTextureRect() {
    static bool middle = false;
    if(!middle)
        m_jumpingRect.left -= 70;
    else
        m_jumpingRect.left += 70;

    if (m_jumpingRect.left < 0 && !middle) {
        middle = true;
        m_jumpingRect.left = 0;
        m_playerJump.setTextureRect(m_jumpingRect);
        return;
    }
    if(m_jumpingRect.left > 280 && middle){
        middle = false;
        m_jumpingRect.left = 280;
        m_playerJump.setTextureRect(m_jumpingRect);
        return;
    }

    m_playerJump.setTextureRect(m_jumpingRect);
    return;

}
