#include "MoveableCamera.hpp"
#include <stein/Tools.hpp>
using namespace stein;
using namespace std;

MoveableCamera::MoveableCamera(GLfloat height, const Application * const pApplication) :
	Camera(), m_nextMove(), m_pApplication(pApplication), m_xMousePosition(), m_yMousePosition()
{	
	setPosition(Vector3f(0.,height,1.));
}

MoveableCamera::~MoveableCamera() {
}

// will be called when a key is pushed (add = true) and When the key is released (add = false)
void MoveableCamera::setMovement(Direction to, bool add) {
	size_t axis;
	if(to == FORWARD || to == BACKWARD)
		axis = FORWARD;
	else if (to == RIGHT || to == LEFT)
		axis = RIGHT;
	else
		axis = UP;

	float moveValue = (to == axis) ? 1. : -1.;
	
	//@TODO add operator override 
	if(add)
		m_nextMove[axis] = moveValue; 
	else
		if(m_nextMove[axis] == moveValue)
			m_nextMove[axis] = 0.;
}

void MoveableCamera::move() {
	rotate();
	translate();
}

void MoveableCamera::rotate() {
	//Motion motion information retrieval
	//Comment if mouse motion events are enabled
	SDL_PumpEvents();
	int mouseRelX, mouseRelY;
	#ifdef __APPLE__
		int mystery = 0;
		SDL_GetRelativeMouseState(mystery, &mouseRelX, &mouseRelY);
	#else
		SDL_GetRelativeMouseState(&mouseRelX, &mouseRelY);
	#endif

	m_xMousePosition += 2.0*mouseRelX/(GLfloat)m_pApplication->width();
	m_yMousePosition += -2.0*mouseRelY/(GLfloat)m_pApplication->height();
	// std::cout<<m_xMousePosition<< " " << m_yMousePosition<<std::endl;

	GLfloat angleLong = m_xMousePosition * M_PI;
	GLfloat angleLat = m_yMousePosition * M_PI/2.;
	setRotation(yRotation(angleLong));
	//std::cout<<angleLong<< " " << angleLat<<std::endl;
	
	/*
	// Method with rotates

	GLfloat xAxis[]={1.0,0.0,0.0};
	GLfloat yAxis[]={0.0,1.0,0.0};
	GLfloat rotateAroundX[16], rotateAroundY[16];
	
	setToRotate(rotateAroundX, -angleLat, xAxis);
	setToRotate(rotateAroundY, angleLong, yAxis);

	setToIdentity(this->scene->camera->view);
	multMatrixBtoMatrixA(this->scene->camera->view,rotateAroundX);
	multMatrixBtoMatrixA(this->scene->camera->view,rotateAroundY);
	
	for(GLuint iCoord=0; iCoord<3; iCoord++)
	{
		//Updates the axis with values in view
		this->scene->camera->x[iCoord]=this->scene->camera->view[iCoord*4+0];
		this->scene->camera->y[iCoord]=this->scene->camera->view[iCoord*4+1];
		this->scene->camera->z[iCoord]=this->scene->camera->view[iCoord*4+2];
		//Updates the position of the camera c
		this->scene->camera->c[iCoord]=cameraNewPos[iCoord];

	}
	*/
}

void MoveableCamera::translate() {
	Vector3f nextGlobalMove(m_nextMove);
	nextGlobalMove[FORWARD] *= -1; // Inverse the forward axis
	nextGlobalMove.normalize();
	// @TODO : Switch from local coordinates to global coordinates then :
	
	setPosition(getPosition() + nextGlobalMove * MOVE_STEP);
}
