#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include "Mirror.hpp"
#include <stein/Application.hpp>
#include <iostream>
#include <string>

enum Level {
	EASY = 0, HARD = 1
}
	
struct Game {
	Application* application;
	Player player;
	Mirror* mirrors;
	size_t nbMirrors;
	Level level;
	// score, time, bonus ...
	
	Game(const Application * const app);
	~Game();
	bool save();
	bool load(Level level);
	
private :
	void _buildLevelEasy();
	void _buildLevetHard();
};

#endif // _GAME_HPP_
