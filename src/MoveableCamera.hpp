#ifndef _MOVEABLE_CAMERA_HPP_
#define _MOVEABLE_CAMERA_HPP_

#include <stein/Camera.hpp>
#include <stein/math/Vector3f.hpp>
#include <stein/Application.hpp>
#include <cstdlib>
#include <iostream>

using namespace stein;
using namespace std;

enum Direction {
	RIGHT = 0, UP = 1, FORWARD = 2, LEFT = 3, DOWN = 4, BACKWARD = 5, NOWHERE = 6
};

class MoveableCamera : public stein::Camera {
public:
	stein::Vector3f m_nextMove;
	
protected :
	const stein::Application * const m_pApplication;
	GLfloat m_xMousePosition;
	GLfloat m_yMousePosition;
	 
public :
	const static GLfloat MOVE_STEP = 0.1;

	MoveableCamera(GLfloat height, const Application * const pApplication);
	virtual ~MoveableCamera();
	void setMovement(Direction to, bool add);
	void move();
	virtual void translate();
	virtual void rotate();
};

#endif // _MOVEABLE_CAMERA_HPP_
