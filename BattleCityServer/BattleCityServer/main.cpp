import <iostream>;
#include "map.h"
//#include "playermovement.h"
import <vector>;
#include "../Logging/logging.h"
#include <fstream>

#include "database.h"
#include "routing.h"

//TODO: add namespace game for every class


int main()
{
	std::ofstream of("syslog.log", std::ios::app);
	Logger logger(of);
	logger.Log("Started Application...", Logger::Level::Info);

	/*server::Database db = server::CreateDatabase("test.db");  
	server::GameDatabase gameDb(db);  
	http::Routing routing;
	routing.Run(gameDb);*/

	std::cout << "Hello team!" << std::endl;
	
	game::Map myMap;
	std::vector<Bomb> bombs;
	myMap.PlaceBombsOnWalls(bombs);
	myMap.PlacePlayer();
	std::cout << myMap;


	//PlayerMovement player(5, 5);
	//player.DisplayBoard();

	

  

	return 0;
}