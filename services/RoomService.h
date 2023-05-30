#pragma once

#include <nlohmann/json.hpp>
#include "env.h"
#include "iostream"
#include "curl/curl.h"
#include "RoomModel.h"

using json = nlohmann::json;

namespace RoomService{
    json createRoom(RoomModel room);
    json updateRoom(RoomModel room);
    RoomModel getRoom(std::string roomId);
    json deleteRoom(std::string roomId);
}