#include <crow.h>
#include "database.h"
#include "user.h"
#include "weapon.h"

namespace http {
    class Routing {
    public:
        void Run(server::GameDatabase& storage)
        {
            m_app.route_dynamic("/login")
                .methods("POST"_method)([this, &storage](const crow::request& req) {
                return this->LoginRoute(storage, req);
                    });
            m_app.port(18080).run();
        }

    private:
        crow::response LoginRoute(server::GameDatabase& storage, const crow::request& req) const
        {
            auto json = crow::json::load(req.body);
            if (!json)
            {
                return crow::response(400, "Invalid JSON data");
            }

            std::string username = json["username"].s();
            std::string password = json["password"].s();

            try
            {
                user::User user = storage.GetUserByUsername(username);

                /*if (user.GetPassword() == password) 
                {
                    return crow::response(200, "Login successful");
                }
                else
                {
                    return crow::response(401, "Invalid username or password");
                }*/
            }
            catch (const std::exception& e)
            {
                return crow::response(404, "User not found");
            }
        }

    private:
        crow::SimpleApp m_app;
    };
}
