#ifndef _GHOST_CAMERA_HPP_
#define _GHOST_CAMERA_HPP_

#include <stein/Camera.hpp>
#include <stein/math/Vector3f.hpp>
#include <stein/Application.hpp>
#include <cstdlib>

enum Direction {
	FORWARD = 0, RIGHT = 1, UP = 2, BACKWARD = 3, LEFT = 4, DOWN = 5
};


class MoveableCamera : public stein::Camera {
private:
	stein::Vector3f m_nextMove;
	
protected :
	stein::Application * m_pApplication;
	GLfloat xMousePosition;
	GLfloat yMousePosition;
	 
public :
	const static GLfloat MOVE_STEP = 0.1;

	MoveableCamera();
	virtual ~MoveableCamera();
	void setMovement(size_t, bool);
	void move();
	virtual void translation();
	virtual void rotation();
};

#endif // _GHOST_CAMERA_HPP_
