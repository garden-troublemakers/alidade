#include "Game.hpp"

using namespace std;
using namespace stein;

Game::Game(Scene* pScene):
	m_pScene(pScene), m_ghostCamera(), m_portals(), m_player(),
	m_level(EASY), m_mirrors(), m_lObjects(),
	m_bRunning(false), m_bPause(false), m_bGhostMode(false)
{}

Game::~Game() {
	//delete [] player;
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
				Obj::ObjectType type = Obj::VISIBLE_WALL;
				Obj obj(m_pScene, elem->Attribute("src"), type);
				elem->QueryIntAttribute("block", &obj.block);
				elem->QueryDoubleAttribute("posX", &obj.posX);
				elem->QueryDoubleAttribute("posY", &obj.posY);
				elem->QueryDoubleAttribute("posZ", &obj.posZ);
				m_lObjects.push_back(obj);
				elem = elem->NextSiblingElement();
				m_pScene->addObjectToDraw(obj.object.id);
				
				//Extracting values from the xml object list to the corresponding place to build the level
				list<Obj>::iterator i;
				for(i=m_lObjects.begin(); i!= m_lObjects.end(); ++i){
					/*Object & object = new Object(GL_TRIANGLES);
					GLuint storedObjectTriangleID = m_pScene->storeObject(objectTriangle);
					buildObjectGeometryFromOBJ(objectTriangle, i->path, true);
					m_pScene->addObjectToDraw(object.id);
					m_pScene->setDrawnObjectColor(0, Color(frand(), frand(), frand()));*/
				}
			}
	}
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
    // Shader
    m_pScene->setDefaultShaderID(loadProgram("../shaders/simpleShader.glsl"));
    
	// prepare level using xml.
	// build objects from xml
	// add 'em to the scene
	// ... like that
	Object &object = m_pScene->createObject(GL_TRIANGLES);
	buildSquare(object);
	m_pScene->addObjectToDraw(object.id);

	Object &object2 = m_pScene->createObject(GL_TRIANGLES);
	buildSquare(object2);
	m_pScene->addObjectToDraw(object2.id);

	Vector3f tr(0, 0, 1);
	Vector3f rt(0, 1, 0);

	m_pScene->setDrawnObjectModel(object2.id, translation(tr) * rotation(90, rt));

	m_pScene->setDrawnObjectColor(1, Color(frand(), frand(), frand()));
	m_pScene->setDrawnObjectColor(0, Color(frand(), frand(), frand()));
	
	m_bRunning = true;
}

void Game::exit() {
	m_bRunning = false;
}

void Game::update() {
	if(!m_bPause) {
		if(m_bGhostMode) {
			((MoveableCamera*)m_pScene->pCamera)->move();
		} else {
			/*Portal* newPortal;
			if(!!m_player.checkCollisionPortals(m_portals, newPortal)) { // const Portal* Portals::checkCollisionPortal(const Portals & portals) const;
				// teleport player depending on newPortal
				
			}
			if(!m_player.checkCollisions(m_lObjects)) { // bool Portals::checkCollisionPortal(std::list<Obj*>) const;
				((MoveableCamera*)m_pScene->pCamera)->move();
			}*/
		}
		m_portals.update();
		
	}
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

void Game::handleClickEvent() {
	if(m_bRunning) {
		//Color color = (click.LEFT) ? Color.BLUE : Color.RED;
		m_player.shootPortal(Color::BLUE);
		// Build intersection here.
		//m_portals.setPortal(color, intersection, &m_player, m_pScene);
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
