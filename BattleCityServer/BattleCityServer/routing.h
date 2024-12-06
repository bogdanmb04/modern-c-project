#pragma once

#include <crow.h>
#include "database.h"
#include "map.h"

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