
#include "AvailableRooms.h"

AvailableRooms::AvailableRooms(PlayerModel player): p(player), m_window(*WindowManager::instance().getWindow()),m_background(*ResourcesManager::instance().getBackground()) {
    init();
    chooseRoom();
}

void AvailableRooms::init() {
    auto rooms = RoomService::getAvailableRooms();
    std::cout << rooms << "\n";
    for(auto room : rooms){
        std::string roomId = room["roomId"];
        std::string roomName = room["name"];
        availableRooms[roomId] = roomName;
    }

    for(auto room : availableRooms){
        std::cout << "id: " << room.first << " name: " << room.second << "\n";
    }

    m_text.setFont(*ResourcesManager::instance().getFont());
    m_text.setString("Choose room to join");
    m_text.setPosition(WINDOW_WIDTH/2 , WINDOW_HEIGHT*0.1);
    m_text.setCharacterSize(H1);
    m_text.setOrigin(m_text.getGlobalBounds().width/2,m_text.getGlobalBounds().height/2);
}

void AvailableRooms::chooseRoom() {
    WindowManager::instance().eventHandler(
            [](auto move, auto exit) { return false; },
            [](auto click, auto exit) { return false; },
            [](auto key, auto &exit) { return false; },
            [](auto type, auto exit) { return false; },
            [](auto &exit) {}
    );
}
