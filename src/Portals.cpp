#include "Portals.hpp"
#include <stein/Color.hpp>

using namespace stein;

Portals::Portals() : pBluePortal(NULL), pRedPortal(NULL)
{}

Portals::~Portals() {
	delete pBluePortal;
	delete pRedPortal;
}

// called at each frame
void Portals::update(const Vector3f & playerPos) {
	if(!!pBluePortal)
		pBluePortal->update(playerPos);
	if(!!pRedPortal)
		pRedPortal->update(playerPos);
}

void Portals::setPortal(const bool & bRed, const Intersection * const pIntersection, Scene* pScene) {
	// Create the portal with the color corresponding to the type
	// Make it a portal or not.
	Color color = (bRed) ? Color::RED : Color::BLUE;
	Portal* pCurrentPortal = bRed ? pRedPortal : pBluePortal;
	Portal* pOtherPortal = bRed ? pBluePortal : pRedPortal;
	
	// If current portal, delete it gracefuly
	if(!!pCurrentPortal) {
		delete pCurrentPortal;
		pCurrentPortal = NULL;
	}

	// intersection = new portal
	if(pIntersection) {
		pCurrentPortal = new Portal(pScene, pScene->defaultShaderID, color);
		
		// @TODO : Translation and rotate portal here
		std::cout << "Here i portalize" << std::endl;
	}
	
	// set other portals' accessors
	if(!!pCurrentPortal)
		pCurrentPortal->setOtherPortal(pOtherPortal);
	if(!!pOtherPortal)
		pOtherPortal->setOtherPortal(pCurrentPortal);
}
