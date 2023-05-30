
#include "RoomService.h"

namespace RoomService {
    size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s){
        s->append(static_cast<char *>(ptr), size*nmemb);
        return size*nmemb;
    }

    nlohmann::json RoomService::createRoom(RoomModel room) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/rooms.json";
        std::string s;

        std::string body = room.toJson().dump();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json response = json::parse(s.c_str());

        return response;
    }

    json updateRoom(RoomModel room) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/rooms/" + room.getRoomId() + ".json";

        std::string body = room.toJson().dump();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

        CURLcode res = curl_easy_perform(curl);
        std::cout << res << std::endl;
        return json();
    }

    json deleteRoom(std::string roomId) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/rooms/" + roomId + ".json";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        CURLcode res = curl_easy_perform(curl);

        std::cout << res << std::endl;

        return json();
    }

    RoomModel RoomService::getRoom(std::string roomId) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/rooms/" + roomId + ".json";
        std::string s;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return RoomModel::fromJson(roomId, json::parse(s.c_str()));
    }
}