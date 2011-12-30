#ifndef _GAME_APPLICATION_HPP_
#define _GAME_APPLICATION_HPP_

#include "consts.h"
#include "Game.hpp"
#include "MoveableCamera.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <tinyxml/tinyxml.h>
#include <tinyxml/tinystr.h>
#include <stein/Application.hpp>
#include <stein/Tools.hpp>
#include <stein/Object.hpp>
#include <stein/Builders.hpp>
//#include <stein/math/StreamUtils.h>
//#include <vector>

class GameApplication : public stein::Application {
private :
	Game m_game;
	MoveableCamera m_ghostCamera;
	double m_volumes[3];
	bool m_bInGame;
	bool m_bGhostMode;
	bool m_bInPause;
	
public :
	const static GLfloat GHOST_CAMERA_HEIGHT = 0.1;

	GameApplication();
	virtual ~GameApplication();
	void pause(); 	// pause the game
	void resume(); 	// resume the game
	/* Move in Game:
	void startGame();
	void loadLevel(Game & game);
	void exitGame();
	*/
	// At each frame
	virtual void animate();
	// On event
	virtual void handleKeyEvent(const SDL_keysym& keysym, bool down);
	
	// Menu
	void displayHighscore();
	void displayOptions();
	void setVolume(size_t type = VOLUME_SOUND, double volume = .5);
	void displayCredits();
	void displayControls();
};

#endif // _GAME_APPLICATION_HPP_
