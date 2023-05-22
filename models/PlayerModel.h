#pragma once

#include <string>

class PlayerModel{
public:
    PlayerModel() : m_name("ofek"),m_uid("123456"){}
private:
    std::string m_uid, m_name;
};