#pragma once

#include <crow.h>
#include "database.h"

namespace http 
{
    class Routing 
    {
    public:
        void Run(server::GameDatabase& gameDatabase);

    private:
        crow::SimpleApp m_app;
    };
}