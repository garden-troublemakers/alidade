#include "Game.hpp"

using namespace std;

Game::Game(const Application * const app): application(app), player(), mirrors(NULL) {
	
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

bool Game::load(Level level) {
	if (level == EASY) {
		_buildLevelEasy();
	} else if (level == HARD) {
		_buildLevelHard();
	}
	// ok ?
	return 0;
}

void Game::_buildLevelEasy() {
	// Example : Adding one mirror
	mirrors = new Mirror[1](&(application->pScene)); 
}

void Game::_buildLevelHard() {

}
