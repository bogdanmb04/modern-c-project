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

//GAME START 




    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    std::vector<game::Player> players;
    auto dbUsers = gameDatabase.GetAllUsers();

    game::Game::kGameCounter = 1;

    
    //logger.Log("Started Application...", Logger::Level::Info);

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);
    //logger.Log("Map initialized with bombs and player placed.", Logger::Level::Info);


    http::Routing routing;
    routing.Run(gameDatabase, myMap);
    return 0;
}
