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
void HttpManager::sendShootRequest(const QString& playerID, int bulletDirection, ResponseCallback callback) {
    QString shootData = QString("{\"playerID\":\"%1\", \"bulletDirection\": %2}").arg(playerID).arg(bulletDirection);

    // Log the player ID and bullet direction
    std::cout << "Sending shoot request: playerID = " << playerID.toStdString()
        << ", bulletDirection = " << bulletDirection << std::endl;

    cpr::Response response = cpr::Post(
        cpr::Url{ "http://localhost:18080/shoot" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ shootData.toStdString() }
    );

    if (response.status_code == 200) {
        std::cout << "Shoot request successful!\n";
    }
    else {
        std::cout << "Shoot request failed with status code: " << response.status_code << '\n';
    }

    if (callback) {
        callback(response);
    }
}
