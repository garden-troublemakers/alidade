#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>


class Player {
private :
	stein::Vector3f m_movement;
	unsigned int m_life;
public :
	stein::Camera camera;
	//@TODO : Player Constructor
	Player();
	~Player();
	void move();
	bool shootPortal(unsigned int type);
	unsigned int getLife();
};

#endif // _PLAYER_H_
