#pragma once

#include <string>

class PlayerModel{
public:
    PlayerModel(const std::string& name,const std::string& id) : m_name(name),m_uid(id){}
    const std::string m_uid, m_name;
};