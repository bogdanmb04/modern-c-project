#include "Routing.h"
#include "Map.h"
#include "Player.h"

void http::Routing::Run(server::GameDatabase& gameDatabase, game::Map& map)
{
    CROW_ROUTE(m_app, "/")([]() {
        return "Welcome to Battle City!";
        });

    CROW_ROUTE(m_app, "/register").methods(crow::HTTPMethod::POST)([&gameDatabase](const crow::request& req) {

        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();

        if (username.empty() || password.empty()) {
            return crow::response(400, "Username and password cannot be empty");
        }

        if (gameDatabase.UserExists(username)) {
            return crow::response(409, "User already exists");
        }

        bool registrationSuccess = gameDatabase.RegisterUser(username, password);
        if (registrationSuccess) {
            return crow::response(201, "User registered successfully");
        }
        else {
            return crow::response(500, "Failed to register user");
        }
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

    CROW_ROUTE(m_app, "/map").methods(crow::HTTPMethod::GET)([&map](const crow::request& req)
        {
            auto body = crow::json::load(req.body);
            std::vector<crow::json::wvalue> info;

            //very big dummy testing here to get a hang of json
            //will change it later so the whole layout gets ported over nicer than whatever you'll see here
            // http://localhost:18080/map
            info.push_back(crow::json::wvalue{
                {"width", map.GetWidth()},
                {"height", map.GetHeight()},
                {"tiles", map.GetTileLayout()},
                {"entities", map.GetEntityLayout()}
                });

            return crow::json::wvalue{ info };
        });

    CROW_ROUTE(m_app, "/move").methods(crow::HTTPMethod::POST)([&gameDatabase, &map](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body)
        {
            return crow::response(400, "Invalid JSON");
        }

        uint32_t playerID = body["playerID"].i();
        std::string directionStr = body["direction"].s();
        Direction direction{};
        try 
        {
            direction = StringToDirection(directionStr);
        }
        catch (const std::exception& e)
        {
            return crow::response(401, "Invalid move");
        }

        map.MovePlayer(playerID, direction);

        return crow::response(200, "Move successful");
        });

    m_app.port(18080).multithreaded().run();
}
