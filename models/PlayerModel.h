#pragma once

#include <string>
#include <nlohmann/json.hpp>

class PlayerModel{
public:
    PlayerModel(const std::string& name,const std::string& id) : m_name(name),m_uid(id){}

    static PlayerModel fromJson(std::string id, nlohmann::json data) {
        return PlayerModel(id,data);
    }

    std::string to_string(){
        std::string data = "uid: ";
        data += m_uid;
        data += " name: ";
        data += m_name;

        return data;

    }

    const std::string m_uid, m_name;

private:
    PlayerModel(std::string id, nlohmann::json data) : m_name(data["name"]), m_uid(id){}
};