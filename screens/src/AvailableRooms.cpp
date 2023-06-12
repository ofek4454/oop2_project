
#include "../include/AvailableRooms.h"

AvailableRooms::AvailableRooms(PlayerModel player) : p(player), m_window(*WindowManager::instance().getWindow()),
                                                     m_background(*ResourcesManager::instance().getBackground()) {
    init();
    chooseRoom();
}

void AvailableRooms::init() {
    auto rooms = RoomService::getAvailableRooms();
    for (auto room: rooms) {
        std::string roomId = room["roomId"];
        std::string roomName = room["name"];
        availableRooms[roomId] = roomName;
    }

    m_text.setFont(*ResourcesManager::instance().getFont());
    m_text.setString("Choose room to join");
    m_text.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.1);
    m_text.setCharacterSize(H2);
    m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
    m_text.setFillColor(sf::Color::White);
    m_background = *ResourcesManager::instance().getBackground();

    float start_y = m_text.getGlobalBounds().top + m_text.getGlobalBounds().height*2 + WINDOW_HEIGHT*0.1;
    for (int i = 0; i < availableRooms.size(); i++){
        auto temp = sf::RectangleShape();
        temp.setSize(sf::Vector2f(WINDOW_WIDTH * 0.7, WINDOW_HEIGHT * 0.2));
        temp.setPosition(WINDOW_WIDTH / 2, (start_y) + (i * temp.getGlobalBounds().height * 1.5));
        temp.setOrigin((WINDOW_WIDTH * 0.7) / 2, (WINDOW_HEIGHT * 0.2) / 2);
        temp.setFillColor(GRAY_COLOR);
        temp.setOutlineThickness(1);
        temp.setOutlineColor(sf::Color::White);
        m_buttons.push_back(temp);
        auto text = sf::Text();
        auto it = availableRooms.begin();
        std::advance(it, i);
        text.setFont(*ResourcesManager::instance().getFont());
        text.setCharacterSize(H1);
        text.setString(it->second);
        text.setPosition(temp.getPosition().x - text.getGlobalBounds().width / 2,
                         temp.getPosition().y - text.getGlobalBounds().height);
        m_texts.push_back(text);

    }
}

void AvailableRooms::chooseRoom() {
    print();
    WindowManager::instance().eventHandler(
            [](auto move, auto exit) { return false; },
            [this](auto click, auto &exit) {
                clickHandler(click,exit);
                return false;
            },
            [this](auto key, auto &exit) {
                if(key.code == sf::Keyboard::Escape){
                    exit = true;
                    UserService::deleteUser(p.m_uid);
                }
                return false;
            },
            [](auto type, auto exit) { return false; },
            [this](auto offset, auto exit) {
                if(!availableRooms.empty()) print(offset);
                return false;
            },
            [](auto &exit) {}
    );
}

void AvailableRooms::print(int offset) {
    m_window.clear();
    m_window.draw(m_background);
    if(m_buttons.empty()){
        m_text.setString("No Available room to join in...");
        m_text.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT/2);
        m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
        m_window.draw(m_text);
        m_window.display();
        return;
    }

    if ((m_buttons[0].getGlobalBounds().height * m_buttons.size() * 1.5) < WINDOW_HEIGHT * 0.85)
        offset = 0;
    else if (m_buttons[0].getPosition().y + offset > (WINDOW_HEIGHT * 0.15))
        offset = WINDOW_HEIGHT * 0.15 - m_buttons[0].getPosition().y;
    else if (m_buttons[m_buttons.size() - 1].getPosition().y + offset < WINDOW_HEIGHT * 0.85)
        offset = WINDOW_HEIGHT * 0.85 - m_buttons[m_buttons.size() - 1].getPosition().y;

    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons[i].move(sf::Vector2f(0, offset));
        m_texts[i].move(sf::Vector2f(0, offset));
        m_window.draw(m_buttons[i]);
        m_window.draw(m_texts[i]);
    }
    m_window.draw(m_text);
    m_window.display();
}

void AvailableRooms::clickHandler(sf::Event::MouseButtonEvent &click,bool &exit) {
    for (int i = 0; i < m_buttons.size(); i++) {
        if (m_buttons[i].getGlobalBounds().contains(m_window.mapPixelToCoords({click.x, click.y}))) {
            auto map_it = availableRooms.begin();
            std::advance(map_it,i);
            RoomState::instance().joinRoom(map_it->first,p.m_uid);
            auto enemyUser = UserService::getUser(RoomState::instance().getRoom().creatorUid());
            Controller(p ,enemyUser, false);
            exit = true;
            break;
        }
    }
}