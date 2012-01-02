#include "Player.hpp"
#include "GameApplication.hpp"

using namespace std;
using namespace stein;

Player::Player() : MoveableCamera(PLAYER_HEIGHT) {
	m_life = 100;
}

Player::~Player() {

}

bool Player::shootPortal(Color color) {
	// dir = Vector "forward" normalized
	/*Ray ray(getPosition, dir);
	Intersection intersection;
	
	list<Obj>::iterator i;
	
	for(i = lObjects.begin(); i!= lObjects.end(); ++i){
		// foreach triangle
		Triangle triangle(a, b, c, &i);
		Vector3f result;
		if(checkIntersection(ray, triangle, result)) {
			Intersection currentIntersection(ray, triangle, result);
			if(intersection.computeDepth() > currentIntersection.computeDepth)
				intersection = currentIntersection;
		}
	}
	------------------------------------
	if(((Obj*)intersection.triangle.pObject)->type == PORTALABLE_ZONE) {
	
		if(portal
			if(!portals[type])
				portals[type] = Portal(type, isMirror, surface);
			else
				portals[type].setPortal(surface, collisionPoint);
				// change position
			if(!isMirror)
				portals[1-type].setPortal() // setMirror(false);
				
		if(!!game.portals.redPortal) {
			if(game.portals.redPortal.getPosition() - intersection.point) {
			
			}
		if(color == BLUE) {
			if(!!game.portals.pRedPortal)
				if((game.portals.pRedPortal.getPosition() - intersection.point).norm() > Portal::WIDTH/2.) {
					game.portals.setPortal(newPortal);
				}
			}
			if(game.portals.redPortal == NULL) {
				game.portals.setPortal
			}
		} 
		if(game.portals.redPortal == NULL) {
			
		}
		game.portals.setPortal();
	}
=======
	MoveableCamera::move();*/
	return 0;
}

void Player::mirror(Portal& p) {
	// Calculate the angle for getting out of a mirror
	// Update m_nextMove in Camera
}


void Player::move() {
	SDL_PumpEvents();
	int mouseRelX, mouseRelY;
	#ifdef __APPLE__
	int mystery = 0;
	SDL_GetRelativeMouseState(mystery, &mouseRelX, &mouseRelY);
	#else
		SDL_GetRelativeMouseState(&mouseRelX, &mouseRelY);
	#endif

	m_xMousePosition += 2. * mouseRelX / (GLfloat)GameApplication::WIDTH;
	m_yMousePosition += -2. * mouseRelY / (GLfloat)GameApplication::HEIGHT;

	float moveStep=0.1;
	Vector3f cameraNewPos;

	float moveOnX = - m_nextMove[0] * moveStep;
	float moveOnY = m_nextMove[1] * moveStep;
	float moveOnZ = m_nextMove[2] * moveStep;
	for(size_t iCoord=0; iCoord<3; ++iCoord)
	{
		cameraNewPos[iCoord]=position[iCoord]
			+xAxis[iCoord]*moveOnX
			+yAxis[iCoord]*moveOnY
			+zAxis[iCoord]*moveOnZ;

	}
	
	float angleForWindowWidth=M_PI;
	//float angleForWindowHeight=M_PI/2.0;
	float angleLong = m_xMousePosition*angleForWindowWidth;
	//float angleLat = m_yMousePosition*angleForWindowHeight;
	//std::cout<<angleLong<< " " << angleLat<<std::endl;

	//Method with rotates

	//Matrix4f rotateAroundX = xRotation(angleLat);
	Matrix4f rotateAroundY = yRotation(angleLong);
	Matrix4f translate = translation(cameraNewPos);

	view.setIdentity();
	view = view * rotateAroundY * translate;

	for(size_t iCoord=0; iCoord<3; ++iCoord)
	{
		//Updates the axis with values in view
		xAxis[iCoord]=view(iCoord, 0);
		yAxis[iCoord]=view(iCoord, 1);
		zAxis[iCoord]=view(iCoord, 2);
		//Updates the position of the camera c
		position[iCoord] = cameraNewPos[iCoord];
	}
}

bool Player::checkCollisionPortals(const Portals& portals, const Portal& newP) {
	return false;
}
	/*Portal* checkPlayerCollisionPortal(const Portals & portals) const {
		if(_checkCollisionWithPortal(pPlayer->getPosition(), pBluePortal)) {
			return pRedPortal;
		}
		if(_checkCollisionWithPortal(pPlayer->getPosition(), pBluePortal)) {
			return pBluePortal;
		}
		return NULL;
	}
	
	bool _checkCollisionWithPortal(stein::Vector3f position, Portal* pPortal) const {
		return true;
	}*/

/*Obj* Player::checkCollisionWithObj(list<Obj*> lObjs) {
	// Here
}*/
