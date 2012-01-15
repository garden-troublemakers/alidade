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
	while(!m_pMirrors.empty()) {
        delete m_pMirrors.back();
        m_pMirrors.pop_back();
    }
}

void Game::loadLevel() {
	list<Obj> objList;
	TiXmlDocument* xmlDoc = NULL;
	TiXmlElement* elem = NULL;
	
	//Loading xml depending on level chosen
	if(m_level == EASY)
		xmlDoc = new TiXmlDocument("../res/maps/tuto.xml");
	else if(m_level == HARD)
		xmlDoc = new TiXmlDocument("../res/maps/ez.xml");

	if(!xmlDoc->LoadFile()) {
		cerr << "loading error #" << xmlDoc->ErrorId() << " : " << xmlDoc->ErrorDesc() << endl;
	}
	else {
		//Parsing the xml document
		TiXmlHandle hdl(xmlDoc);
		elem = hdl.FirstChildElement().FirstChildElement().Element();
	
		if(!elem)
			cerr << "node to reach doesn't exist" << endl;
		while (elem){
			int tmpType;
			elem->QueryIntAttribute("type", &tmpType);
			Obj* obj = new Obj(m_pScene, elem->Attribute("src"), (ObjectType)tmpType);
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
	xmlDoc = NULL;
	elem = NULL;
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
    vector<string> files;
    files.push_back("../shaders/shaderTools.glsl");
    files.push_back("../shaders/lightingShader.glsl");
    GLuint shaderId = loadProgram(files);
    files.pop_back();
    //m_pScene->setDefaultShaderID(shaderId);
    glUseProgram(shaderId);
    GLfloat ambient[] = {1., 1., 1., 1.,};
    GLfloat diffuse[] = {1., 1., 1., 1.,};
    GLfloat specular[] = {1., 1., 1., 1.,};
    GLfloat ka=0.01, kd=1.0, ks=2.0, shininess=5.0;
    setMaterialInShader(shaderId, ambient, diffuse, specular, ka, kd, ks, shininess);
    
	// prepare level using xml for building objects
	loadLevel();
	
	// add 'em to the scene
	for(list<Obj*>::iterator i = m_lObjects.begin(); i != m_lObjects.end(); ++i) {
		buildObjectGeometryFromOBJ((*i)->object, (*i)->path.c_str(), false, false, (*i)->builder);
		m_pScene->addObjectToDraw((*i)->object.id);
		m_pScene->setDrawnObjectColor((*i)->object.id, Color(frand(), frand(), frand()));
		m_pScene->setDrawnObjectTextureID((*i)->object.id, 0, (*i)->object.getTextureId());
		m_pScene->setDrawnObjectShaderID((*i)->object.id, shaderId);
		m_pScene->setDrawnObjectModel((*i)->object.id, scale(Vector3f(10, 10, 10)));
	}
	
	for(size_t i = 0; i < m_pMirrors.size(); ++i) {
		//m_pScene->setDrawnObjectColor(frame.object.id, stein::Color::WHITE);
		//m_pScene->setDrawnObjectColor(surface.object.id, stein::Color::GRAY);
		//m_pMirrors[i]->goToPosition(Vector3f(35,1,10*(i+1)));
	}
	
	// We add mirrors

	m_bRunning = true;
}

void Game::exit() {
	m_bRunning = false;
}

void Game::update() {
		((MoveableCamera*)m_pScene->pCamera)->move();
		if(m_bGhostMode) {
		} else {
			//	test collision with objs
			//  switch
			list<Obj*> objects = m_lObjects;
			objects.push_back(&(m_portals.pBluePortal->frame));
			objects.push_back(&(m_portals.pBluePortal->surface));
			objects.push_back(&(m_portals.pRedPortal->frame));
			objects.push_back(&(m_portals.pRedPortal->surface));
			for(std::vector<Mirror*>::iterator i = m_pMirrors.begin(); i != m_pMirrors.end(); ++i) {
				objects.push_back(&((*i)->frame));
				objects.push_back(&((*i)->surface));
			}
			
			for(list<Obj*>::iterator i = objects.begin(); i != objects.end(); ++i) {
				break;
				/*Collision collision(*i);
				if(m_player.checkCollision(collision) {
					switch((*i)->type) {
						case PORTAL :
							// teleport
							m_player.teleport(Portal portal);
							break;
						case ACTION_ZONE :
							// do the dance
							break;
						case INVISIBLE_WALL :
						case PORTALABLE_ZONE :
						case VISIBLE_WALL :
						case MIRROR :
							// un-set movement
						default :
							break;
					}
					
					// avoid looping on other objects
					break;
				}*/
			}
			/*
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
			Color color = (mEvent.button == SDL_BUTTON_LEFT) ? Color::BLUE : Color::RED;
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

// On click, when the game is running
void Game::handleShootPortal(stein::Color color) {
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
	Matrix4f forward = translation(Vector3f(0,0,-1));
	Ray ray(m_player.getPosition(), Vector3f(forward(3,0), forward(3,1), forward(3,2)));
	Intersection* pIntersection = NULL;
	
	// walkin' through portalable zones
	cout << "nbObjects" << m_lObjects.size() << endl;
	for(list<Obj*>::iterator i = m_lObjects.begin(); i != m_lObjects.end(); ++i)
		if((*i)->type == PORTALABLE_ZONE) {
			intersectRayObject(ray, *i, &m_player, pIntersection);	
		}
	
	// do the right thing.			
	if(pIntersection) {
		m_portals.setPortal(color, *pIntersection, m_pScene);
	}

	delete pIntersection;
	pIntersection = NULL;
}
