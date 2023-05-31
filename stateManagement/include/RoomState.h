#pragma once

#include "RoomModel.h"
#include "RoomService.h"
#include "Location.h"
#include "PlayerModel.h"

class RoomState {
public:
    static RoomState &instance(){
        static RoomState roomState;
        return roomState;
    }

    RoomModel &getRoom(){ return room;}
    bool isOpponentJoined();
    std::pair<Location,Location> getOpponentFlagAndHole();

    void createRoom(PlayerModel &creator);
    void joinRoom(std::string roomId,std::string uid);
    void deleteRoom();

    void upload();
    void changeTurn(Turn_t turn);
    void setBoardCell(Location loc , std::string str);

private:
    RoomState(){}
    RoomModel room;

    bool m_isMeP1;
};
