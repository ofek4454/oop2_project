
#include "RoomService.h"

namespace RoomService {

    json createRoom(RoomModel room, std::string creator_name) {
        auto response = HttpRequestsManager::instance().postRequest(room.toJson(), BASE_URL + "/rooms.json");
        std::string roomId = response["name"];
        json data;
        data["name"] = creator_name;
        data["roomId"] = roomId;
        HttpRequestsManager::instance().putRequest(data, BASE_URL + "/available_rooms/" + roomId + ".json");
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

    json getAvailableRooms(){
        auto response = HttpRequestsManager::instance().getRequest(BASE_URL + "/available_rooms.json");
        return response;
    }
}