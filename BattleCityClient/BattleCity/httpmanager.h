#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QString>
#include <functional>
#include <cpr/cpr.h>

using ResponseCallback = std::function<void(const cpr::Response&)>;

class HttpManager {
public:
    HttpManager();
    ~HttpManager();

    void sendGetRequest(const QString& url, ResponseCallback callback);
    void sendPostRequest(const QString& url, const QString& data, ResponseCallback callback);
    void sendShootRequest(const QString& playerID, int bulletDirection, ResponseCallback callback);

};

#endif
