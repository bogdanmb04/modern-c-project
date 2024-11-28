#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <conio.h>

#include "map.h"
#include "routing.h"
#include "database.h"
#include "../Logging/logging.h"


int main() {
    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    std::ofstream of("syslog.log", std::ios::app);
    Logger logger(of);
    logger.Log("Started Application...", Logger::Level::Info);

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);
    myMap.PlacePlayer();
    std::cout << myMap;

    std::shared_ptr player = std::make_shared<Player>();
    myMap.InsertPlayer(player);

    myMap.MovePlayer(player->GetID(), Direction::DOWN);
    std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;

    std::cout << myMap;

   /* bool running = true;
    while (running)
    {
        if (_kbhit()) 
        {
            int ch = _getch();
            switch (ch) 
            {
            case 'w':
                myMap.MovePlayer(player->GetID(), Direction::UP);
                std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;
                break;
            case 's':
                myMap.MovePlayer(player->GetID(), Direction::DOWN);
                std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;
                break;
            case 'a':
                myMap.MovePlayer(player->GetID(), Direction::LEFT);
                std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;
                break;
            case 'd':
                myMap.MovePlayer(player->GetID(), Direction::RIGHT);
                std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;
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
	routing.Run(gameDatabase);

    return 0;
}
