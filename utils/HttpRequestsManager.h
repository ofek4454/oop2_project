#pragma once

#include "Consts.h"
#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include "iostream"

using json = nlohmann::json;


class HttpRequestsManager {
public:
    static HttpRequestsManager &instance() {
        static HttpRequestsManager http_manager;
        return http_manager;
    }
    ~HttpRequestsManager();
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response);
    json postRequest(const json& data,std::string url);
    json getRequest(std::string url);
    json putRequest(json data,std::string url);
    json deleteRequest(std::string url);

private:
    HttpRequestsManager(){
        m_delete_curl = curl_easy_init();
        m_get_curl = curl_easy_init();
        m_put_curl = curl_easy_init();
        m_post_curl = curl_easy_init();
    }
    CURL *m_post_curl;
    CURL *m_get_curl;
    CURL *m_put_curl;
    CURL *m_delete_curl;
    bool m_isDataRecieved;
};


