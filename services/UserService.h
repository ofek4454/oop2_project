#pragma once

#include <nlohmann/json.hpp>
#include "env.h"
#include "iostream"
#include "curl/curl.h"
#include "PlayerModel.h"
#include "Consts.h"

using json = nlohmann::json;

namespace UserService{
    PlayerModel createUser(std::string name);
    PlayerModel getUser(std::string uid);
    json deleteUser(std::string uid);
};