#pragma once

#include <string>
#if WIN32
#pragma warning(push)
#pragma warning(disable: 28020)
#endif
#include "nlohmann/json.hpp"
#if WIN32
#pragma warning(pop)
#endif
#include "SFML/Graphics.hpp"

class PlayerModel{
public:
    PlayerModel(const std::string& name = "name",const std::string& id = "id") : m_name(name),m_uid(id){}

    static PlayerModel fromJson(std::string id, nlohmann::json data) {
        return PlayerModel(id,data);
    }
    void setPicture(sf::Texture text){
        m_picture.setTexture(text);
    }

    std::string to_string(){
        std::string data = "uid: ";
        data += m_uid;
        data += " name: ";
        data += m_name;

        return data;

    }

    std::string m_uid, m_name;
    sf::Sprite m_picture;

private:
    PlayerModel(std::string id, nlohmann::json data) : m_name(data["name"]), m_uid(id){}
};