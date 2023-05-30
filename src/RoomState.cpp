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
