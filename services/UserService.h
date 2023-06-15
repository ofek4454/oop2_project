#pragma once

#if WIN32
#pragma warning(push)
#pragma warning(disable: 28020)
#endif
#include "nlohmann/json.hpp"
#if WIN32
#pragma warning(pop)
#endif
#include "env.h"
#include "iostream"
#include "PlayerModel.h"
#include "Consts.h"

using json = nlohmann::json;

namespace UserService{
    PlayerModel createUser(const std::string &uid);
    PlayerModel getUser(const std::string &uid);
    json deleteUser(const std::string &uid);
};