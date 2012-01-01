#include "Portals.hpp"

Portals::Portals() : pBluePortal(NULL), pRedPortal(NULL)
{}

Portals::~Portals() {
	delete pBluePortal;
	delete pBluePortal;
}

// called at each frame
void Portals::update() {
	// Change texture depending on camera.
	bool bMirror = (!pBluePortal || !pRedPortal);
	if(bMirror) {
		// orientate to ourself
	} else {
		// orientate using another portal camera
	}
}

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
