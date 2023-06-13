
#include "RoomService.h"

namespace RoomService {

    json createRoom(RoomModel &room, std::string creator_name) {
        auto response = HttpRequestsManager::instance().postRequest(room.toJson(), BASE_URL + "/rooms.json");
        std::string roomId = response["name"];
        json data;
        data["name"] = creator_name;
        data["roomId"] = roomId;
        HttpRequestsManager::instance().putRequest(data, BASE_URL + "/available_rooms/" + roomId + ".json");
        return response;
    }

    json updateRoom(RoomModel &room) {
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

    json deleteAvailableRoom(std::string roomId) {
        auto response = HttpRequestsManager::instance().deleteRequest(BASE_URL + "/available_rooms/" + roomId + ".json");
        return response;
    }

    json setFlagAndHole(RoomModel &room, int row1,int row2){
        std::string url = BASE_URL + "/rooms/" + room.getRoomId() + "/board/" + std::to_string(row1) + ".json";
        HttpRequestsManager::instance().putRequest(room.getBoardRow(row1), url);
        url = BASE_URL + "/rooms/" + room.getRoomId() + "/board/" + std::to_string(row2) + ".json";
        auto response = HttpRequestsManager::instance().putRequest(room.getBoardRow(row2), url);
        return response;
    }

    json updateRematch(std::string roomId,std::string wantToRematch,int cell){
        std::string url = BASE_URL + "/rooms/" + roomId + "/board/0/" + std::to_string(cell) + ".json";
        auto response = HttpRequestsManager::instance().putRequest(wantToRematch,url);
        return response;
    }


}