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

int main() 
{
    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    game::Game::kGameCounter = 1;

    //std::ofstream of("syslog.log", std::ios::app);
    //Logger logger(of);
    //logger.Log("Started Application...", Logger::Level::Info);

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);
    //logger.Log("Map initialized with bombs and player placed.", Logger::Level::Info);

    auto test = gameDatabase.GetUserByUsername(std::string{"test"});
    auto weapon = gameDatabase.GetWeapon(test.GetID());

    game::Player playerBogdan{ test, std::move(weapon)};
    std::shared_ptr<game::Player> player = std::make_shared<game::Player>(playerBogdan);
    uint32_t id = 1;
    gameDatabase.AddTotalScore(1, 1000);
    gameDatabase.AddSpecialMoney(1, 1000);
    myMap.InsertPlayer(player);
    myMap.PlacePlayers();
    player->SetDirection(Direction::RIGHT);
    myMap.MovePlayer(id,Direction::RIGHT);
    //myMap.ShootBullet(player->GetID());

    http::Routing routing;
    routing.Run(gameDatabase, myMap);
    return 0;
}
