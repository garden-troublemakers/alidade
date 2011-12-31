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

	SDL_ShowCursor(SDL_DISABLE); // Hide cursor
	SDL_WM_GrabInput(SDL_GRAB_ON); // Restrict cursor to the window
    
    // @TODO : build menu in sdl.
    
	// Default game
    startGame(); // for test purpose only, make a game by default
}

GameApplication::~GameApplication() {
	//delete [] m_volumes;
}

// @TODO : del
void GameApplication::startGame() {
	// init level configuration
	/*
	m_game.init / m_game.load ...
	*/
	
	// init camera and shaders
	
    //const float size = .06;
    // @TODO : Don't forget to init player's camera
    // We set the actual camera to be the player's one (fps mode)
    m_Scene.pCamera = & m_game.player;
    /* ... like that
    setPerspectiveProjection(-size, size, -size, size, .1, 100);
    m_Scene.camera.setPosition(Vector3f(0, 0, 55));
    */
    // Shader
    m_Scene.setDefaultShaderID(loadProgram("../shaders/simpleShader.glsl"));
    
	// prepare level using xml.
	// build objects from xml
	// add 'em to the scene
	// ... like that
	Object &object = m_Scene.createObject(GL_TRIANGLES);
    buildSquare(object);
    m_Scene.addObjectToDraw(object.id);

    Object &object2 = m_Scene.createObject(GL_TRIANGLES);
       buildSquare(object2);
       m_Scene.addObjectToDraw(object2.id);

       Vector3f tr(0, 0, 1);
       Vector3f rt(0, 1, 0);

       m_Scene.setDrawnObjectModel(object2.id, translation(tr) * rotation(90, rt));

       m_Scene.setDrawnObjectColor(1, Color(frand(), frand(), frand()));

    m_Scene.setDrawnObjectColor(0, Color(frand(), frand(), frand()));
    // Go
    game.start(); // @TODO
}

// @TODO : Enlever ça
void GameApplication::exitGame() {
	game.exit();
}

void GameApplication::animate() {
	if(m_bInGame) {
		if(!m_bInPause) {
			((MoveableCamera*) m_Scene.pCamera)->move();
			
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
	Direction to = NOWHERE;
	if(keysym.sym == SDLK_ESCAPE && down) {
		Application::handleKeyEvent(keysym, down);
		/*if(m_bInGame) {
			// pause();
		} else {
			// resume();
		}*/
	}
	if(m_bInGame) {
		if(keysym.sym == SDLK_g && down) {
			m_bGhostMode = !m_bGhostMode;
			m_Scene.pCamera = m_bGhostMode ? & m_ghostCamera : & m_game.player;
		} else if(keysym.sym == SDLK_p && down)
			m_bInPause = !m_bInPause;
		else if(!m_bInPause) {
			switch(keysym.sym) {
				case SDLK_z :
				case SDLK_UP :
					to = FORWARD; break;
				case SDLK_s :
				case SDLK_DOWN :
					to = BACKWARD; break;
				case SDLK_q :
				case SDLK_LEFT :
					to = LEFT; 	break;
				case SDLK_d :
				case SDLK_RIGHT :
					to = RIGHT;	break;
				default : break;
			}
			if(to != NOWHERE)
				((MoveableCamera*) m_Scene.pCamera)->setMovement(to, down);
		}
		else
			Application::handleKeyEvent(keysym, down);
	}
}


void GameApplication::setVolume(size_t type, double volume) {
	m_volumes[type] = volume;
}

// SDL
void GameApplication::displayHighscore() {}
void GameApplication::displayOptions() {}
void GameApplication::displayCredits() {}
void GameApplication::displayControls() {}

