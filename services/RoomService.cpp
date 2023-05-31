
#include "RoomService.h"

namespace RoomService {

    nlohmann::json createRoom(RoomModel room) {
        auto response = HttpRequestsManager::instance().postRequest(room.toJson(), BASE_URL + "/rooms.json");
        return response;
    }

    json updateRoom(RoomModel room) {
        auto response = HttpRequestsManager::instance().putRequest(room.toJson(), BASE_URL + "/rooms/" + room.getRoomId() + ".json");
        return response;
    }

    json deleteRoom(std::string roomId) {
        auto response = HttpRequestsManager::instance().deleteRequest(BASE_URL + "/rooms/" + roomId + ".json");
        return response;
    }

    RoomModel getRoom(std::string roomId) {
        auto response = HttpRequestsManager::instance().getRequest(BASE_URL + "/rooms/" + roomId + ".json");
        return RoomModel::fromJson(roomId, response);
    }
}