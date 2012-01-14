#include "Obj.hpp"
#include "Game.hpp"

using namespace std;
using namespace stein;

Game::Game(Scene* pScene):
	m_pScene(pScene), m_ghostCamera(), m_portals(), m_player(pScene),
	m_level(EASY), m_pMirrors(), m_lObjects(),
	m_bRunning(false), m_bPause(false), m_bGhostMode(false) {	
	}



Game::~Game() {
	while(!m_pMirrors.empty()) {
        delete m_pMirrors.back();
        m_pMirrors.pop_back();
    }
}

void Game::loadLevel() {
	list<Obj> objList;
	TiXmlDocument* xmlDoc = NULL;
	TiXmlElement* elem = NULL;
	
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
    GLuint shaderId = loadProgram("../shaders/lightingShader.glsl");
    //m_pScene->setDefaultShaderID();
	// cout << "fu" << endl;
	// loadTexture("../res/textures/image1.ppm");
	// glUniform1i(glGetUniformLocation(shaderId, "textureUnit0"), 0);

    
	// prepare level using xml.
	// build objects from xml
	// add 'em to the scene
	// ... like that

	loadLevel();
	for(list<Obj*>::iterator i = m_lObjects.begin(); i != m_lObjects.end(); i.next()) {
		buildObjectGeometryFromOBJ((*i)->object, (*i)->path.c_str(), false, false);
		m_pScene->addObjectToDraw((*i)->object.id);
		m_pScene->setDrawnObjectColor((*i)->object.id, Color(frand(), frand(), frand()));
		m_pScene->setDrawnObjectTextureID((*i)->object.id, 0, (*i)->object.getTextureId());
		m_pScene->setDrawnObjectShaderID((*i)->object.id, shaderId);
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
			Color color = (mEvt.button == SDL_BUTTON_LEFT) ? Color::BLUE : Color::RED;
			handleShootPortal(color);
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

<<<<<<< HEAD
// On click, when the game is running
void handleShootPortal(Color color) {
	// get direction of player's camera.
	// get color of portal
	// get position
	// get shoot's direction
	// call player's shootPortal
	// launch ray
	// loop for intersections
	// 	 get intersection
	// do the job
	//   interpret color
	//   ...
	// exit
	// dir = Vector "forward" normalized
	Ray ray(m_player.getPosition(), m_player.getView()*Vector3f(0,0,-1));
	Intersection intersection;
	
	list<Obj>::iterator i = lObjects.begin();
	// walkin' through portalable zones
	while (i != lObjects.end()) {
		if(i.type == PORTALABLE_ZONE) {
			std::list<Triangle> triangles = i.getTrianglesList();
			// loop on primitives
			for(list<Triangle>::iterator t = triangles.begin(); t != triangles.end(); i.next()) {
				// make triangle
				Triangle t(a, b, c, normal, pObject);
				// get intersection
				Intersection tIntersection(ray, t);
				// test intersection
				if(tIntersection.checkIntersection()) {
					// test its depth
					if((intersection.point == stein::Vector3f()) || (tIntersection.computeDepth(m_player) < intersection.computeDepth(m_player))) {
						intersection = tIntersection;
					}
				}
			}
		}
	}
	// complexity : NB_TRIANGLE*PORTALABLE_ZONE_NUMBER
	if(intersection.point != stein::Vector3f()) {
		portals.setPortal(color, intersection, m_pScene);
	}
}
=======
>>>>>>> be574d1c1d5a71e42d6b6777d742b8a0c10a68a4
