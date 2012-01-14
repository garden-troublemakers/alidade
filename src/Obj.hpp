#ifndef _OBJ_HPP_
#define _OBJ_HPP_

#include <stein/Object.hpp>
#include <stein/Scene.hpp>
#include <string>

enum ObjectType {
	PLAYER, VISIBLE_WALL, INVISIBLE_WALL, PORTALABLE_ZONE, ACTION_ZONE, MIRROR, DECOR
};
	
struct Obj {
	stein::Object &object;
	std::string path;
	ObjectType type;
	int block;
	double posX, posY, posZ;
	Obj(stein::Scene * pScene, const std::string & p, const ObjectType &t) :
		object(pScene->createObject(GL_TRIANGLES)), path(p), type(t)
	{
		pScene->addObjectToDraw(object.id);
	}
	std::list<Triangle> getTrianglesList() {
		ArrayBinder binder(vaoId);
		// Draw the elements stored by the vao
		
		// Inspiration :
		// glDrawElements(object.getPrimitivesType(), object.getNbIndices(), GL_UNSIGNED_INT, 0);
	}
};

#endif // _OBJ_HPP_
