#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "consts.h"
#include "Mirror.hpp"
#include "Obj.hpp"
#include "MoveableCamera.hpp"
#include "Player.hpp"
#include "Portals.hpp"
#include <SDL/SDL.h>
#include <stein/Scene.hpp>
#include <stein/Tools.hpp>
#include <tinyxml/tinyxml.h>
#include <tinyxml/tinystr.h>
#include <list>
#include <iostream>
#include <string>

enum Level {
	EASY, HARD
};

class Game {
private :
	stein::Scene* m_pScene;
	MoveableCamera m_ghostCamera;
	Player m_player;
	Level m_level;
	Portals m_portals;
	std::vector<Mirror> m_mirrors;
	std::list<Obj> m_lObjects;

	// boolean
	bool m_bRunning;
	bool m_bPause;
	bool m_bGhostMode;
	
public :
	Game(stein::Scene* pScene);
	~Game();
	void loadLevel();
	bool load(); // @TODO
	bool save(); // @TODO
	void start();
	void exit();
	void update();
	
	void handleKeyEvent(const SDL_keysym& keysym, bool down);
	
	inline const bool isRunning() const {
		return m_bRunning;
	}
	
	inline const bool inGhostMode() const {
		return m_bGhostMode;
	}
	
	inline const bool inPause() const {
		return m_bPause;
	}
	
	inline const std::list<Obj> objectsList() const {
		return m_lObjects;
	}
	
	void switchGhostMode();
	void switchPause();
};

#endif // _GAME_HPP_
