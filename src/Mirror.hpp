#ifndef _MIRROR_HPP_
#define _MIRROR_HPP_

#include <stein/Builders.hpp>
#include <stein/Camera.hpp>
#include <stein/Color.hpp>
#include <stein/Scene.hpp>
#include <cstdlib>


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
		pScene->setDrawnObjectColor(frame.id, stein::Color(WHITE));
		pScene->setDrawnObjectColor(surface.id, stein::Color(GRAY));
	}
	virtual ~Mirror();
	// called at each frame
	virtual void update() {
		// show own view
	}
};

struct Portal : public Mirror {
	stein::Color color;
	Portal(stein::Scene* pScene, Color col) : Mirror(pScene), color(col) {}
	virtual ~Portal() {}
	virtual void update(const Portal & otherPortal) {
		// show otherPortal's view
	}
};

#endif // _MIRROR_HPP_
