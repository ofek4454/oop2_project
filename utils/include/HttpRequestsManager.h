#pragma once

#include "Consts.h"
#if WIN32
#pragma warning(push)
#pragma warning(disable: 6101 6054 6240 6239)
#endif
#include "curl/curl.h"
#if WIN32
#pragma warning(pop)
#endif
#if WIN32
#pragma warning(push)
#pragma warning(disable: 28020)
#endif
#include "nlohmann/json.hpp"
#if WIN32
#pragma warning(pop)
#endif
#include "iostream"
#include "HttpException.h"

using json = nlohmann::json;

class HttpRequestsManager {
public:
    static HttpRequestsManager &instance() {
        static HttpRequestsManager http_manager;
        return http_manager;
    }
    ~HttpRequestsManager();
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response);
    json postRequest(const json& data, std::string url);
    json getRequest(std::string url);
    json putRequest(const json& data, std::string url);
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


