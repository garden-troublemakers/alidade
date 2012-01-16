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
	GLuint fboID;
	GLuint depthBufferID;
	GLuint textureID;
	GLenum fboBuffs;
	stein::MeshBuilder surfaceBuilder;
	stein::MeshBuilder frameBuilder;

	virtual ~Mirror() {}
	Mirror(stein::Scene* pS, const GLuint& sId) : 
		MoveableCamera(), pScene(pS), shaderId(sId),
		frame(pScene, shaderId, "", MIRROR), surface(pScene, shaderId, "", MIRROR)
	{
		glGenFramebuffers(1, &(fboID));
		glGenRenderbuffers(1, &(depthBufferID));
		glGenTextures(1, &(textureID));
		fboBuffs=GL_COLOR_ATTACHMENT0;
		
		pScene->addObjectToDraw(frame.object.id);
		pScene->addObjectToDraw(surface.object.id);
		buildSquare(frame.object, 1, surfaceBuilder);
		buildSquare(surface.object, 0.5, surfaceBuilder);
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
		setRotation(rot);
	}
	void prepareFBO(int width, int height)
	{
		// Binds the FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboID);
		// Creates depth renderbuffer
		glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
		// Creates the color final texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		// How to handle not normalised uvs
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// How to handle interpolation from texels to fragments
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Attaches texture to the shader color output and the RBO to the depth
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);
		//getFBOErrors();
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	
};

#endif // _MIRROR_HPP_
