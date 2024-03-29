#include "RoomState.h"
#include "GameException.h"

void RoomState::createRoom(PlayerModel &creator) {
    m_isMeP1 = true;
    for (int row = 0; row < 2; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "2U";

    for (int row = 2; row < ROWS-2; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "";

    for (int row = ROWS - 2; row < ROWS; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "1U";

    room.creator_uid = creator.m_uid;
    room.player2_uid = "";
    room.turn = P1;
    room.enemyLastMove = "";
    room.loggedOut = false;
    room.emoji = NonEmoji_t;
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
    if (room.player2_uid == "")
        HttpRequestsManager::instance().deleteRequest(BASE_URL + "/available_rooms/" + room.roomId + ".json");
    if (m_isMeP1)
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
    else room.board[ROWS - loc.row - 1][BOARD_SIZE - loc.col - 1] = str;
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
    if(tmpRoom.enemyLastMove.starts_with("Logout")){
        return std::make_pair(Location(-2,-2),Location(-2,-2));
    }
    std::string flagStr = m_isMeP1 ? "2F" : "1F";
    std::string holeStr = m_isMeP1 ? "2H" : "1H";
    Location flag, hole;

    Location location;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            location = m_isMeP1 ? Location(i, j) : Location(ROWS - i - 1, BOARD_SIZE - j - 1);
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
    if(room.loggedOut)
        throw GameException("User has been logged out");
    return room.turn;
}

void RoomState::uploadFlagAndHole() {
    int row1 = m_isMeP1 ? ROWS - 1 : 0;
    int row2 = m_isMeP1 ? ROWS - 2 : 1;
    RoomService::setFlagAndHole(room, row1, row2);
}


void RoomState::setLastMove(std::string warriorId, Location location, std::string weapon) {
    std::string move = warriorId + " ";

    if (m_isMeP1)
        move += std::to_string(location.row) + "," + std::to_string(location.col);
    else
        move += std::to_string(ROWS - location.row - 1) + "," +
                std::to_string(BOARD_SIZE - location.col - 1);

    move += " , " + weapon;
    room.enemyLastMove = move;
}

void RoomState::setLastMoveTie(std::string last_move, Location location, std::string id) {
    std::string move = last_move + " ";
    move += id;
    if (m_isMeP1)
        move += std::to_string(location.row) + "," + std::to_string(location.col);
    else
        move += std::to_string(ROWS - location.row - 1) + "," +
                std::to_string(BOARD_SIZE - location.col - 1);

    room.enemyLastMove = move;
}

void RoomState::setLastMoveMsg(std::string last_move) {
    room.enemyLastMove = last_move;
}

void RoomState::wantToRematch(bool rematch) {
    RoomService::updateRematch(room.roomId, rematch ? "1" : "0", !m_isMeP1);
}

int RoomState::isOpponentWantsToRematch() {
    auto tmpRoom = RoomService::getRoom(room.roomId);
    if (m_isMeP1) {
        if (tmpRoom.board[0][1].size() != 1)
            return 2;
        return tmpRoom.board[0][1] == "1";
    } else {
        if (tmpRoom.board[0][0].size() != 1)
            return 2;
        return tmpRoom.board[0][0] == "1";
    }
}

void RoomState::resetRoom() {
    for (int row = 0; row < 2; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "2U";

    for (int row = ROWS - 2; row < ROWS; row++)
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "1U";

    for (int row = 2; row < ROWS - 2; row++) {
        for (int i = 0; i < BOARD_SIZE; i++)
            room.board[row][i] = "";
    }
    room.board[0][0] = "1";
    room.turn = P1;
    room.enemyLastMove = "";
    upload();
}

bool RoomState::isRoomReset() {
    room = RoomService::getRoom(room.roomId);
    return room.board[0][0] == "1";
}

bool RoomState::isLoggedOut() {
    return room.loggedOut;
}

void RoomState::logout(){
    room.loggedOut = true;
    RoomService::logout(room.roomId);
}
