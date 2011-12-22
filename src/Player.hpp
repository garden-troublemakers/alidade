#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stein/math/Vector3f.hpp>
#include "Camera.hpp"


class Player {
private :
	Vector3f m_Movement;
public :
	Camera camera;
	//@TODO : Player Constructor
	Player();
	~Player();
	move();
};

#endif // _PLAYER_H_
