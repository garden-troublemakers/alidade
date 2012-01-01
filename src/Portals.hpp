#ifndef _PORTALS_HPP_
#define _PORTALS_HPP_

#include "Mirror.hpp"
#include "Geometry.hpp"
#include <stein/Color.hpp>

struct Portals {
	Portal * pBluePortal;
	Portal * pRedPortal;
	
	Portals();
	~Portals();
	
	void update();
	/*
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
	
	
=======
#ifndef _PORTAL_HPP_
#define _PORTAL_HPP_

#include <stein/Camera.hpp>
#define BLUE	0
#define RED		1

class Portal : public stein::Camera {
	private :
		unsigned int m_type;
		bool m_bMirror;
		PortalSurface* m_surface;
		
	// ALL the properties of Camera
	public :
		Portal(const size_t & type);
		~Portal();
		// Will be called in animate()
		void update();
		void draw() const;
		void setPortal();
		void setMirror();
}

struct Portals {
	Portal* portals;
	
	Portals() : portals[2]() {}
	virtual ~Portal();
>>>>>>> portal
	
	// @TODO : Class Surface or struct
	virtual void makePortal(MouseButton, const Surface & surface) {
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
				portals[1-type].setPortal();//setMirror(false);
		}
	}
	
	virtual void destructPortal(KeyboardKey) {
		bool isMirror = !portals[1-type];
		portals[type] = NULL;
		if(!isMirror)
			portals[1-type].setMirror(true);
	}*/
};

#endif // _PORTAL_HPP_
