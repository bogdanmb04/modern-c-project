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
