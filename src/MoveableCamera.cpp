#include "MoveableCamera.hpp"
#include <stein/Tools.hpp>
using namespace stein;
using namespace std;

MoveableCamera::MoveableCamera(GLfloat height, const Application * const pApplication) :
	Camera(), m_nextMove(), m_pApplication(pApplication), m_xMousePosition(), m_yMousePosition()
{	
	setPosition(Vector3f(0.,height,-1.));
}

MoveableCamera::~MoveableCamera()
{}

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
	
	if(add)
		m_nextMove[axis] = moveValue; 
	else
		if(m_nextMove[axis] == moveValue)
			m_nextMove[axis] = 0.;
}

// @TODO : Optimize this function
void MoveableCamera::move() {
	SDL_PumpEvents();
	int mouseRelX, mouseRelY;
	#ifdef __APPLE__
	int mystery = 0;
	SDL_GetRelativeMouseState(mystery, &mouseRelX, &mouseRelY);
	#else
		SDL_GetRelativeMouseState(&mouseRelX, &mouseRelY);
	#endif

	this->m_xMousePosition += 2.0*mouseRelX/(GLfloat)m_pApplication->width();
	this->m_yMousePosition += -2.0*mouseRelY/(GLfloat)m_pApplication->height();

	GLfloat moveStep=0.1;
	Vector3f cameraNewPos;

	GLfloat moveOnX = this->m_nextMove[0] * moveStep;
	GLfloat moveOnY = this->m_nextMove[1] * moveStep;
	GLfloat moveOnZ = this->m_nextMove[2] * moveStep;
	for(GLuint iCoord=0; iCoord<3; iCoord++)
	{
		cameraNewPos[iCoord]=position[iCoord]
			+xAxis[iCoord]*moveOnX
			+yAxis[iCoord]*moveOnY
			+zAxis[iCoord]*moveOnZ;

	}
	
	GLfloat angleForWindowWidth=M_PI;
	GLfloat angleForWindowHeight=M_PI/2.0;
	GLfloat angleLong = this->m_xMousePosition*angleForWindowWidth;
	GLfloat angleLat = this->m_yMousePosition*angleForWindowHeight;
	//std::cout<<angleLong<< " " << angleLat<<std::endl;

	//Method with rotates

	Matrix4f rotateAroundX = xRotation(angleLat);
	Matrix4f rotateAroundY = yRotation(angleLong);
	Matrix4f translate = translation(cameraNewPos);

	view.setIdentity();
	view = view * rotateAroundY * translate;

	for(GLuint iCoord=0; iCoord<3; iCoord++)
	{
		//Updates the axis with values in view
		xAxis[iCoord]=view(iCoord, 0);
		yAxis[iCoord]=view(iCoord, 1);
		zAxis[iCoord]=view(iCoord, 2);
		//Updates the position of the camera c
		position[iCoord] = cameraNewPos[iCoord];
	}
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
	// std::cout<<m_m_xMousePosition<< " " << m_yMousePosition<<std::endl;

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
	nextGlobalMove[RIGHT] *= -1; // Inverse the right axis
	nextGlobalMove[TOP] *= -1; // Inverse the right axis
	nextGlobalMove.normalize();
	// @TODO : Switch from local coordinates to global coordinates then :
	
	setPosition(getPosition() + nextGlobalMove * MOVE_STEP);
}
