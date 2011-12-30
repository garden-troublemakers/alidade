#ifndef _PORTALS_HPP_
#define _PORTALS_HPP_

#include "Mirror.hpp"
#include <stein/Camera.hpp>
#include <stein/Color.hpp>

struct Portals {
	Portal * pBluePortal;
	Portal * pRedPortal;
	
	Portals();
	virtual ~Portal();
	void Portals::setPortal(const Portal & portal);
	
	
	
	// GameApplication -> gestion des événements Souris
	// NOT SURE IF NEEDED : if(ButtonClick == LEFT || ButtonClick == RIGHT) {
		// Pour tous les objets de la scène.
		calculer toutes les intersections();
	//}
	
	game -> update() {
		if(evenement nouveau portal (color)) {
			// NON
			Portal newPortal(pScene, color);
			portals.setPortal(newPortal);
		}
	}
	
	portals -> setPortal() {
		// règles de construction
	}
	
	
	
	// @TODO : Class Surface or struct
	virtual void makePortal(/*MouseButton*/, const Surface & surface) {
		size_t type = (mouseButton == LEFT) ? BLUE : RED;
		bool isMirror = !portals[1-type];
		// We are attempting to create a portal on a non-PortalSurface so we delete it.
		if(surfaceIsPortalSurface) {
			if(!portals[type])
				portals[type] = Portal(type, isMirror, surface);
			else
				portals[type].setPortal(surface, collisionPoint);
				// change position
			if(!isMirror)
				portals[1-type].setPortal()/*setMirror(false)*/;
		}
	}
	
	virtual void destructPortal(/*KeyboardKey*/) {
		bool isMirror = !portals[1-type];
		portals[type] = NULL;
		if(!isMirror)
			portals[1-type].setMirror(/*true*/);
	}
}

#endif // _PORTAL_HPP_
