#include "Game.hpp"

using namespace std;

Game::Game(): player() {
	
}

Game::Game(string path) {
	// xml = loadFromXML(path);
	//player = new Player(...);
	//level = xml.level_id
}

Game::~Game() {
	//delete [] player;
}

bool Game::save() {
	// make xml from values
	return 0; // SUCCESS ?
}
