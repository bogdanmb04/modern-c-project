#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <conio.h>

#include "Map.h"
#include "Routing.h"
#include "Database.h"
#include "../Logging/logging.h"
#include "Game.h"

int main() {
    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    game::Game::kGameCounter = 1;

    std::ofstream of("syslog.log", std::ios::app);
    Logger logger(of);
    logger.Log("Started Application...", Logger::Level::Info);

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);
    logger.Log("Map initialized with bombs and player placed.", Logger::Level::Info);
    logger.Log(myMap.ToString(), Logger::Level::Info);

    auto bogdan = gameDatabase.GetUserByUsername(std::string{"bogdan"});
    auto weapon = gameDatabase.GetWeapon(bogdan.GetID());

    game::Player playerBogdan{ std::forward<User>(bogdan), std::forward<Weapon>(weapon) };

    std::shared_ptr<game::Player> player = std::make_shared<game::Player>(playerBogdan);

    //myMap.InsertPlayer(player);
    //myMap.PlacePlayers();
    //player->SetDirection(Direction::RIGHT);
    //myMap.ShootBullet(player->GetID());

    //std::cout << myMap;

    //logger.Log("Player moved to position: " + std::to_string(player->GetPosition().first) + " " + std::to_string(player->GetPosition().second), Logger::Level::Info);
    //logger.Log(myMap.ToString(), Logger::Level::Info);

    /*bool running = true;
    while (running)
    {
        if (_kbhit())
        {
            int ch = _getch();
            switch (ch)
            {
            case 'w':
                myMap.MovePlayer(player->GetID(), Direction::UP);
                logger.Log("Player moved UP to position: " + std::to_string(player->GetPosition().first) + " " + std::to_string(player->GetPosition().second), Logger::Level::Info);
                logger.Log(myMap.ToString(), Logger::Level::Info);
                break;
            case 's':
                myMap.MovePlayer(player->GetID(), Direction::DOWN);
                logger.Log("Player moved DOWN to position: " + std::to_string(player->GetPosition().first) + " " + std::to_string(player->GetPosition().second), Logger::Level::Info);
                logger.Log(myMap.ToString(), Logger::Level::Info);
                break;
            case 'a':
                myMap.MovePlayer(player->GetID(), Direction::LEFT);
                logger.Log("Player moved LEFT to position: " + std::to_string(player->GetPosition().first) + " " + std::to_string(player->GetPosition().second), Logger::Level::Info);
                logger.Log(myMap.ToString(), Logger::Level::Info);
                break;
            case 'd':
                myMap.MovePlayer(player->GetID(), Direction::RIGHT);
                logger.Log("Player moved RIGHT to position: " + std::to_string(player->GetPosition().first) + " " + std::to_string(player->GetPosition().second), Logger::Level::Info);
                logger.Log(myMap.ToString(), Logger::Level::Info);
                break;
            case 'q':
                running = false;
                break;
            default:
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }*/

    http::Routing routing;
    routing.Run(gameDatabase, myMap);
    of.close();

    return 0;
}
