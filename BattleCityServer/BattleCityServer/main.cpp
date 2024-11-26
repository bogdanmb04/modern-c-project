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
#include "routing.h"
#include "../Logging/logging.h"


int main() {
    server::GameDatabase gameDatabase;
    gameDatabase.Initialize();

    std::ofstream of("syslog.log", std::ios::app);
    Logger logger(of);
    logger.Log("Started Application...", Logger::Level::Info);

    std::cout << "Hello team!" << std::endl;

    game::Map myMap;
    std::vector<Bomb> bombs;
    myMap.PlaceBombsOnWalls(bombs);
    myMap.PlacePlayer();
    std::cout << myMap;

    Player player;

	//de-comment this to test the movement
	//RequestHandler requestHandler;

 //   bool running = true;
 //   while (running) {
 //       if (_kbhit()) {
 //           int ch = _getch();
 //           switch (ch) {
 //           case 'w':
 //               requestHandler.HandleMovementRequest(player, MovementRequest::MoveUp);
 //               break;
 //           case 's':
 //               requestHandler.HandleMovementRequest(player, MovementRequest::MoveDown);
 //               break;
 //           case 'a':
 //               requestHandler.HandleMovementRequest(player, MovementRequest::MoveLeft);
 //               break;
 //           case 'd':
 //               requestHandler.HandleMovementRequest(player, MovementRequest::MoveRight);
 //               break;
 //           case 'q':
 //               running = false;
 //               break;
 //           default:
 //               break;
 //           }
 //       }
 //       std::this_thread::sleep_for(std::chrono::milliseconds(100));
 //   }
  
  
  
    //http::Routing routing;
	//routing.Run(gameDatabase);

    return 0;
}
