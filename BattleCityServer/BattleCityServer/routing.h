#pragma once

#include <crow.h>
#include "database.h"
#include "user.h"
#include "weapon.h"

namespace http {
    class Routing {
    public:
        void Run(server::GameDatabase& storage);

    private:
        crow::SimpleApp m_app;
    };
}