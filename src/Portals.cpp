#include "Portals.hpp"

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

void Portals::setPortal(const Color & color, const Intersection * const pIntersection, Scene* pScene) {
	// Create the portal with the color corresponding to the type
	// Make it a portal or not.
	if(color != Color::RED && color != Color::BLUE) {
		std::cerr << "Invalid Portal color" << std::endl;
		exit(1);
	}
	Portal* pCurrentPortal = (color == Color::BLUE) ? pBluePortal : pRedPortal;
	Portal* pOtherPortal = (color == Color::RED) ? pBluePortal : pRedPortal;
	
	// If current portal, delete it gracefuly
	if(!!pCurrentPortal) {
		delete pCurrentPortal;
		pCurrentPortal = NULL;
	}
	
	// intersection = new portal
	if(pIntersection) {
		pCurrentPortal = new Portal(pScene, color);
		
		// @TODO : Translation and rotate portal here
		std::cout << "Here i portalize" << std::endl;
	}
	
	// set other portals' accessors
	if(!!pCurrentPortal)
		pCurrentPortal->setOtherPortal(pOtherPortal);
	if(!!pOtherPortal)
		pOtherPortal->setOtherPortal(pCurrentPortal);
}
