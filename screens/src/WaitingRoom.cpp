
#include "../include/WaitingRoom.h"

WaitingRoom::WaitingRoom(PlayerModel player) : p(player), m_window(*WindowManager::instance().getWindow()),
                                               m_background(*ResourcesManager::instance().getBackground()) {
    m_loadingText = TextClass("Waiting For The Second Player...",40,sf::Vector2f(WINDOW_WIDTH / 2 - m_loadingText.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2)).getText();
    init();
    waitForOpponent();
}

void WaitingRoom::init() {
    m_text = TextClass("Waiting For The Opponent...",H1,sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)).getText();
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