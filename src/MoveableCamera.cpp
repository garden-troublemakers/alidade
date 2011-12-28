#include "MoveableCamera.hpp"

MoveableCamera::MoveableCamera(Position pos) :
	Camera(),
	IMoveable(pos)
{
	// @TODO : Camera settings goes here
	// setPosition();
}

MoveableCamera::~MoveableCamera() {

}

void MoveableCamera::move() {
	
}
