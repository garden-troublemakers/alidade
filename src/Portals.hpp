#ifndef _PORTALS_HPP_
#define _PORTALS_HPP_

#include "Geometry.hpp"
#include "Portal.hpp"
#include <stein/Scene.hpp>
#include <stein/math/Vector3f.hpp>

struct Portals {
	Portal * pBluePortal;
	Portal * pRedPortal;
	
	Portals();
	~Portals();
	
	void update(const stein::Vector3f & playerPos);
	void setPortal(const bool & bRed, const Intersection * const pIntersection, stein::Scene* pScene);
};

#endif // _PORTALS_HPP_
