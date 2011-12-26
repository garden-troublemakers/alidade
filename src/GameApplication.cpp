#include "GameApplication.hpp"

using namespace std;
using namespace stein;

static inline float frand() {
    return float(rand()) / RAND_MAX;
}

GameApplication::GameApplication() : Application(800, 600), m_ghostCamera() {
	m_bInGame = false;
	m_bGhostMode = false;
	m_bInPause = false;
	m_volumes = new double[3]();
	// Init volumes at 80 percents each
	for(size_t i = 0; i < 3 ; ++i)
		m_volumes[i] = 0.8;
	
    cout << "fu : " << m_volumes[0] << endl;
    
    // @TODO : build menu in sdl.
    // @TODO : load player
    
	// Default game
    startGame(); // for test purpose only, make a game by default
}

GameApplication::~GameApplication() {
	delete [] m_volumes;
	delete [] m_game;
}

//
void GameApplication::startGame() {
	// init level configuration
	if(m_game == NULL) {
		m_game = new Game();
	}
	
	// init camera and shaders
	
    //const float size = .06;
    // @TODO : Don't forget to init player's camera
    // We set the actual camera to be the player's one (fps mode)
    //m_Scene.camera = &(m_game->player.camera);
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
	m_bInGame = true; // go
}

// @TODO :
void GameApplication::exitGame() {
	m_bInGame = false;
}

void GameApplication::animate() {
	if(m_bInGame) {
		if(!m_bInPause) {
			if(!m_bGhostMode)
				m_game->player.move();
			else
				m_ghostCamera.move();
			/*
			// @TODO check this out, need a move() on Ghost Cam ?
			// @FIXME : Check this harder (no levelStatus)
			switch(levelStatus) {
				case LEVEL_FINISHED :
					m_bInGame = false;
					if(m_game->player.level != LEVEL_MAX) {
						++(m_game->player.level);
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
					if(m_game->player.getLife() == 0)
						return LEVEL_FAILED;
					//else if(m_game->player.pos == m_conf.endPos) // something like that
					//	return LEVEL_FINISHED;
					// else
					m_game->player.move();
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
    if (down) {
        switch (keysym.sym) {
            case SDLK_ESCAPE:
            	/*if(m_bInGame)
            		m_bInPause = !m_bInPause;
            	else*/
                //	m_bRunning = false;
                break;
            case SDLK_p :
            	if(m_bInGame)
            		m_bInPause = !m_bInPause;
            		
            case SDLK_f:
                Application::printFPS();
                break;
            case SDLK_g:
            	/*m_bGhostMode = !m_bGhostMode;
            	if(m_bGhostMode)
            		m_ghostCamera = m_game->player.camera;
            	m_scene.camera = (m_bGhostMode) ? m_ghostCamera : m_game->player.camera;*/
            case SDLK_z :
            case SDLK_q :
            case SDLK_s :
            case SDLK_d :
            	if(m_bInGame) {
            		if(!m_bInPause) {
            			if(!m_bGhostMode) {
            				/* @TODO :
   							setMovement appliquée à player, camera : update des variables de déplacements
   							appelées à chaque update de l'affichage d'un objet (dans animate ?)
   							*/
            				//m_game->player.setMovement(keysym.sym);
            				// move player
            			} else {
            				// move ghost Camera
            			}
            		}
            		else {
            			// move in pause menu
            		}
            	}
            default:
                break;
        }
    }
	// @TODO : Add handler for key up (else)
}


void GameApplication::setVolume(unsigned int type, double volume) {
	m_volumes[type] = volume;
}

// SDL
void GameApplication::displayHighscore() {}
void GameApplication::displayOptions() {}
void GameApplication::displayCredits() {}
void GameApplication::displayControls() {}
