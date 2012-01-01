#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MoveableCamera.hpp"
#include "Geometry.hpp"
#include "Obj.hpp"
#include <stein/Color.hpp>
#include <stein/math/Vector3f.hpp>
#include <stein/Camera.hpp>
#include <stein/Application.hpp>
#include <list>

// forward declaration
class MoveableCamera;

class Player : public MoveableCamera {
private :
	//stein::Vector3f m_movement;
	size_t m_life;
public :
	const static float PLAYER_HEIGHT = 0.8;
	Player();
	~Player();
	bool shootPortal(stein::Color color, std::list<Obj> lObjects);
};

#endif // _PLAYER_H_
