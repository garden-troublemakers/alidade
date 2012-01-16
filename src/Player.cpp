#include "Player.hpp"
#include "GameApplication.hpp"

using namespace std;
using namespace stein;

Player::Player(Scene * pScene) : MoveableCamera(PLAYER_HEIGHT), Obj(pScene, string(""), PLAYER), m_pScene(pScene), m_corners() {
	vector<unsigned int> indices;
	vector<stein::Vector3f> vertices;
	vector<stein::Vector3f> normals;
	vector<stein::UV> uvs;
	float distMax = 0;
	m_life = 100;
	block = 1;
	
	buildSquare(object, 1, m_builder);
	m_builder.unpack(indices, vertices, normals, uvs);
	
	for(size_t i = 0; i < indices.size() ; i+=3) {
		const unsigned int & v0 = indices[i];
		const unsigned int & v1 = indices[i+1];
		const unsigned int & v2 = indices[i+2];
		
		Vector3f vertex(vertices[v0].x, vertices[v1].y, vertices[v2].z);
		
		// Bring the vertex to the same altitude as the position vertex
		//vertex.y = position.y;
		
		// Distance of the vertex from the position
		float dist = sqrt((vertex.x - position.x) * (vertex.x - position.x)
						+ (vertex.y - position.y) * (vertex.y - position.y)
						+ (vertex.z - position.z) * (vertex.z - position.z));
		if (dist > distMax)
			distMax = dist;
		++distMax;
		// So distMax give the size of the bounding box
		m_corners.push_back(Vector3f(position.x + distMax, 0, position.z + distMax));
		m_corners.push_back(Vector3f(position.x - distMax, 0, position.z + distMax));
		m_corners.push_back(Vector3f(position.x - distMax, 0, position.z - distMax));
		m_corners.push_back(Vector3f(position.x + distMax, 0, position.z - distMax));
		m_corners.push_back(Vector3f(position.x - distMax, position.y + distMax , position.z - distMax));
	}
}

Player::~Player() {

}

void Player::shootPortal(Color color) {

}

bool Player::checkCollision(const Obj* obj) {
	list<Triangle> triangles = obj->getTrianglesList();
	
	for (list<Triangle>::iterator triangle = triangles.begin(); triangle != triangles.end(); ++triangle)
		for (vector<Vector3f>::iterator corner = m_corners.begin(); corner != m_corners.end(); ++corner)
			if ((triangle->a - *corner).dotP(triangle->normal) < 0)
				return true;
	return false;
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
