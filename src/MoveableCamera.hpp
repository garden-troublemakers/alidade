#ifndef _GHOST_CAMERA_HPP_
#define _GHOST_CAMERA_HPP_

#include "IMoveable.hpp"
#include <stein/Camera.hpp>

class MoveableCamera : public stein::Camera, public IMoveable {
protected :
	Camera camera;

public :
	MoveableCamera(Position);
	virtual ~MoveableCamera();
	virtual void move();
};

#endif // _GHOST_CAMERA_HPP_
