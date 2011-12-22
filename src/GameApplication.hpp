#ifndef _GAME_APPLICATION_HPP_
#define _GAME_APPLICATION_HPP_

#include "consts.h"
#include "Game.hpp"
#include <stein/Application.hpp>
#include <stein/Object.hpp>
#include <stein/Tools.hpp>
#include <stein/Builders.hpp>
#include <stein/math/StreamUtils.h>
#include <iostream>
#include <vector>


class GameApplication : public stein::Application {
private :
	Game * m_game;
	unsigned char * m_volumes;
	Camera ghostCamera;
	bool m_bInGame;
	bool m_bGhostMode;
	bool m_bInPause;
	
public :
	GameApplication(); // create player 
	~GameApplication();
	void pause(); 	// pause the game
	void resume(); 	// resume the game
	void init(); 	// start the game from the beginning
	void startLevel(unsigned int level = LEVEL_TEST);
	// At each frame
	virtual void animate();
	// On event
	virtual void handleKeyEvent(const SDL_keysym& keysym, bool down);
	
	// Menu
	void displayHighscore();
	void displayOptions();
	void setVolume(unsigned int type = VOLUME_SOUND, unsigned char volume);
	void displayCredits();
	void displayControls();
	
	// @TODO : 
	void save(); 	// save the player
	void load(); 	// load a previous player
};

#endif // _GAME_APPLICATION_HPP_
