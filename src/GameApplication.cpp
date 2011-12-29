#include "GameApplication.hpp"

using namespace std;
using namespace stein;

static inline float frand() {
    return float(rand()) / RAND_MAX;
}

GameApplication::GameApplication() :
	Application(800, 600), m_game(this), m_ghostCamera(GHOST_CAMERA_HEIGHT, this), m_volumes(), m_bInGame(false), m_bGhostMode(false), m_bInPause(false) {
	// Init volumes at 80 percents each
	for(size_t i = 0; i < 3 ; ++i)
		m_volumes[i] = 0.8;
    
    // @TODO : build menu in sdl.
    
	// Default game
    startGame(); // for test purpose only, make a game by default
}

GameApplication::~GameApplication() {
	//delete [] m_volumes;
}

//
void GameApplication::startGame() {
	// init level configuration
	/*
	m_game.init / m_game.load ...
	*/
	
	// init camera and shaders
	
    //const float size = .06;
    // @TODO : Don't forget to init player's camera
    // We set the actual camera to be the player's one (fps mode)
    //m_Scene.camera = &(m_game.player.camera);
    /* ... like that
    setPerspectiveProjection(-size, size, -size, size, .1, 100);
    m_Scene.camera.setPosition(Vector3f(0, 0, 55));
    */
    // Shader
    m_Scene.setDefaultShaderID(loadProgram("../shaders/simpleShader.glsl"));
    
	// prepare level using xml.
	// build objects from xml
	// add 'em to the scene
	/* ... like that
	Object &object = m_Scene.createObject(GL_TRIANGLES);
    buildSquare(object);
    for (size_t i = 0; i < m_Simulation.boids().size(); ++i) {
        m_Scene.addObjectToDraw(object.id);
        m_Scene.setDrawnObjectColor(i, Color(frand(), frand(), frand()));
    }*/
	// m_bInGame = true; // go
}

// @TODO :
void GameApplication::exitGame() {
	m_bInGame = false;
}

void GameApplication::animate() {
	if(m_bInGame) {
		if(!m_bInPause) {
			// Should be use for moving nothing, the player or the ghostCamera with the same function.
			// @TODO : Init with the correct pointer (or reference !)
			// CF : animate()
			MoveableCamera* moveable = m_bGhostMode ? &m_ghostCamera : &(m_game.player);
			moveable->move();
			/*
			// @FIXME : Check this harder (no levelStatus)
			switch(levelStatus) {
				case LEVEL_FINISHED :
					m_bInGame = false;
					if(m_game.player.level != LEVEL_MAX) {
						++(m_game.player.level);
					} else {
						// GAME OVER ! // EXIT APP
					}
				break;
				case LEVEL_FAILED :
					// Reinit da player in the beginning
					//m_level->initPlayer(m_player);
				break;
				default :
					// @TODO : write end level conditions
					if(m_game.player.getLife() == 0)
						return LEVEL_FAILED;
					//else if(m_game.player.pos == m_conf.endPos) // something like that
					//	return LEVEL_FINISHED;
					// else
					m_game.player.move();
					return LEVEL_PLAYING;
					// You see what i did there ?
				break;
			}*/
		}
		else {
			// in game in pause
			// display pause menu
		}
	} else {
		// !in game, display game menu
	}
	// Si pause rien,
	// Sinon
	// Déplacement
		// Caméra
	// Collisions
}

// Distributes task for the "key" kind of events 
// For example : cout when b key is pressed
// down is true when the key is pressed, false when released
void GameApplication::handleKeyEvent(const SDL_keysym& keysym, bool down) {
	// @FIXME : Maybe we should call the parent's function (then privatize Application::m_bRunning again, and redefine correctly the initialisation's order in constructor Application::Application() ). Then we don't have to rewrite the whole switch. Maybe this is what causes awkwardly slow treatment when a key is pushed. Don't know how.
	Direction to = NOWHERE;
	if (down) {
		// CF : animate()
		if(m_bInGame) {
			// Should be use for moving nothing, the player or the ghostCamera with the same function.
			MoveableCamera* pMoveable = m_bGhostMode ? &m_ghostCamera : &(m_game.player);
			if(keysym.sym == SDLK_ESCAPE) {
				if(m_bInPause) {
					// pause();
				} else {
					// resume();
				}
			}
			else if(keysym.sym == SDLK_p)
				m_bInPause = !m_bInPause;
			else if(!!pMoveable) {
				switch(keysym.sym) {
					case SDLK_z :
					case SDLK_UP :
						to = UP; 	break;
					case SDLK_s :
					case SDLK_DOWN :
						to = DOWN; 	break;
					case SDLK_q :
					case SDLK_LEFT :
						to = LEFT; 	break;
					case SDLK_d :
					case SDLK_RIGHT :
						to = RIGHT;	break;
					default : break;
				}
				if(to != NOWHERE)
					pMoveable->setMovement(to, true);
			}
		}
		else
			Application::handleKeyEvent(keysym, down);
	}
	// on key release
	else if(m_bInGame && !m_bInPause) {
		MoveableCamera* pMoveable = m_bGhostMode ? &m_ghostCamera : &(m_game.player);
		if(!!pMoveable) {
			switch(keysym.sym) {
				case SDLK_z :
				case SDLK_UP :
					to = UP; 	break;
				case SDLK_s :
				case SDLK_DOWN :
					to = DOWN; 	break;
				case SDLK_q :
				case SDLK_LEFT :
					to = LEFT; 	break;
				case SDLK_d :
				case SDLK_RIGHT :
					to = RIGHT;	break;
				default : break;
			}
			if(to != NOWHERE)
				pMoveable->setMovement(to, false);
		}
	}
	// @TODO : Add handler for key up (else)
}


void GameApplication::setVolume(size_t type, double volume) {
	m_volumes[type] = volume;
}

// SDL
void GameApplication::displayHighscore() {}
void GameApplication::displayOptions() {}
void GameApplication::displayCredits() {}
void GameApplication::displayControls() {}

