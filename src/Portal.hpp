#ifndef _PORTAL_HPP_
#define _PORTAL_HPP_

#include "Mirror.hpp"
#include <stein/Object.hpp>
#include <stein/Builders.hpp>
#include <stein/Camera.hpp>
#include <stein/Scene.hpp>
#include <stein/Color.hpp>
#include <stein/math/Vector3f.hpp>

struct Portal : public Mirror {
	stein::Color color;
	
	Portal* pSecondPortal; 
	Portal(stein::Scene* pScene, stein::Color col) :
		Mirror(pScene), color(col), pSecondPortal(NULL)
	{}
	
	virtual ~Portal() { delete pSecondPortal; }
	
	virtual void update(const stein::Vector3f & playerPos) {
		// update camera fixed on mirror.
		if(!pSecondPortal)
			Mirror::update(playerPos);
		else {
			stein::Vector3f sourcePos(pSecondPortal->getPosition() + (playerPos - getPosition()));
			pSecondPortal->mirrorView(sourcePos);
			//pSecondPortal->update();
			//pSecondPortal // ?
			// show second portal view
		}
	}
	
	inline void setOtherPortal(Portal * pOtherPortal) {
		pSecondPortal = pOtherPortal;
	}
};

#endif // _PORTAL_HPP_
