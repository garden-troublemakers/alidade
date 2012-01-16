#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MoveableCamera.hpp"
#include "Geometry.hpp"
#include "Portals.hpp"
#include "Portal.hpp"
#include "Obj.hpp"
#include <stein/Color.hpp>
#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>
#include <stein/Application.hpp>
#include <stein/Builders.hpp>
#include <stein/Scene.hpp> 

#include <list>

class Player : public MoveableCamera, public Obj {
private :
	//stein::Vector3f m_movement;
	size_t m_life;
	stein::Scene* m_pScene;
	std::vector<stein::Vector3f> m_corners;
public :
	void mirror(Portal& p);
	const static float PLAYER_HEIGHT = 2.5;
	// const static std::string PLAYER_PATH = "./player.obj";
	Player(stein::Scene * pScene);
	virtual ~Player();
	void shootPortal(stein::Color color);
	virtual void teleport(Portal* pPortal);
	virtual stein::Vector3f mirrorPosition(Portal* pPortal);
	virtual stein::Vector3f mirrorDirection(Portal* pPortal);
	// redefinition from MoveableCamera
	virtual void setDirection(stein::Vector3f rotation);
	virtual void move();
	virtual void gotoPositionRotation(const stein::Vector3f & pos, stein::Matrix4f rot = stein::Matrix4f::identity());
	bool checkCollision(const Obj* obj);
};

#endif // _PLAYER_H_
