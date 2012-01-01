#ifndef _GAME_APPLICATION_HPP_
#define _GAME_APPLICATION_HPP_

#include "consts.h"
#include "Game.hpp"
#include <stein/Application.hpp>

// @TODO : rm !
// forward declaration
//class Game;

class GameApplication : public stein::Application {
private :
	Game m_game;
	float * m_volumes;
	
public :
	const static GLfloat GHOST_CAMERA_HEIGHT = 0.1;
	const static size_t WIDTH = 800;
	const static size_t HEIGHT = 600;
	
	GameApplication();
	virtual ~GameApplication();
	virtual void animate();	// At each frame
	virtual void handleKeyEvent(const SDL_keysym& keysym, bool down);	// On event
	
	// Menus
	void displayHighscore();
	void displayOptions();
	void setVolume(size_t type = VOLUME_SOUND, double volume = .5);
	void displayCredits();
	void displayControls();
};

#endif // _GAME_APPLICATION_HPP_
