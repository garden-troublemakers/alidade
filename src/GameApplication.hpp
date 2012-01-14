#ifndef _GAME_APPLICATION_HPP_
#define _GAME_APPLICATION_HPP_

// @TODO : rm !
#include "consts.h"
#include "GameMenu.hpp"
#include "Game.hpp"
#include <stein/Application.hpp>

class GameApplication : public stein::Application {
private :
	Game m_game;
	float * m_volumes;
	GameMenu m_pause;
	
public :
	const static GLfloat GHOST_CAMERA_HEIGHT = 0.1;
	const static size_t WIDTH = 800;
	const static size_t HEIGHT = 600;
	
	GameApplication();
	virtual ~GameApplication();
	virtual void animate();	// At each frame
	virtual void handleKeyEvent(const SDL_keysym& keysym, bool down);	// On key event
	virtual void handleEvent(const SDL_Event& event); // on event
	virtual void handleMouseEvent(const SDL_MouseButtonEvent& mEvent); // on mouse event
	
	// Menus
	void displayHighscore();
	void displayOptions();
	void setVolume(size_t type = VOLUME_SOUND, double volume = .5);
	void displayCredits();
	void displayControls();
};

#endif // _GAME_APPLICATION_HPP_
