#ifndef _GHOST_CAMERA_HPP_
#define _GHOST_CAMERA_HPP_

#include "IMoveable.hpp"
#include <stein/Camera.hpp>

class GhostCamera : public stein::Camera, public IMoveable {
public :
	GhostCamera();
	virtual ~GhostCamera();
	virtual void move();
	virtual void setMovement(unsigned int);
};

#endif // _GHOST_CAMERA_HPP_
