#ifndef _MOVEABLE_CAMERA_HPP_
#define _MOVEABLE_CAMERA_HPP_

//#include "GameApplication.hpp"
#include <SDL/SDL.h>
#include <stein/Camera.hpp>
#include <stein/math/Vector3f.hpp>
#include <cstdlib>
#include <iostream>
#include <stein/Tools.hpp>

// forward declaration
class GameApplication;

enum Direction {
	RIGHT = 0, UP = 1, FORWARD = 2, LEFT = 3, DOWN = 4, BACKWARD = 5, NOWHERE = 6
};

class MoveableCamera : public stein::Camera {
protected :
	stein::Vector3f m_nextMove;
	float m_xMousePosition;
	float m_yMousePosition;
	 
public :
	const static float MOVE_STEP = 0.1;

	MoveableCamera(float height = 0.8);
	virtual ~MoveableCamera();
	void setMovement(Direction to, bool add);
	virtual void move();
	/*
	virtual void translate();
	virtual void rotate();
	*/
};

#endif // _MOVEABLE_CAMERA_HPP_
