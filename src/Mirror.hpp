#ifndef _MIRROR_HPP_
#define _MIRROR_HPP_

#include "MoveableCamera.hpp"
#include "Obj.hpp"
#include <stein/Object.hpp>
#include <stein/Builders.hpp>
#include <stein/Scene.hpp>
#include <stein/Color.hpp>
#include <stein/math/Vector3f.hpp>	
#include <stein/math/Matrix4f.hpp>	

struct Mirror : public MoveableCamera {
	stein::Scene* pScene;
	const GLuint shaderId;
	Obj frame;
	Obj surface;
	virtual ~Mirror() { std::cout << "destruct mirror" << std::endl;}
	Mirror(stein::Scene* pS, const GLuint& sId) : 
		MoveableCamera(), pScene(pS), shaderId(sId),
		frame(pScene, shaderId, std::string(), MIRROR), surface(pScene, shaderId, std::string(), MIRROR)
	{
		pScene->addObjectToDraw(frame.object.id);
		pScene->addObjectToDraw(surface.object.id);
		buildSquare(frame.object, 1);
		buildSquare(surface.object);
		std::cout << "Mirrors" << std::endl;	
		pScene->setDrawnObjectColor(frame.object.id, stein::Color::WHITE);
		pScene->setDrawnObjectColor(surface.object.id, stein::Color::GRAY);
	}
	
	Mirror(const Mirror &other) :
		pScene(other.pScene), shaderId(other.shaderId), frame(pScene, shaderId, std::string(), MIRROR), surface(pScene, shaderId, std::string(), MIRROR) {}
	
	void mirrorView(const stein::Vector3f & playerPos) {
		stein::Vector3f targetPos = playerPos - getPosition();
		targetPos.x *= -1.; // mirror effect
		// camera lookAt(targetPosition)
	}
	
	// called at each frame
	virtual void update(const stein::Vector3f & playerPos) {
		mirrorView(playerPos);
		// show own view
		// orient toward player->getPosition(), inversed in camera view matrix
		// lookat new fictive position
	}
	
	virtual void gotoPositionRotation(stein::Vector3f pos, stein::Matrix4f rot = stein::Matrix4f::identity()) {
		pos.y *= -1;
		stein::Matrix4f tr(translation(-pos));
		rot.transpose();
		pScene->setDrawnObjectModel(surface.object.id, tr*rot);		
		pScene->setDrawnObjectModel(frame.object.id, tr*rot);
		setPosition(pos);
	}
	
};

#endif // _MIRROR_HPP_
