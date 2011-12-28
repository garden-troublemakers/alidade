#include "Game.hpp"

using namespace std;

Game::Game(const stein::Application * const application): player(application) {
	
}

Game::~Game() {
	//delete [] player;
}

bool Game::save() {
	// make xml from values
	return 0; // SUCCESS ?
}

bool Game::load() {
	return 0;
}
