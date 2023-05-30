//
// Created by Ofek Gorgi on 30/05/2023.
//

#include "UserService.h"

namespace UserService{
    size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s){
        s->append(static_cast<char *>(ptr), size*nmemb);
        return size*nmemb;
    }

    PlayerModel UserService::createUser(std::string name) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/users.json";

        json body;
        body["name"] = name;
        std::string s;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.dump().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json response = json::parse(s.c_str());

        std::string uid = response["name"];

        return PlayerModel(name, uid);
    }

    PlayerModel UserService::getUser(std::string uid) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/users/" + uid + ".json";
        std::string s;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json response = json::parse(s.c_str());

        return PlayerModel(response["name"], uid);
    }

    json UserService::deleteUser(std::string uid) {
        CURL *curl = curl_easy_init();
        std::string url = BASE_URL + "/users/" + uid + ".json";
        std::string s;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json response = json::parse(s.c_str());
    }
}