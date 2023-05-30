#include <ctime>
#include <cstdlib>
#include "include/Menu.h"
#include "HttpRequestsManager.h"
#include "nlohmann/json.hpp"
#include "UserService.h"

int main(){
//    srand(time(NULL));
//    Menu menu;
    json data;
    data["name"] = "bar";
    data["score"] = "19";
    std::cout << HttpRequestsManager::instance().postRequest(data,BASE_URL);
    return 0;
}