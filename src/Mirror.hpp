#ifndef _MIRROR_HPP_
#define _MIRROR_HPP_

#include "Player.hpp"
#include <stein/Object.hpp>
#include <stein/Builders.hpp>
#include <stein/Camera.hpp>
#include <stein/Scene.hpp>
#include <stein/Color.hpp>
#include <stein/math/Vector3f.hpp>

struct Mirror : public stein::Camera {
	stein::Scene* pScene;
	Player* pPlayer;
	stein::Object frame;
	stein::Object surface;
	Mirror(stein::Scene* pS, Player* pP) : 
		stein::Camera(), pScene(pS), pPlayer(pP),
		frame(pScene->createObject(GL_TRIANGLES)), surface(pScene->createObject(GL_TRIANGLES))
	{
		buildSquare(frame, .6);
		buildSquare(surface);
		pScene->addObjectToDraw(frame.id);
		pScene->addObjectToDraw(surface.id);
		pScene->setDrawnObjectColor(frame.id, stein::Color::WHITE);
		pScene->setDrawnObjectColor(surface.id, stein::Color::GRAY);
	}
	virtual ~Mirror() {}
	
	void mirrorView(const stein::Vector3f & sourcePos) {
		stein::Vector3f targetPos = sourcePos - getPosition();
		targetPos.x *= -1.; // mirror effect
		// camera lookAt(targetPosition)
	}
	
	// called at each frame
	virtual void update() {
		stein::Vector3f sourcePos(pPlayer->getPosition());
		mirrorView(sourcePos);
		// show own view
		// orient toward player->getPosition(), inversed in camera view matrix
		// lookat new fictive position
	}
};

#endif // _MIRROR_HPP_
