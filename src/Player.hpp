#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MoveableCamera.hpp"
#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>


class Player : public MoveableCamera {
private :
	stein::Vector3f m_movement;
	unsigned int m_life;
public :
	//@TODO : Player Constructor
	Player();
	virtual ~Player();
	virtual void move();
	bool shootPortal(unsigned int type);
	unsigned int getLife();
};

#endif // _PLAYER_H_
