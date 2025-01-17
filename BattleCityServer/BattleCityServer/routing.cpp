#include "Routing.h"
#include "Map.h"
#include "Player.h"
#include "powerup.h"

using std::uint32_t;

static std::string EntityToValue(std::shared_ptr<Entity> entity)
{
    if (entity == nullptr)
    {
        return "nothing";
    }
    if (auto player = std::dynamic_pointer_cast<game::Player>(entity); player)
    {
        return std::to_string(player->GetID());
    }
    if (auto bullet = std::dynamic_pointer_cast<game::Bullet>(entity); bullet)
    {
        return "bullet";
    }
    if (auto bomb = std::dynamic_pointer_cast<Bomb>(entity); bomb)
    {
        return "bomb";
    }
    if (auto powerUp = std::dynamic_pointer_cast<game::PowerUp>(entity); powerUp)
    {
        switch (powerUp->GetType())
        {
        case game::PowerUpType::BeerEffect: return "beer";
        case game::PowerUpType::TracingBullet: return "tracing";
        case game::PowerUpType::GhostBullet: return "ghost";
        case game::PowerUpType::MiniBombBullet: return "explosive";
        case game::PowerUpType::Invisibility: return "invisible";
        }
    }

    throw std::exception{ "Non-game component received" };
}

static Direction ConfigureDirection(std::shared_ptr<Entity> entity)
{
    if (auto player = std::dynamic_pointer_cast<game::Player>(entity); player)
    {
        return player->GetDirection();
    }
    if (auto bullet = std::dynamic_pointer_cast<game::Bullet>(entity); bullet)
    {
        return bullet->GetDirection();
    }
    return Direction::NONE;
}

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
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();
        int userId = gameDatabase.ValidateUserCredentials(username, password);

        if (userId != -1) {
            crow::json::wvalue responseJson;
            responseJson["status"] = "Login successful";
            responseJson["userId"] = userId;

            return crow::response{ responseJson };
        }
        else {
            return crow::response(401, "Invalid credentials");
        }
        });


    CROW_ROUTE(m_app, "/map").methods(crow::HTTPMethod::GET)([&map](const crow::request& req)
        {
            auto body = crow::json::load(req.body);
            std::vector<crow::json::wvalue> mapLayout;

            auto checkInfo = [&mapLayout](const game::Map::Square& square) -> void
                {
                    mapLayout.push_back(crow::json::wvalue{
                        {"tile", static_cast<int>(square.first.GetType())},
                        {"entity", EntityToValue(square.second)},
                        {"direction", static_cast<int>(ConfigureDirection(square.second))}
                        });
                };

            std::ranges::for_each(map.GetSquares(), checkInfo);

            return crow::json::wvalue{
                {"width", map.GetWidth()},
                {"height", map.GetHeight()},
                {"layout", mapLayout}
            };

        });

    CROW_ROUTE(m_app, "/move").methods(crow::HTTPMethod::POST)([&map](const crow::request& req) {
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
            std::cout<< directionStr;
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