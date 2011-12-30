#include "Player.hpp"

Player::Player() : m_movement(), camera() {
	m_life = 100;
}

Player::~Player() {

}

void Player::move() {
	// cf code FPS
	// update camera
}

void Player::setMovement(unsigned int to) {
	// @FIXME : Need MERGE
}

bool Player::shootPortal(Color color, const Game & game, std::list<Obj> lObjects) {
	// dir = Vector "forward" normalized
	Ray ray(getPosition, dir);
	Intersection intersection;
	
	std::list<Obj>::iterator i;
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
	if(((Obj*)intersection.triangle.pObject)->type == PORTALABLE_ZONE) {
	
		if(portal
			if(!portals[type])
				portals[type] = Portal(type, isMirror, surface);
			else
				portals[type].setPortal(surface, collisionPoint);
				// change position
			if(!isMirror)
				portals[1-type].setPortal()/*setMirror(false)*/;
				
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
	return true;
}

unsigned int Player::getLife() {
	return m_life;
}
