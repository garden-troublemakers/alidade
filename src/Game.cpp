#include "Obj.hpp"
#include "Game.hpp"

using namespace std;
using namespace stein;

Game::Game(Scene* pScene):
	m_pScene(pScene), m_ghostCamera(), m_portals(), m_player(pScene),
	m_level(EASY), m_pMirrors(), m_lObjects(),
	m_bRunning(false), m_bPause(false), m_bGhostMode(false)
{}

Game::~Game() {
	//delete [] player;
	/*list delete m_lObjects;*/
	while(!m_pMirrors.empty()) {
        delete m_pMirrors.back();
        m_pMirrors.pop_back();
    }
    
}

void Game::loadLevel() {
	list<Obj> objList;
	TiXmlDocument *xmlDoc = NULL;
	TiXmlElement *elem = NULL;
	
	cout << "loadLevel" << endl;
	
	//Loading xml depending on level chosen
	if(m_level == EASY)
		xmlDoc = new TiXmlDocument("../res/maps/tuto.xml");
	else if(m_level == HARD)
		xmlDoc = new TiXmlDocument("../res/maps/ez.xml");
		
		cout << "else if" << endl;
		
	if(!xmlDoc->LoadFile()) {
		cerr << "loading error" << endl;
		cerr << "error #" << xmlDoc->ErrorId() << " : " << xmlDoc->ErrorDesc() << endl;
	}
	else {
		cout << "else" << endl;
		//Parsing the xml document
		TiXmlHandle hdl(xmlDoc);
		elem = hdl.FirstChildElement().FirstChildElement().Element();
	
		if(!elem)
			cerr << "node to reach doesn't exist" << endl;
		while (elem){
			cout << "Load object from XML" << endl;
			int tmpType;
			elem->QueryIntAttribute("type", &tmpType);
			Obj* obj = new Obj(m_pScene, elem->Attribute("src"), VISIBLE_WALL);
			elem->QueryIntAttribute("block", &(obj->block));
			elem->QueryDoubleAttribute("posX", &(obj->posX));
			elem->QueryDoubleAttribute("posY", &(obj->posY));
			elem->QueryDoubleAttribute("posZ", &(obj->posZ));
			
			m_lObjects.push_back(obj);
			elem = elem->NextSiblingElement();
		}
		for(size_t j = 0; j < 10 ; ++j)
			m_pMirrors.push_back(new Mirror(m_pScene));
		for(size_t i= 0; i < m_pMirrors.size(); ++i) {
			Matrix4f rotation = xRotation(-float(0.33*i * M_PI)) *  yRotation(float(0.33*i * M_PI));
			m_pMirrors[i]->gotoPositionRotation(Vector3f(35, 10, 2*i), rotation);
		}
	}
	delete xmlDoc;
	delete elem;
}

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
    m_player.setPosition(Vector3f(37,.5,10));
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
	
	for(size_t i = 0; i < m_pMirrors.size(); ++i) {
		//m_pMirrors[i]->goToPosition(Vector3f(35,1,10*(i+1)));
	}			
	
	
	// We add mirrors
	

	m_bRunning = true;
}

void Game::exit() {
	m_bRunning = false;
}

void Game::update() {
	if(!m_bPause) {
		((MoveableCamera*)m_pScene->pCamera)->move();
		if(m_bGhostMode) {
		} else {
			/*Portal* newPortal;
			if(!!m_player.checkCollisionPortals(m_portals, newPortal)) { // const Portal* Portals::checkCollisionPortal(const Portals & portals) const;
				// teleport player depending on newPortal
				// m_player->setPosition( new position )
				// m_player.nextMove( ... ) // Inverse the vector for rotating camera when the player crosses a portal
			}
			if(!m_player.checkCollisions(m_lObjects)) { // bool Portals::checkCollisionPortal(std::list<Obj*>) const;
				((MoveableCamera*)m_pScene->pCamera)->move();
			}*/
		}
		m_portals.update(m_player.getPosition());

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

void Game::handleMouseEvent(const SDL_MouseButtonEvent& mEvent) {
	if(m_bRunning && mEvent.type == SDL_MOUSEBUTTONDOWN  && mEvent.state == SDL_PRESSED) {
		if(!m_bPause && !m_bGhostMode){
			// Add delay between launches and getter for color ?
			//Color color = (click.LEFT) ? Color.BLUE : Color.RED;
			if(mEvent.button == SDL_BUTTON_LEFT) {
				m_player.shootPortal(Color::BLUE);
				Vector3f forward;
				forward.z = 1.;
				//forward = forward * Matrix4f(m_pScene->pCamera->getView()); // @TODO get forward vector the vector directing the player's camera
				Ray shoot(m_player.getPosition(), forward);
				//Intersection intersection();
				
				//m_portals.setPortal(Color::BLUE, m_pScene);
				//
				cout << " click gauche " << endl;
				//Color color = (click.LEFT) ? Color.BLUE : Color.RED;
			}
			else if(mEvent.button == SDL_BUTTON_RIGHT) {
				m_player.shootPortal(Color::RED);
				cout << " click droit " << endl;
			}
			if(mEvent.button == SDL_BUTTON_LEFT || mEvent.button == SDL_BUTTON_LEFT) {
					//Intersection intersection(); // compute this
					// if intersection.obj.type == PORTALABLE ...
						//m_portals.setPortal(color, intersection, &m_player, m_pScene);
			}
			// Build intersection here.
			//m_portals.setPortal(color, intersection, &m_player, m_pScene);
		}
	}
}

void Game::switchGhostMode() {
	m_bGhostMode = !m_bGhostMode;
	// @TODO : reset nextMove of camera
	if(m_bGhostMode)
		m_ghostCamera.setPosition(m_player.getPosition() - Vector3f(1,0,1));
	m_pScene->pCamera = m_bGhostMode ? &m_ghostCamera : &m_player;
	cout << (m_bGhostMode ? "GhostMode on" : "GhostMode off") << endl;
}

void Game::switchPause() {
	m_bPause = !m_bPause;
	// @TODO : reset nextMove of camera if pause on
	m_pScene->pCamera = &m_player;
	cout << (m_bPause ? "Pause on" : "Pause off") << endl;
}
