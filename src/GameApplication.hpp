#ifndef _GAME_APPLICATION_HPP_
#define _GAME_APPLICATION_HPP_

#include "consts.h"
#include "Game.hpp"
#include "GhostCamera.hpp"
#include <cstdlib>
#include <iostream>
#include <stein/Application.hpp>
//#include <stein/Object.hpp>
#include <stein/Tools.hpp>
//#include <stein/Builders.hpp>
//#include <stein/math/StreamUtils.h>
//#include <vector>


class GameApplication : public stein::Application {
private :
	Game * m_game;
	double * m_volumes;
	GhostCamera m_ghostCamera;
	bool m_bInGame;
	bool m_bGhostMode;
	bool m_bInPause;
	
public :
	GameApplication(); // create player 
	~GameApplication();
	void pause(); 	// pause the game
	void resume(); 	// resume the game
	void startGame();
	void exitGame();
	// At each frame
	virtual void animate();
	// On event
	virtual void handleKeyEvent(const SDL_keysym& keysym, bool down);
	
	// Menu
	void displayHighscore();
	void displayOptions();
	void setVolume(unsigned int type = VOLUME_SOUND, double volume = .5);
	void displayCredits();
	void displayControls();
};

#endif // _GAME_APPLICATION_HPP_
