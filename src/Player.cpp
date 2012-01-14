#include "Player.hpp"
#include "GameApplication.hpp"

using namespace std;
using namespace stein;

Player::Player(Scene * pScene) : MoveableCamera(PLAYER_HEIGHT), Obj(pScene, string(""), PLAYER), m_pScene(pScene) {
	m_life = 100;
	block = 1;
	buildSquare(object, 1);
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
		Triangle triangle(a, b, c, normal, (Obj*)i);
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

void Player::teleport(Portal* pPortal) {
	// Calculate the angle for getting out of a mirror
	setPosition(mirrorPosition(pPortal));
	// @TODO : ! setDirection !!
	// setDirection(mirrorDirection(Portal* pPortal));
	// Update m_nextMove in Camera
	// Matrix4f rotateAroundY = yRotation(angleLong);
}


Vector3f Player::mirrorPosition(Portal* pPortal) {
	// Calculate the angle for getting out of a mirror
	// Update m_nextMove in Camera
	return pPortal->pSecondPortal->getPosition() + getPosition() - pPortal->getPosition();
	// set
	//Matrix4f rotateAroundY = yRotation(angleLong);
}


Vector3f Player::mirrorDirection(Portal* pPortal) {
	return Vector3f(1., 0., 0.); //pPortal->getPosition() + (getPosition() - pPortal->getPosition()));
}

// @FIXME we need me, inherited from setDirection.
void Player::setDirection(Vector3f rotation) {
	// orientate camera here, will be taken from move.
	// we can pass the angle (vector ?) of the computed rotation.
	// This shall change update camera's landmark ...
}



/*
 * @TODO We need to use setPosition and setRotation here
 * those functions must inherit from MoveableCamera
 * setRotation should be called when the mouse is moving.
 * setPosition is called on every frame.
 */
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
		cameraNewPos[iCoord]=position[iCoord]
			+xAxis[iCoord]*moveOnX
			+yAxis[iCoord]*moveOnY
			+zAxis[iCoord]*moveOnZ;
	
	float angleForWindowWidth=M_PI;
	float angleLong = m_xMousePosition*angleForWindowWidth;

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
	posX = cameraNewPos[0];
	posY = cameraNewPos[1];
	posZ = cameraNewPos[2];
	gotoPositionRotation(cameraNewPos, rotateAroundY);
	/*Matrix4f transformBody = rotateAroundY;
	Matrix4f inverseTranslate;
	inverseTranslate.setIdentity();
	for(size_t iCoord=0; iCoord<3; ++iCoord)
		inverseTranslate(3,iCoord) = -cameraNewPos[iCoord];
	transformBody.transpose();
	m_pScene->setDrawnObjectModel(object.id, inverseTranslate*transformBody);*/
	
	// Reinit body position and orientation
	
}

bool Player::checkCollisionPortals(const Portals& portals, const Portal& newP) {
	return false;
}


void Player::gotoPositionRotation(const stein::Vector3f & pos, stein::Matrix4f rot) {
	//pos.y *= -1;
	rot.transpose();
	m_pScene->setDrawnObjectModel(object.id, translation(-pos)*rot);
	setPosition(pos);
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
