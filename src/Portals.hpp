#ifndef _PORTALS_HPP_
#define _PORTALS_HPP_

#include "Geometry.hpp"
#include "Portal.hpp"
#include <stein/Color.hpp>
#include <stein/Scene.hpp>

struct Portals {
	Portal * pBluePortal;
	Portal * pRedPortal;
	
	Portals();
	~Portals();
	
	void update();
	void setPortal(stein::Color & color, Intersection & intersection, const Player* pPlayer, stein::Scene* pScene);
};

#endif // _PORTALS_HPP_
