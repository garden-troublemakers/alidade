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

void Portals::setPortal(Color & color, Intersection & intersection, Scene* pScene) {
	// Find the nearest portal from intersection
	// Create the portal with the color corresponding to the type
	// Make it a portal or not.
	if(color != Color::RED && color != Color::BLUE) {
		std::cerr << "Invalid Portal color" << std::endl;
		exit(1);
	}
	Portal* pCurrentPortal = (color == Color::BLUE) ? pBluePortal : pRedPortal;
	Portal* pOtherPortal = (color == Color::RED) ? pBluePortal : pRedPortal;
	
	if(!!pCurrentPortal) {
		delete pRedPortal;
		if(!!pOtherPortal)
			pOtherPortal->setOtherPortal(NULL);
	}
	// @TODO : IF intersection OK
	if(true) {
		// if Intersection ok
		pCurrentPortal = new Portal(pScene, color);
		if(!!pOtherPortal) {
			pCurrentPortal->setOtherPortal(pOtherPortal);
			pOtherPortal->setOtherPortal(pCurrentPortal);
		}
	}
}

/*void Portals::setBluePortal(Color color, Intersection intersection) {
}*/

/*
void Portals::setPortal(Color color, Intersection intersection) {
			// We are attempting to create a portal on a non-PortalSurface so we delete it.
		if(surfaceIsPortalSurface) {
			if(!portals[type])
				portals[type] = Portal(type, isMirror, surface);
			else
				portals[type].setPortal(surface, collisionPoint);
				// change position
			if(!isMirror)
				portals[1-type].setPortal()//setMirror(false);
		}
	pPortal
	if(portal.color == BLUE) {
		if(!bluePortal) {
			portal.
			pBluePortal = &portal;
		}
			delete pBluePortal;
		}
	} else if(portal.color == RED) {
		if(!!redPortal) {
			delete redPortal;
		}
		redPortal = &portal;
	}
	
}*/
