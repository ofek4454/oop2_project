#include "HttpRequestsManager.h"

bool HttpRequestsManager::postRequest(const json& data, std::string url) {
    std::string requestBody = data.dump();
    curl_easy_setopt(m_post_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_post_curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(m_post_curl, CURLOPT_POSTFIELDS, requestBody.c_str());


    CURLcode res;
    res = curl_easy_perform(m_post_curl);
    if (res == CURLE_OK)
        return true;
    else
        return false;

}

bool HttpRequestsManager::getRequest(json data, std::string url) {
    return false;
}

bool HttpRequestsManager::deleteRequest(std::string url) {
    return false;
}

bool HttpRequestsManager::putRequest(json data, std::string url) {
    return false;
}
