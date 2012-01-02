#ifndef _PORTALS_HPP_
#define _PORTALS_HPP_

#include "Mirror.hpp"
#include "Geometry.hpp"
#include "Player.hpp"
#include <stein/Color.hpp>

struct Portals {
	Portal * pBluePortal;
	Portal * pRedPortal;
	
	Portals();
	~Portals();
	
	void update();
	void setPortal(stein::Color & color, Intersection & intersection, const Player* pPlayer, stein::Scene* pScene);
	Portal* checkPlayerCollisionPortal(const Portals & portals) const {
		if(_checkCollisionWithPortal(pPlayer->getPosition(), pBluePortal) {
			return pRedPortal;
		}
		if(_checkCollisionWithPortal(pPlayer->getPosition(), pBluePortal) {
			return pBluePortal;
		}
		return (Portal*)NULL;
	}
	
	bool _checkCollisionWithPortal(stein::Vector3f position, Portal* pPortal) const {
		return /* Position on portal ? */ true;
	}
};

#endif // _PORTAL_HPP_
