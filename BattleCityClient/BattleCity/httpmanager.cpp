#include "HttpManager.h"
#include <iostream>

HttpManager::HttpManager() {}

HttpManager::~HttpManager() {}

void HttpManager::sendGetRequest(const QString& url, ResponseCallback callback) {
    cpr::Response response = cpr::Get(cpr::Url{ url.toStdString() });
    if (response.status_code == 200) {
        std::cout << "GET request successful!\n";
    }
    else {
        std::cout << "GET request failed with status code: " << response.status_code << '\n';
    }

    if (callback) {
        callback(response);
    }
}

