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
    ~RoomState() {deleteRoom();}

    RoomModel &getRoom(){ return room;}
    bool isOpponentJoined();
    std::pair<Location,Location> getOpponentFlagAndHole();

    void createRoom(PlayerModel &creator);
    void joinRoom(std::string roomId,std::string uid);
    void deleteRoom();
    void uploadFlagAndHole();

    void upload();
    void changeTurn();
    void setBoardCell(Location loc , std::string str);
    Turn_t getTurn();
    void setLastMove(Location oldLocation, Location newLocation, std::string weapon);

private:
    RoomState(){}
    RoomModel room;

    bool m_isMeP1;
};
