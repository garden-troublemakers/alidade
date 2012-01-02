#include "Obj.hpp"
#include "Game.hpp"

using namespace std;
using namespace stein;

Game::Game(Scene* pScene):
	m_pScene(pScene), m_ghostCamera(), m_player(),
	m_level(EASY), m_portals(), m_mirrors(), m_lObjects(),
	m_bRunning(false), m_bPause(false), m_bGhostMode(false)
{}

Game::~Game() {
	//delete [] player;
	/*list delete m_lObjects;*/
}

void Game::loadLevel() {
	list<Obj> objList;
	TiXmlDocument xmlDoc;
	TiXmlElement *elem;
	
	//Loading xml depending on level chosen
	if(m_level == EASY)
		xmlDoc = TiXmlDocument("../res/maps/tuto.xml");
	else if(m_level == HARD)
		xmlDoc = TiXmlDocument("../res/maps/ez.xml");
		
	if(!xmlDoc.LoadFile()) {
		cerr << "loading error" << endl;
		cerr << "error #" << xmlDoc.ErrorId() << " : " << xmlDoc.ErrorDesc() << endl;
	}
	else {
		//Parsing the xml document
		TiXmlHandle hdl(&xmlDoc);
		elem = hdl.FirstChildElement().FirstChildElement().Element();
	
		if(!elem)
			cerr << "node to reach doesn't exist" << endl;
		else
			while (elem){
				cout << "Load object from XML" << endl;
				int tmpType;
				elem->QueryIntAttribute("type", &tmpType);
				Obj* obj = new Obj(m_pScene, elem->Attribute("src"), tmpType);
				elem->QueryIntAttribute("block", &(obj->block));
				elem->QueryDoubleAttribute("posX", &(obj->posX));
				elem->QueryDoubleAttribute("posY", &(obj->posY));
				elem->QueryDoubleAttribute("posZ", &(obj->posZ));
				
				m_lObjects.push_back(obj);
				elem = elem->NextSiblingElement();
			}
	}
}

// @FIXME
/*void Game::handleClick(Mouse.clickType) {
	// Check syntax with Mouse event
	Color color = (clickType == LEFT) ? BLUE : RED;
	Intersection * pIntersection = NULL;
	bool effectiveShoot = player.shoot(pIntersection, color);
	if(effectiveShoot) {
		portals.setPortal(color, pIntersection);
	}
}*/

bool Game::save() {
	// make xml from values
	return 0; // SUCCESS ?
}

bool Game::load() {
	// ok ?
	return 0;
}

void Game::start() {	// init level configuration
    // We set the actual camera to be the player's one (fps mode)
    m_pScene->pCamera = &m_player;
    // Shader
    m_pScene->setDefaultShaderID(loadProgram("../shaders/simpleShader.glsl"));
    
	// prepare level using xml.
	// build objects from xml
	// add 'em to the scene
	// ... like that

	loadLevel();

	for(list<Obj*>::iterator i = m_lObjects.begin(); i != m_lObjects.end(); ++i) {
		buildObjectGeometryFromOBJ((*i)->object, (*i)->path.c_str(), false, false);
		m_pScene->addObjectToDraw((*i)->object.id);
		m_pScene->setDrawnObjectColor((*i)->object.id, Color(frand(), frand(), frand()));
		//m_pScene->setDrawnObjectModel((*i)->object.id, scale(Vector3f(10, 10, 10)));
	}

	m_bRunning = true;
}

void Game::exit() {
	m_bRunning = false;
}

void Game::update() {
	if(!m_bPause)
		((MoveableCamera*)m_pScene->pCamera)->move();
		
	/*
	// @FIXME : Check this harder (no levelStatus but getPosition())
	switch(levelStatus) {
		case LEVEL_FINISHED :
			if(m_game.player.level != LEVEL_MAX) {
				++(m_game.player.level);
			} else {
				// GAME OVER ! // EXIT APP
			}
		case LEVEL_FAILED :
			m_bRunning = false;
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

void Game::handleKeyEvent(const SDL_keysym& keysym, bool down) {
	if(keysym.sym == SDLK_p && down)
		switchPause();
	else if(keysym.sym == SDLK_g && down && !m_bPause)
		switchGhostMode();
	else if(!m_bPause) {
		Direction to = NOWHERE;
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
			((MoveableCamera*)m_pScene->pCamera)->setMovement(to, down);
	}
}

void Game::switchGhostMode() {
	m_bGhostMode = !m_bGhostMode;
	m_pScene->pCamera = m_bGhostMode ? &m_ghostCamera : &m_player;
	cout << (m_bGhostMode ? "GhostMode on" : "GhostMode off") << endl;
}

void Game::switchPause() {
	m_bPause = !m_bPause;
	m_pScene->pCamera = &m_player;
	cout << (m_bPause ? "Pause on" : "Pause off") << endl;
}
