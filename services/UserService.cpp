
#include "UserService.h"

namespace UserService{

    PlayerModel createUser(const std::string &name) {
        json body;
        body["name"] = name;

        auto response = HttpRequestsManager::instance().postRequest(body, BASE_URL + "/users.json");
        std::string uid = response["name"];
        return PlayerModel{name, uid};
    }

    PlayerModel getUser(const std::string &uid) {
        std::string url = BASE_URL + "/users/" + uid + ".json";

        auto response = HttpRequestsManager::instance().getRequest(url);
        if(response == nullptr)
            throw std::invalid_argument("No user found with the given id");
        return PlayerModel{response["name"], uid};

//        try{
//
//
//        } catch(HttpException &e) {
//            std::cerr << e.what() << std::endl;
//            throw;
//        } catch (json::exception &e) {
//            std::cerr << e.what() << std::endl;
//            throw;
//        }catch (...){
//            std::cerr << "Unknown exception was caught!" << std::endl;
//        }
    }

    json deleteUser(const std::string &uid) {
        std::string url = BASE_URL + "/users/" + uid + ".json";

        auto response = HttpRequestsManager::instance().deleteRequest(url);
        return response;
    }
}