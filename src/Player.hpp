#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MoveableCamera.hpp"
#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>
#include <stein/Application.hpp>


class Player : public MoveableCamera {
private :
	stein::Vector3f m_movement;
	size_t m_life;
public :
	//@TODO : Player Constructor
	const static GLfloat PLAYER_HEIGHT = 0.8;
	Player(const stein::Application * const application);
	virtual ~Player();
	bool shootPortal(Color color, list<Obj> listObjects);
};

#endif // _PLAYER_H_
