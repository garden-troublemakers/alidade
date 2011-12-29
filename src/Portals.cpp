#include "Portal.hpp"

Portal::Portal(unsigned int color, bool isMirror) :
	Camera(),
	m_type(color),
	m_bMirror(isMirror)
{
	draw();
}

Portal::~Portal() {
}

// called at each frame
void Portal::update() {
	// Change texture depending on camera.
	if(m_bMirror) {
		// orientate to ourself
	} else {
		// orientate using another portal camera
	}
}

void Portal::draw() const {
	// add 3d object here, depending on attributes
}

void Portal::setPortal() {
	m_bMirror = false;
	draw();
}

void Portal::setMirror() {
	m_bMirror = true;
	draw();
}
