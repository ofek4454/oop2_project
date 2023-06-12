#pragma once

#include "string"
#include "array"
#include "vector"
#include "Consts.h"
#include "chrono"
#include <nlohmann/json.hpp>
#include "ostream"
#include "iostream"

using namespace nlohmann::literals;

class RoomModel{
    friend class RoomState;
public:
    RoomModel(){}
    static RoomModel fromJson(std::string id, nlohmann::json data) {
        return RoomModel{id, data};
    }

    nlohmann::json toJson(){
        nlohmann::json data;
        data["creator_uid"] = creator_uid;
        data["player2_uid"] = player2_uid;
        data["watchers_uids"] = watchers_uids;
        data["board"] = board;
        data["turn"] = int(turn);
        data["enemy_last_move"] = enemyLastMove;

        return data;
    }

    std::string to_string(){
        std::string str = "id: ";
        str += roomId;
        str += "\ncreator_uid: ";
        str += creator_uid;
        str += "\nplayer2_uid: ";
        str += player2_uid;
        str += "\nboard:\n";
        for(auto line : board){
            for (auto tmp: line){
                str += tmp;
                str += " ";
            }
            str+= "\n";
        }
        str += enemyLastMove;
        str += "\n";
        return str;
    }

    std::string getRoomId() const {return roomId;}
    std::string creatorUid() const {return creator_uid;}
    std::string player2Uid() const {return player2_uid;}
    std::array<std::string, BOARD_SIZE> getBoardRow(int row) const {return board[row];}
    std::string getLastMove() {return enemyLastMove;}

//    void rotateBoard(){
//        std::reverse(board.begin(),board.end());
//        for(auto &line : board){
//            std::reverse(line.begin(),line.end());
//        }
//    }

private:
    std::string roomId;
    std::string creator_uid;
    std::string player2_uid;
    std::vector<std::string> watchers_uids;
    std::array<std::array<std::string, BOARD_SIZE>,ROWS> board;
    Turn_t turn;
    std::string enemyLastMove = "";

    RoomModel(std::string id, nlohmann::json &data){
        roomId = id;
        creator_uid = data["creator_uid"];
        player2_uid = data["player2_uid"];
        if(data.contains("watchers_uids"))
            watchers_uids = data["watchers_uids"];
        board = data["board"];
        turn = Turn_t(data["turn"]);
        enemyLastMove = data["enemy_last_move"];
    }
};