#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include <stein/Application.hpp>
#include <iostream>
#include <string>


struct Game {
	Player player;
	unsigned int level;
	// score, time, bonus ...
	
	Game(const stein::Application * const application);
	~Game();
	bool save();
	bool load();
};

#endif // _GAME_HPP_
