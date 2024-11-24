import <iostream>;
#include "map.h"
//#include "playermovement.h"
import <vector>;
#include "../Logging/logging.h"
#include <fstream>

//TODO: add namespace game for every class


int main()
{
	/*std::ofstream of("syslog.log", std::ios::app);
	Logger logger(of);
	logger.Log("Started Application...", Logger::Level::Info);*/

	std::cout << "Hello team!" << std::endl;
	
	game::Map myMap;
	std::cout << myMap;
	std::vector<Bomb> bombs;
	myMap.PlaceBombsOnWalls(bombs);

	//PlayerMovement player(5, 5);
	//player.DisplayBoard();

	

  

	return 0;
}