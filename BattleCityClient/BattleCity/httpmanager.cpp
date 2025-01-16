#include "HttpManager.h"
#include <iostream>

HttpManager::HttpManager() {}

HttpManager::~HttpManager() {}


void HttpManager::sendPostRequest(const QString& url, const QString& data, ResponseCallback callback) {
    cpr::Response response = cpr::Post(
        cpr::Url{ url.toStdString() },
        cpr::Body{ data.toStdString() }
    );

    if (response.status_code == 200 || response.status_code == 201) {
        std::cout << "POST request successful!\n";
    }
    else {
        std::cout << "POST request failed with status code: " << response.status_code << '\n';
    }

    if (callback) {
        callback(response);
    }
}

