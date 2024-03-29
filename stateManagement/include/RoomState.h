#pragma once

#include "RoomModel.h"
#include "RoomService.h"
#include "Location.h"
#include "PlayerModel.h"
#include "UserService.h"

class RoomState {
public:
    static RoomState &instance(){
        static RoomState roomState;
        return roomState;
    }
    ~RoomState(){
        if(m_isMeP1)
            deleteRoom();
    }

    RoomState(const RoomState &other) = delete;
    RoomState operator=(const RoomState &other) = delete;

    RoomModel &getRoom(){ return room;}
    bool isOpponentJoined();
    int isOpponentWantsToRematch();
    std::pair<Location,Location> getOpponentFlagAndHole();

    void createRoom(PlayerModel &creator);
    void joinRoom(std::string roomId,std::string uid);
    void deleteRoom();
    void uploadFlagAndHole();
    void wantToRematch(bool isRematch);
    void upload();
    void changeTurn();
    void setBoardCell(Location loc , std::string str);
    Turn_t getTurn();
    void setLastMove(std::string warriorId, Location location, std::string weapon);
    void setLastMoveTie(std::string last_move , Location location,std::string id);
    void setLastMoveMsg(std::string last_move);
    void setLastEmoji(Emojis emoji) {room.emoji = emoji;}
    Emojis getLastEmoji() { return room.emoji;}
    void resetRoom();
    bool isRoomReset();
    bool isLoggedOut();
    void logout();
private:
    RoomState(){};
    RoomModel room;

    bool m_isMeP1 = false;
};
