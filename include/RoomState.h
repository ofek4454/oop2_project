#pragma once
#include "RoomModel.h"
#include "RoomService.h"

class RoomState{
friend class RoomModel;
public:
    void createRoom(std::string creator_id);

public:
    RoomModel room;
};
