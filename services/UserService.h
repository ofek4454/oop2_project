#pragma once

#include <nlohmann/json.hpp>
#include "env.h"
#include "iostream"
#include "curl/curl.h"
#include "PlayerModel.h"
#include "Consts.h"

using json = nlohmann::json;

namespace UserService{
    PlayerModel createUser(const std::string &uid);
    PlayerModel getUser(const std::string &uid);
    json deleteUser(const std::string &uid);
};