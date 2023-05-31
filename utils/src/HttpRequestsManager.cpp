#include "HttpRequestsManager.h"

json HttpRequestsManager::postRequest(const json& data, std::string url) {
    std::string response;
    std::string body = data.dump();
    curl_easy_setopt(m_post_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_post_curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(m_post_curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(m_post_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(m_post_curl, CURLOPT_WRITEDATA, &response);

    CURLcode res;
    res = curl_easy_perform(m_post_curl);
    if (res == CURLE_OK){
        return json::parse(response.c_str());
    }
    else;
    //TODO throw exception

    return NULL;
}

json HttpRequestsManager::getRequest(std::string url) {
    std::string response;
    curl_easy_setopt(m_get_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_get_curl, CURLOPT_HTTPGET, "GET");
    curl_easy_setopt(m_get_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(m_get_curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(m_get_curl);
    if(res == CURLE_OK){
        return json::parse(response);
    }
    else{
        // TODO throw exception
    }
    // TODO create pthread
    return NULL;

}

json HttpRequestsManager::deleteRequest(std::string url) {
    std::string response;
    curl_easy_setopt(m_delete_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_delete_curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(m_delete_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(m_delete_curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(m_delete_curl);
    if(res == CURLE_OK){
        return json::parse(response);
    }
    else{
        // TODO throw exception
    }
    return NULL;
}

json HttpRequestsManager::putRequest(const json& data, std::string url) {
    std::string response;
    std::string body = data.dump();

    curl_easy_setopt(m_put_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_put_curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(m_put_curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(m_put_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(m_put_curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(m_put_curl);
    if(res == CURLE_OK){
        return json::parse(response);
    }
    else{
        // TODO throw exception
    }
    return NULL;
}

size_t HttpRequestsManager::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response) {
    size_t totalSize = size * nmemb;
    response->append((char *) contents, totalSize);
    return totalSize;
}

HttpRequestsManager::~HttpRequestsManager() {
    curl_easy_cleanup(m_delete_curl);
    curl_easy_cleanup(m_post_curl);
    curl_easy_cleanup(m_put_curl);
    curl_easy_cleanup(m_get_curl);
}
