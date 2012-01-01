#include "Player.hpp"

using namespace std;
using namespace stein;

Player::Player() : MoveableCamera(PLAYER_HEIGHT) {
	m_life = 100;
}

Player::~Player() {

}

bool Player::shootPortal(Color color, std::list<Obj> lObjects) {
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
