#pragma once

#include "RoomModel.h"
#include "RoomService.h"

class RoomState {
public:
    static RoomState &instance(){
        static RoomState roomState;
        return roomState;
    }

    RoomModel &getRoom(){ return room;}

    bool isOpponentJoined();

    void createRoom(std::string creator_id);
    void joinRoom(std::string roomId,std::string uid);
    void deleteRoom();

private:
    RoomState(){}
    RoomModel room;
};
