
#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(PlayerModel player) : p(player), m_window(*WindowManager::instance().getWindow()),
                                               m_background(*ResourcesManager::instance().getBackground()) {
    m_loadingText.setFont(*ResourcesManager::instance().getFont());
    m_loadingText.setString("Waiting For The Second Player...");
    m_loadingText.setCharacterSize(40);
    m_loadingText.setPosition(
            sf::Vector2f(WINDOW_WIDTH / 2 - m_loadingText.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2));
    init();
    waitForOpponent();
}

void WaitingRoom::init() {
    m_text.setFont(*ResourcesManager::instance().getFont());
    m_text.setString("Waiting for opponent...");
    m_text.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    m_text.setCharacterSize(H1);
    m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
}

void WaitingRoom::waitForOpponent() {
    sf::Clock clock;
    m_window.clear();
    m_window.draw(m_background);
    m_window.draw(m_text);
    m_window.display();
    WindowManager::instance().eventHandler(
            [](auto move, auto exit) { return false; },
            [](auto click, auto exit) { return false; },
            [](auto key, auto &exit) {
                if (key.code == sf::Keyboard::Escape) {
                    RoomState::instance().deleteRoom();
                    exit = true;
                }
                return false;
            },
            [](auto type, auto exit) { return false; },
            [](auto offset, auto exit) { return false; },
            [this, &clock](auto &exit) {
                if (clock.getElapsedTime().asSeconds() > 1) {
                    clock.restart();
                    if (RoomState::instance().isOpponentJoined()) {
                        enemy = UserService::getUser(RoomState::instance().getRoom().player2Uid());
                        do{
                            Controller controller(p, enemy, true);
                            if(!EventLoop::instance().hasEvent()) break;
                            RoomState::instance().resetRoom();
                        }while(EventLoop::instance().hasEvent() && (EventLoop::instance().popEvent().getEventType() == Rematch));
                        exit = true;
                    }
                }
            }
    );
}