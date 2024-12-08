#pragma once

#include <crow.h>
#include "Database.h"
#include "Map.h"

namespace http 
{
    class Routing 
    {
    public:
        void Run(server::GameDatabase& gameDatabase, game::Map& map);

    private:
        crow::SimpleApp m_app;
    };
}