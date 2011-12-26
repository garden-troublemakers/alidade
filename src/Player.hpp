#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "IMoveable.hpp"
#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>


class Player : public IMoveable {
private :
	stein::Vector3f m_movement;
	unsigned int m_life;
public :
	stein::Camera camera;
	//@TODO : Player Constructor
	Player();
	virtual ~Player();
	virtual void move();
	virtual void setMovement(unsigned int);
	bool shootPortal(unsigned int type);
	unsigned int getLife();
};

#endif // _PLAYER_H_
