#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include <iostream>
#include <string>

struct Game {
	Player player;
	unsigned int level;
	// score, time, bonus ...
	
	Game();
	Game(std::string);
	~Game();
	bool save();
	bool load();
};

#endif // _GAME_HPP_
