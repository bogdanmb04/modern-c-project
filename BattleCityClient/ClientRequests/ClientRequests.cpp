#include "ClientRequests.h"
#include <cpr/cpr.h>  // Biblioteca cpr pentru cereri HTTP
#include <iostream>    // Pentru std::cout

void ClientRequests::sendRequest(const std::string& url) {
    cpr::Response r = cpr::Get(cpr::Url{url});
    if (r.status_code == 200) {
        // Procesare răspuns valid
        std::cout << "Request successful!" << std::endl;
    } else {
        // Erori
        std::cout << "Request failed!" << std::endl;
    }
}
void ClientRequests::sendPostRequest(const std::string& url, const std::string& data) {
    cpr::Response r = cpr::Post(cpr::Url{url}, cpr::Body{data});
    if (r.status_code == 200) {
        std::cout << "POST request successful!" << std::endl;
    } else {
        std::cout << "POST request failed!" << std::endl;
    }
}
