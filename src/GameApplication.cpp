#include "GameApplication.hpp"

using namespace std;
using namespace stein;

GameApplication::GameApplication() :
	Application(WIDTH, HEIGHT), m_game(&m_Scene), m_volumes(NULL) {
	// Init volumes at 80 percents each
	m_volumes = new float[3]();
	for(size_t i = 0; i < 3 ; ++i)
		m_volumes[i] = 0.8;

	SDL_ShowCursor(SDL_DISABLE); // Hide cursor
	SDL_WM_GrabInput(SDL_GRAB_ON); // Restrict cursor to the window
    
    // @TODO : build menu in sdl.
    
	// Default game
    m_game.start(); // for test purpose only, make a game by default
}

GameApplication::~GameApplication() {
	delete [] m_volumes;
}

void GameApplication::animate() {
	if(!m_game.isRunning())
		cerr << "NO GAME" << endl; // show sdl game menu
	else {
		if (m_game.inPause())
			cout << "IN PAUSE" << endl; // show sdl menu pause
		else
			m_game.update();
	}
}

// Distributes task for the "key" kind of events
// down is true when the key is pressed, false when released
void GameApplication::handleKeyEvent(const SDL_keysym& keysym, bool down) {
	if(keysym.sym == SDLK_ESCAPE) {
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << "Thank you for testing Alidade." << endl;
		cout << "Fork this game at" << endl << "https://github.com/garden-troublemakers/alidade" << endl;
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		Application::handleKeyEvent(keysym, down);	
	}
	if(m_game.isRunning() && keysym.sym != SDLK_f)
		m_game.handleKeyEvent(keysym, down);
	else
		Application::handleKeyEvent(keysym, down);
}

void GameApplication::handleEvent(const SDL_Event& event) {
    switch (event.type) {
        // User events
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
			handleMouseEvent(event.button);
           break;
        default:
			Application::handleEvent(event);
            break;
    }
}

void GameApplication::handleMouseEvent(const SDL_MouseButtonEvent & mEvent) {
	m_game.handleMouseEvent(mEvent);
}

void GameApplication::setVolume(size_t type, double volume) {
	m_volumes[type] = volume;
}

// SDL
void GameApplication::displayHighscore() {}
void GameApplication::displayOptions() {}
void GameApplication::displayCredits() {}
void GameApplication::displayControls() {}

