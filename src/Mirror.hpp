#ifndef _MIRROR_HPP_
#define _MIRROR_HPP_

#include <stein/Object.hpp>
#include <stein/Builders.hpp>
#include <stein/Camera.hpp>
#include <stein/Scene.hpp>
#include <stein/Color.hpp>


struct Mirror : public stein::Camera {
	stein::Object frame;
	stein::Object surface;
	Mirror(stein::Scene* pScene) : 
		stein::Camera(), frame(pScene->createObject(GL_TRIANGLES)), surface(pScene->createObject(GL_TRIANGLES))
	{
		buildSquare(frame, .6);
		buildSquare(surface);
		pScene->addObjectToDraw(frame.id);
		pScene->addObjectToDraw(surface.id);
		pScene->setDrawnObjectColor(frame.id, stein::Color::WHITE);
		pScene->setDrawnObjectColor(surface.id, stein::Color::GRAY);
	}
	virtual ~Mirror() {}
	// called at each frame
	virtual void update() {
		// show own view
	}
};

struct Portal : public Mirror {
	stein::Color color;
	Portal* pSecondPortal;
	Portal(stein::Scene* pScene, stein::Color col) :
		Mirror(pScene), color(col), pSecondPortal(NULL)
	{
	
	}
	virtual ~Portal() {}
	// Not the same signature, former parameter : const Portal & otherPortal
	virtual void update() {
		if(!pSecondPortal)
			Mirror::update();
		else {
			pSecondPortal->update(); // ?
			// show second portal view
		}
	}
	
	inline void setOtherPortal(Portal * pOtherPortal) {
		pSecondPortal = pOtherPortal;
	}
};

#endif // _MIRROR_HPP_
