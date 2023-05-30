#include "RoomState.h"

void RoomState::createRoom(std::string creator_id) {
    for(int row=0 ; row<2 ; row++)
        for(int i = 0 ; i <BOARD_SIZE ; i++)
            room.board[row][i] = "2U";

    for(int row=BOARD_SIZE-2 ; row<BOARD_SIZE ; row++)
        for(int i = 0 ; i <BOARD_SIZE ; i++)
            room.board[row][i] = "1U";

    room.creator_uid = creator_id;

    auto response = RoomService::createRoom(room);
    room.roomId = response["name"];
}

void RoomState::joinRoom(std::string roomId, std::string uid){
    room = RoomService::getRoom(roomId);
    room.player2_uid = uid;
    RoomService::updateRoom(room);
}

void RoomState::deleteRoom() {
    RoomService::deleteRoom(room.roomId);
}

bool RoomState::isOpponentJoined(){
    auto tmpRoom = RoomService::getRoom(room.roomId);
    if(tmpRoom.player2_uid == "")
        return false;

    room.player2_uid = tmpRoom.player2_uid;
    return true;

}