#include "RoomState.h"

void RoomState::createRoom(PlayerModel &creator) {
    m_isMeP1 = true;
    for (int row = 0; row < 2; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "2U";

    for (int row = BOARD_SIZE - 2; row < BOARD_SIZE; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "1U";

    room.creator_uid = creator.m_uid;
    room.turn = P1;
    auto response = RoomService::createRoom(room, creator.m_name);
    room.roomId = response["name"];
}

void RoomState::joinRoom(std::string roomId, std::string uid) {
    m_isMeP1 = false;
    room = RoomService::getRoom(roomId);
    room.player2_uid = uid;
    RoomService::updateRoom(room);
    RoomService::deleteAvailableRoom(roomId);
}

void RoomState::deleteRoom() {
    RoomService::deleteRoom(room.roomId);
    if(room.player2_uid == "")
        HttpRequestsManager::instance().deleteRequest(BASE_URL + "/available_rooms/" + room.roomId + ".json");
    if(m_isMeP1)
        UserService::deleteUser(room.creator_uid);
    else
        UserService::deleteUser(room.player2_uid);
}

bool RoomState::isOpponentJoined() {
    auto tmpRoom = RoomService::getRoom(room.roomId);
    if (tmpRoom.player2_uid == "")
        return false;

    room.player2_uid = tmpRoom.player2_uid;
    HttpRequestsManager::instance().deleteRequest(BASE_URL + "/available_rooms/" + room.roomId + ".json");
    return true;
}

void RoomState::setBoardCell(Location loc, std::string str) {
    if (m_isMeP1) room.board[loc.row][loc.col] = str;
    else room.board[BOARD_SIZE - loc.row - 1][BOARD_SIZE - loc.col - 1] = str;
}

void RoomState::upload() {
    RoomService::updateRoom(room);
}

void RoomState::changeTurn() {
    room.turn = (Turn_t) !room.turn;
    upload();
}

std::pair<Location, Location> RoomState::getOpponentFlagAndHole() {
    auto tmpRoom = RoomService::getRoom(room.roomId);
    std::string flagStr = m_isMeP1 ? "2F" : "1F";
    std::string holeStr = m_isMeP1 ? "2H" : "1H";
    Location flag, hole;

    Location location;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            location = m_isMeP1 ? Location(i, j) : Location(BOARD_SIZE - i - 1, BOARD_SIZE - j - 1);
            if (tmpRoom.board[location.row][location.col] == flagStr)
                flag = Location(location.row, location.col);
            else if (tmpRoom.board[location.row][location.col] == holeStr)
                hole = Location(location.row, location.col);
        }
    }
    return std::make_pair(flag, hole);
}

Turn_t RoomState::getTurn() {
    room = RoomService::getRoom(room.roomId);
    return room.turn;
}

void RoomState::uploadFlagAndHole() {
    int row1 = m_isMeP1 ? BOARD_SIZE - 1 : 0;
    int row2 = m_isMeP1 ? BOARD_SIZE - 2 : 1;
    RoomService::setFlagAndHole(room, row1, row2);
}


void RoomState::setLastMove(Location oldLocation, Location newLocation, std::string weapon) {
    std::string move;

    if (m_isMeP1)
        move = std::to_string(oldLocation.row) + "," + std::to_string(oldLocation.col) + " to " +
               std::to_string(newLocation.row) + "," + std::to_string(newLocation.col);
    else
        move = std::to_string(BOARD_SIZE - oldLocation.row - 1) + "," +
               std::to_string(BOARD_SIZE - oldLocation.col - 1) + " to " +
               std::to_string(BOARD_SIZE - newLocation.row - 1) + "," +
               std::to_string(BOARD_SIZE - newLocation.col - 1);

    move += " , " + weapon;
    room.enemyLastMove = move;
}

void RoomState::setLastMove(std::string last_move){
    room.enemyLastMove = last_move;
}