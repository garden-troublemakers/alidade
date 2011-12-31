#include "Game.hpp"

using namespace std;

Game::Game(const stein::Application * const application):
	m_player(application), m_portals(), m_bRunning(false)
{	
}

Game::~Game() {
	//delete [] player;
}

void Game::loadLevel() {
	list<Obj> objList;
	TiXmlElement *elem;
	Obj obj;
	
	//Loading xml depending on level chosen
	if(m_level == 0) {
		TiXmlDocument xmlDoc("../res/maps/tuto.xml");
			if(!xmlDoc.LoadFile()) {
				cerr << "loading error" << endl;
				cerr << "error #" << xmlDoc.ErrorId() << " : " << xmlDoc.ErrorDesc() << endl;
				return 1;
			}
	}
	else if(m_level == 1) {
		TiXmlDocument xmlDoc("../res/maps/ez.xml");
			if(!xmlDoc.LoadFile()) {
				cerr << "loading error" << endl;
				cerr << "error #" << xmlDoc.ErrorId() << " : " << xmlDoc.ErrorDesc() << endl;
				return 1;
			}
	}
	
	//Parsing the xml document
	TiXmlHandle hdl(&xmlDoc);
	elem = hdl.FirstChildElement().FirstChildElement().Element();
	
	if(!elem){
		cerr << "node to reach doesn't exist" << endl;
	}

	while (elem){
		obj.path = elem->Attribute("src");
		elem->QueryIntAttribute("block", &obj.block);
		elem->QueryDoubleAttribute("posX", &obj.posX);
		elem->QueryDoubleAttribute("posY", &obj.posY);
		elem->QueryDoubleAttribute("posZ", &obj.posZ);
		m_lObjects.push_back(obj);
		elem = elem->NextSiblingElement();
	}
	
	//Extracting values from the xml object list to the corresponding place to build the level
	list<Obj>::iterator i;
	for(i=m_lObjects.begin(); i!= m_lObjects.end(); ++i){
    	/*Object & object = new Object(GL_TRIANGLES);
    	GLuint storedObjectTriangleID = m_Scene->storeObject(objectTriangle);
    	buildObjectGeometryFromOBJ(objectTriangle, i->path, true);
    	m_Scene.addObjectToDraw(object.id);
    	m_Scene.setDrawnObjectColor(0, Color(frand(), frand(), frand()));*/
	}
}

const std::list<const stein::Object> objectsList() const {
	return m_lObjects;
}

// @FIXME
void Game::checkClick(Mouse.clickType) {
	// Check syntax with Mouse event
	Color color = (clicType == LEFT) ? BLUE : RED;
	Intersection * pIntersection = NULL;
	bool effectiveShoot = player.shoot(pIntersection, color);
	if(effectiveShoot) {
		portals.setPortal(color, pIntersection);
	}
}

bool Game::save() {
	// make xml from values
	return 0; // SUCCESS ?
}

bool Game::load() {
	return 0;
}

bool Game::isRunning() const {
	return m_bRunning;
}

void handleClick() {
	m_player.checkClick();
}

void Game::start() {
	m_bRunning = true;
	
}

void Game::exit() {

}
