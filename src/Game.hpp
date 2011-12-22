#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstring>

// forward declaration
class Player;

struct Game {
	Player player;
	unsigned int level;
	// score, time, bonus ...
	
	Game();
	Game(string path);
	~Game();
	bool save();
};

#endif // _GAME_HPP_
