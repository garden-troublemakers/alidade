#ifndef _GAME_HPP_
#define _GAME_HPP_
#define TIXML_USE_STL 1

#include "Geometry.hpp"
#include "Mirror.hpp"
#include "Obj.hpp"
#include "MoveableCamera.hpp"
#include "Player.hpp"
#include "Portals.hpp"
#include <SDL/SDL.h>
#include <stein/Scene.hpp>
#include <stein/Color.hpp>
#include <stein/Tools.hpp>
#include <tinyxml/tinyxml.h>
#include <tinyxml/tinystr.h>
#include <iostream>
#include <cstdio>
#include <memory>

enum Level {
	EASY, HARD
};

class Game {
private :
	stein::Scene* m_pScene;
	MoveableCamera m_ghostCamera;
	Portals m_portals;
	Level m_level;
	std::vector<Mirror*> m_pMirrors;
	std::list<Obj*> m_lObjects;
	std::vector<std::string> files;

	// boolean
	bool m_bRunning;
	bool m_bPause;
	bool m_bGhostMode;
	
	Player* m_pPlayer;
	
	GLuint shaderId;
	GLuint invisibleShaderId;
	
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
	void handleMouseEvent(const SDL_MouseButtonEvent& mEvent);
	void handleShootPortal(const bool & bRed);
	
	inline const bool isRunning() const {
		return m_bRunning;
	}
	
	inline const bool inGhostMode() const {
		return m_bGhostMode;
	}
	
	inline const bool inPause() const {
		return m_bPause;
	}
	
	inline const std::list<Obj*> objectsList() const {
		return m_lObjects;
	}
	
	void switchGhostMode();
	void switchPause();
};

#endif // _GAME_HPP_
