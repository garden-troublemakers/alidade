#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include "Geometry.hpp"
#include <stein/Application.hpp>
#include <tinyxml/tinyxml.h>
#include <tinyxml/tinystr.h>
#include <iostream>
#include <string>

enum ObjectType {
	PLAYER, VISIBLE_WALL, INVISIBLE_WALL, PORTALABLE_ZONE, ACTION_ZONE, MIRROR, DECOR
};

struct Obj : public stein::Object {
	string path;
	int block;
	ObjectType type;
	double posX, posY, posZ;
};

class Game {
private :
	bool m_bRunning;
	Player m_player;
	GameApplication * m_pGameApplication;
	unsigned int m_level;
	std::vector<Mirror> m_mirrors;
	std::list<stein::Object> m_lObjects;
	Portals m_portals;
	
	// score, time, bonus ...
public :
	Game(const stein::Application * const application);
	~Game();
	const std::list<stein::Object> objectsList() const;
	void loadLevel();
	bool save();
	bool load();
	bool isRunning();
	void handleClick(/*mousebutton ...*/);
	void start();
	void exit();
};

#endif // _GAME_HPP_
