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

    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    game::Game::kGameCounter = 1;

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);

    http::Routing routing;
    routing.Run(gameDatabase, myMap);
    return 0;
}
