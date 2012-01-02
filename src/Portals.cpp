#include "Portals.hpp"

Portals::Portals() : pBluePortal(NULL), pRedPortal(NULL)
{}

Portals::~Portals() {
	delete pBluePortal;
	delete pRedPortal;
}

// called at each frame
void Portals::update() {
	if(pBluePortal)
		pBluePortal->update();
	if(pRedPortal)
		pRedPortal->update();
}

void Portals::setPortal(stein::Color & color, Intersection & intersection, Player* pPlayer, stein::Scene* pScene) {
	// Find the nearest portal from intersection
	// Create the portal with the color corresponding to the type
	// Make it a portal or not.
	if(color != stein::Color::RED && color != stein::Color::BLUE) {
		throw "Invalid Portal color";
		exit(1);
	}
	Portal* pCurrentPortal = (color == stein::Color::BLUE) ? pBluePortal : pRedPortal;
	Portal* pOtherPortal = (color == stein::Color::RED) ? pBluePortal : pRedPortal;
	
	if(!!pCurrentPortal) {
		delete pRedPortal;
		if(!!pOtherPortal)
			pOtherPortal->setOtherPortal(NULL);
	}
	// @TODO : IF intersection OK
	if(true) {
		// if Intersection ok
		pCurrentPortal = new Portal(pScene, color, pPlayer);
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
		// @TODO : move
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
