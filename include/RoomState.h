#pragma once
#include "RoomModel.h"
#include "RoomService.h"

class RoomState{
friend class RoomModel;
public:
    RoomState() = default;
    void createRoom(std::string creator_id);

public:
    RoomModel room;
};
