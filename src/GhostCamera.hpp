#ifndef _GHOST_CAMERA_HPP_
#define _GHOST_CAMERA_HPP_

#include <stein/Camera.hpp>

class GhostCamera : public stein::Camera {
public :
	GhostCamera();
	~GhostCamera();
	void move();
};

#endif // _GHOST_CAMERA_HPP_
