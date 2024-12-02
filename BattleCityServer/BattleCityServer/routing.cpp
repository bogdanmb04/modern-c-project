#include "routing.h"
#include "map.h"
#include "player.h"

void http::Routing::Run(server::GameDatabase& gameDatabase)
{
    CROW_ROUTE(m_app, "/")([]() {
        return "Welcome!";
        });

    CROW_ROUTE(m_app, "/login").methods(crow::HTTPMethod::POST)([&gameDatabase](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body)
        {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();

        if (gameDatabase.ValidateUserCredentials(username, password))
        {
            return crow::response(200, "Login successful");
        }
        else
        {
            return crow::response(401, "Invalid credentials");
        }
        });

    CROW_ROUTE(m_app, "/move").methods(crow::HTTPMethod::POST)([&gameDatabase](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body)
        {
            return crow::response(400, "Invalid JSON");
        }

        uint32_t playerID = body["playerID"].i();
        std::string directionStr = body["direction"].s();
        Direction direction;

        if (directionStr == "UP") {
            direction = Direction::UP;
        }
        else if (directionStr == "DOWN") {
            direction = Direction::DOWN;
        }
        else if (directionStr == "LEFT") {
            direction = Direction::LEFT;
        }
        else if (directionStr == "RIGHT") {
            direction = Direction::RIGHT;
        }
        else {
            return crow::response(400, "Invalid direction");
        }

        game::Map map;
        map.MovePlayer(playerID, direction);

        return crow::response(200, "Move successful");
        });

    m_app.port(18080).multithreaded().run();
}
