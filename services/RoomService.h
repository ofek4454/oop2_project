#pragma once

#include <nlohmann/json.hpp>
#include "env.h"
#include "iostream"
#include "curl/curl.h"
#include "RoomModel.h"

using json = nlohmann::json;

namespace RoomService {
    json createRoom(RoomModel &room, const std::string &creator_name);

    json updateRoom(RoomModel &room);

    RoomModel getRoom(const std::string &roomId);

    json deleteRoom(const std::string &roomId);

    json getAvailableRooms();

    json deleteAvailableRoom(const std::string &roomId);

    json setFlagAndHole(RoomModel &room, int row1, int row2);

    json updateRematch(RoomModel &room);

    json updatedLastMove(RoomModel &room);

    json updateRematch(const std::string &roomId, const std::string &wantToRematch, int cell);

    json logout(std::string roomId);
}