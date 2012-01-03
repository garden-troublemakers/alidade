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
#include <list>

class Player : public MoveableCamera {
private :
	//stein::Vector3f m_movement;
	size_t m_life;
public :
	void mirror(Portal& p);
	const static float PLAYER_HEIGHT = 0;
	Player();
	virtual ~Player();
	bool checkCollisionPortals(const Portals& portals, const Portal& newP);
	bool shootPortal(stein::Color color);
	virtual void move();
	void mirror(Portal * portal);
	//Obj* checkCollisionWithObj(list<Obj*> lObjs, mirrors?);
};

#endif // _PLAYER_H_
