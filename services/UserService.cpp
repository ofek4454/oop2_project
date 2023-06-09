
#include "UserService.h"

namespace UserService{
    size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s){
        s->append(static_cast<char *>(ptr), size*nmemb);
        return size*nmemb;
    }

    PlayerModel UserService::createUser(std::string name) {
        json body;
        body["name"] = name;

        auto response = HttpRequestsManager::instance().postRequest(body,BASE_URL + "/users.json");

        std::string uid = response["name"];

        return PlayerModel(name, uid);
    }

    PlayerModel UserService::getUser(std::string uid) {
        std::string url = BASE_URL + "/users/" + uid + ".json";
        auto response = HttpRequestsManager::instance().getRequest(url);

        return PlayerModel(response["name"], uid);
    }

    json UserService::deleteUser(std::string uid) {
        std::string url = BASE_URL + "/users/" + uid + ".json";
        auto response = HttpRequestsManager::instance().deleteRequest(url);
        return response;
    }
}