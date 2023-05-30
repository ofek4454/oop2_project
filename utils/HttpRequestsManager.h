#pragma once

#include "Consts.h"
#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include "iostream"


class HttpRequestsManager {
public:
    static HttpRequestsManager &instance() {
        static HttpRequestsManager http_manager;
        return http_manager;
    }
    ~HttpRequestsManager(){
        curl_easy_cleanup(m_delete_curl);
        curl_easy_cleanup(m_post_curl);
        curl_easy_cleanup(m_put_curl);
        curl_easy_cleanup(m_get_curl);
    }
    bool postRequest(const json& data,std::string url);
    bool getRequest(json data,std::string url);
    bool putRequest(json data,std::string url);
    bool deleteRequest(std::string url);

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
    json m_body;
};


