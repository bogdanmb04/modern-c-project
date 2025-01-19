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
#include "../PasswordEncryption/passwordEncryption.h"

int main() 
{
    std::ofstream of("syslog.log", std::ios::app);
    Logger logger(of);

    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    game::Game::kGameCounter = 1;

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);
    //logger.Log("Map initialized with bombs and player placed.", Logger::Level::Info);

    //auto test = gameDatabase.GetUserByUsername(std::string{"bogdan"});
    //auto weapon = gameDatabase.GetWeapon(test.GetID());

    //game::Player playerTest{ test, std::move(weapon)};

    //std::shared_ptr<game::Player> player = std::make_shared<game::Player>(playerTest);

    //std::cout << myMap << std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds{ 5 });

    //myMap.InsertPlayer(player);
    //myMap.PlacePlayers();
    //player->SetDirection(Direction::RIGHT);
    //std::cout << myMap;
    //std::system("cls");
    //myMap.ShootBullet(player->GetID());
    //std::system("cls");
    //std::cout << myMap;

    //while (true)
    //{
    //    std::this_thread::sleep_for(std::chrono::seconds{ 3 });
    //    myMap.MoveBullets();
    //    std::system("cls");
    //    std::cout << myMap << std::endl;
    //    //std::this_thread::sleep_for(std::chrono::seconds{ 5 });
    //}

    http::Routing routing;
    routing.Run(gameDatabase, myMap);
    return 0;
}
