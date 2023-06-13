//
// Created by Bar Kobi on 09/06/2023.
//

#include "AfterGameScreen.h"
#include "SoundFlip.h"

AfterGameScreen::AfterGameScreen(bool isMeWon, PlayerModel userModel, PlayerModel enemyModel, Turn_t myTurn)
        : m_isMeWinner(isMeWon), m_userModel(userModel),
          m_enemyModel(enemyModel), m_myServerTurn(myTurn), m_window(
                WindowManager::instance().getWindow()) {
    m_background = *ResourcesManager::instance().getBackground();
    m_playerJump.setTexture(*ResourcesManager::instance().getTexture(WinningJump));
    if (m_isMeWinner)
        m_playerJump.setTextureRect(sf::IntRect(0, 0, 70, 90));
    else
        m_playerJump.setTextureRect(sf::IntRect(0, 90, 70, 90));
    m_playerJump.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.7, WINDOW_HEIGHT * 0.45));
    m_refereeFlag.setTexture(*ResourcesManager::instance().getTexture(RefereeDeclareWinning));
    if (m_isMeWinner)
        m_refereeFlag.setTextureRect(sf::IntRect(0, 0, 200, 125));
    else
        m_refereeFlag.setTextureRect(sf::IntRect(0, 125, 200, 125));
    m_refereeFlag.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.3, WINDOW_HEIGHT * 0.4));
    std::string text = "";
    text = "The Winner Is: ";
    if (isMeWon)
        text += userModel.m_name + "!";
    else
        text += enemyModel.m_name + "!";

    m_text.setFont(*ResourcesManager::instance().getFont());
    m_text.setString(text);
    m_text.setCharacterSize(H1);
    m_text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - m_text.getGlobalBounds().width / 2, WINDOW_HEIGHT * 0.2));
    m_text.setOutlineThickness(2);
    m_text.setOutlineColor(sf::Color::Black);
    m_rematchText.setFont(*ResourcesManager::instance().getFont());
    m_rematchText.setString("Rematch?");
    m_rematchText.setCharacterSize(H2);
    m_rematchText.setOrigin(
            sf::Vector2f(m_rematchText.getGlobalBounds().width / 2, m_rematchText.getGlobalBounds().height / 2));
    m_rematchText.setPosition(
            sf::Vector2f(WINDOW_WIDTH / 2 - m_rematchText.getGlobalBounds().width / 2, WINDOW_HEIGHT * 0.8));
    m_rematchText.setOutlineThickness(2);
    m_rematchText.setOutlineColor(sf::Color::Black);
    m_originalCursor.loadFromSystem(sf::Cursor::Arrow);
    m_clickable.loadFromSystem(sf::Cursor::Hand);
    m_jumpingRect = m_playerJump.getTextureRect();
    m_refRect = m_refereeFlag.getTextureRect();
    m_playerJump.setScale(1.5f, 1.5f);
    m_refereeFlag.setScale(1.5f, 1.5f);
    m_yesNoTexts[0].setString("Yes");
    m_yesNoTexts[1].setString("No");
    for (auto &txt: m_yesNoTexts) {
        txt.setFont(*ResourcesManager::instance().getFont());
        txt.setCharacterSize(H3);
        txt.setOrigin(
                sf::Vector2f(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2));
        txt.setPosition(sf::Vector2f(
                m_rematchText.getPosition().x,
                m_rematchText.getPosition().y + m_rematchText.getGlobalBounds().height + txt.getGlobalBounds().height));
        txt.setOutlineThickness(2);
        txt.setOutlineColor(sf::Color::Black);
    }
    m_yesNoTexts[0].move(WINDOW_WIDTH * -0.1,0);
    m_yesNoTexts[1].move(WINDOW_WIDTH * 0.1,0);

    playLosingAnimation();

}

void AfterGameScreen::playLosingAnimation() {
    sf::Clock refAnimationClock, jumpingClock;
    print();
    WindowManager::instance().eventHandler(
            [this](auto move, auto exit) {
                if (!m_waitingForOpponent)
                    handleHover(move);
                return false;
            },
            [this](auto click, auto &exit) {
                if (!m_waitingForOpponent)
                    handleClick(click, exit);
                return false;
            },
            [this](auto key, auto &exit) {
                if (key.code == sf::Keyboard::Escape) {
                    if (m_waitingForOpponent)
                        RoomState::instance().wantToRematch(false);
                    exit = true;
                }
                return false;
            },
            [](auto type, auto exit) { return false; },
            [this](auto offset, auto exit) {
                return false;
            },
            [this, &refAnimationClock, &jumpingClock](auto &exit) {
                if (!m_waitingForOpponent) {
                    auto time = refAnimationClock.getElapsedTime().asSeconds();
                    if (time > 0.3) {
                        refAnimationClock.restart().asSeconds();
                        changeRefereeTextureRect();
                    }
                    auto time2 = jumpingClock.getElapsedTime().asSeconds();
                    if (time2 > 0.1) {
                        jumpingClock.restart().asSeconds();
                        changeJumpingTextureRect();
                    }
                }
                else{
                    checkOpponentsResponse(exit);
                }
                print();

            }
    );

}

void AfterGameScreen::print() {
    m_window->clear();
    m_window->draw(m_background);
    SoundFlip::instance().draw(*m_window);
    if(!m_waitingForOpponent){
        m_window->draw(m_refereeFlag);
        m_window->draw(m_playerJump);
        m_window->draw(m_rematchText);
        m_window->draw(m_yesNoTexts[0]);
        m_window->draw(m_yesNoTexts[1]);
    }
    m_window->draw(m_text);
    m_window->display();
}

void AfterGameScreen::handleHover(sf::Event::MouseMoveEvent &event) {
    if (m_rematchText.getGlobalBounds().contains(event.x, event.y)) {
        m_rematchText.setScale(1.1, 1.1);
        m_window->setMouseCursor(m_clickable);
    } else {
        m_rematchText.setScale(1, 1);
        m_window->setMouseCursor(m_originalCursor);
    }
}

void AfterGameScreen::handleClick(sf::Event::MouseButtonEvent &event, bool &exit) {
    bool rematch;
    if (m_yesNoTexts[0].getGlobalBounds().contains(event.x, event.y)) {
        RoomState::instance().wantToRematch(true);
        m_waitingForOpponent = true;
        m_text.setString("Waiting For Opponent..");
        m_text.setOrigin(sf::Vector2f(m_text.getGlobalBounds().width / 2,m_text.getGlobalBounds().height / 2));
    }
    if (m_yesNoTexts[1].getGlobalBounds().contains(event.x, event.y)) {
        RoomState::instance().wantToRematch(false);
        exit = true;
    }
}

void AfterGameScreen::changeRefereeTextureRect() {
    static bool end = false;
    if (!end) {
        m_refRect.left = 200;
        m_refereeFlag.setTextureRect(m_refRect);
        end = true;
    } else {
        m_refRect.left = 0;
        m_refereeFlag.setTextureRect(m_refRect);
        end = false;
    }
}

void AfterGameScreen::changeJumpingTextureRect() {
    static bool middle = false;
    if (!middle)
        m_jumpingRect.left -= 70;
    else
        m_jumpingRect.left += 70;

    if (m_jumpingRect.left < 0 && !middle) {
        middle = true;
        m_jumpingRect.left = 0;
        m_playerJump.setTextureRect(m_jumpingRect);
        return;
    }
    if (m_jumpingRect.left > 280 && middle) {
        middle = false;
        m_jumpingRect.left = 280;
        m_playerJump.setTextureRect(m_jumpingRect);
        return;
    }

    m_playerJump.setTextureRect(m_jumpingRect);
    return;

}

void AfterGameScreen::checkOpponentsResponse(bool &exit) {
    static sf::Clock timerForCheck;
    auto time = timerForCheck.getElapsedTime().asSeconds();
    if(time < 1) return;

    timerForCheck.restart();
    auto tmp = RoomState::instance().isOpponentWantsToRematch();
    if(tmp == 2)
        return;
    if(tmp == 1)
        EventLoop::instance().addEvent(Event(Rematch));
    exit = true;
}
