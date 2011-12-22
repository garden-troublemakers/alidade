#include "Game.hpp"

// forward declaration
class Player;

Game::Game() {
	player = new Player(...);
	
}

Game::Game(string path) {
	// xml = loadFromXML(path);
	//player = new Player(...);
	//level = xml.level_id
}

Game::~Game() {
	delete [] player;
}

bool Game::save() {
	// make xml from values
	return 0; // SUCCESS ?
}



#endif // _GAME_HPP_
